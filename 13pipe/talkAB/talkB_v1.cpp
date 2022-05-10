#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 128

using namespace std;

int main() {
	int ret = -1;

	char buf[SIZE];

	ret = fork();
	if(ret < 0) {
		perror("fork");
		return 1;
	}
	if(ret == 0) {
		//子进程
		int fdw = -1;
		fdw = open("fifo1", O_WRONLY);
		if(fdw == -1) {
			perror("open");
			return 1;
		}
		cout << "只写打开fifo1" << endl;
		while(1) {
			memset(buf, 0 ,SIZE);
			fgets(buf, SIZE, stdin);
			if(buf[strlen(buf) - 1] == '\n')
				buf[strlen(buf) - 1] = '\0';

			ret = write(fdw, buf, strlen(buf));
			if(ret <= 0) {
				perror("write");
				break;
			}
			cout << "write ret: " << ret << endl;
		}
		close(fdw);
		exit(0);
	}
	//父进程
	int fdr = -1;
	fdr = open("fifo2", O_RDONLY);
	if(fdr == -1) {
		perror("open");
		return 1;
	}
	cout << "只读打开fifo2" << endl;

	while(1) {
		memset(buf, 0, SIZE);
		ret = read(fdr, buf, SIZE);
		if(ret <= 0) {
			perror("read");
			break;
		}
		cout << "talkB read fifo:" << buf << endl;
	}
	close(fdr);
	return 0;
}
