#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#define SIZE 64

using namespace std;

//父进程写 子进程读
int main() {
	pid_t pid = -1;
	int fds[2];
	int ret = -1;
	char buf[SIZE];

	ret = pipe(fds);
	if(ret == -1) {
		perror("pipe");
		return 1;
	}
//	cout << "fd[0]: " << fds[0] << "  fd[1]: " << fds[1] << endl;
	pid = fork();
	if(pid == -1) {
		perror("fork");
		return 1;
	}
	if(pid == 0) {
		//子进程
		close(fds[1]);
		memset(buf, 0, SIZE);
		ret = read(fds[0], buf, SIZE);
		if(ret == -1) {
			perror("read");
			exit(-1);
		}
		cout << "child process buf: " << buf << endl;
		close(fds[0]);
		exit(0);
	}
	//父进程
	close(fds[0]);
	sleep(1);	
	ret = write(fds[1], "ABCDEFGHIJK", 10);
	if(ret == -1) {
		perror("write");
		return 1;
	}
	cout << "parent process write len: " << ret << endl;
	
	close(fds[1]);

	return 0;
}
