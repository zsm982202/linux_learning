#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main() {
	pid_t pid = -1;
	pid = fork();
	if(pid == -1) {
		perror("fork");
		return 1;
	}

	if(pid > 0) {
		cout << "父进程休息3秒后退出" << endl;
		sleep(3);
		cout << "父进程退出" << endl;
		exit(0);
	}

	while(1) {
		cout << "子进程工作 ppid: " << getppid() << endl;
		sleep(1);
	}

	return 0;
}
