#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

using namespace std;

void fun(int signo) {
	cout << "捕捉到信号：" << signo << endl;
	cout << "子进程退出" << endl;
	//非阻塞方式
	while(waitpid(-1, NULL, WNOHANG) > 0) {	}
}

int main() {
	pid_t pid = -1;
	
	struct sigaction act;
	act.sa_handler = fun;
	act.sa_flags = 0;
	sigaction(SIGCHLD, &act, NULL);

	pid = fork();
	if(-1 == pid) {
		perror("fork");
		return 1;
	}
	if(0 == pid) {
		cout << "子进程sleep2秒" << endl;
		sleep(2);
		cout << "子进程醒来" << endl;
		exit(0);
	}
	while(1) {
		cout << "父进程do working" << endl;
		sleep(1);
	}

	return 0;
}
