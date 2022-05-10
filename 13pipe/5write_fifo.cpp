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
	int i = 0;
	int fd = -1;
	int ret = -1;

	char buf[SIZE];

	fd = open("fifo", O_WRONLY);
	if(fd == -1) {
		perror("open");
		return 1;
	}
	cout << "只写打开一个管道" << endl;

	while(1) {
		memset(buf, 0, SIZE);
		sprintf(buf, "hello world %d", i++);
		ret = write(fd, buf, strlen(buf));
		if(ret <= 0) {
			perror("write");
			break;
		}
		cout << "write fifo:" << ret << endl;
		sleep(1);
	}
	close(fd);
	return 0;
}
