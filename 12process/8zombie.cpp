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

	if(pid == 0) {
		for(int i = 0;i < 5;i++) {
			cout << "子进程" << i << endl;
			sleep(1);
		}
		cout << "子进程结束了" << endl;
		exit(0);
	}

	//getchar();
	sleep(100);
	cout << "父进程睡醒了退出" << endl;
	return 0;
}
