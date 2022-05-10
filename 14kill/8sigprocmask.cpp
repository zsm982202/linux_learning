#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

using namespace std;

void fun1(int signum) {
	cout << "捕捉到信号：" << signum << endl;
}

void fun2(int signum) {
	cout << "捕捉到信号：" << signum << endl;
}

int main() {
	int ret = -1;
	sigset_t set;
	sigset_t old;
	//ctrl + C
	signal(SIGINT, fun1);
	//ctrl + "\"
	signal(SIGQUIT,	fun2);
	
	cout << "按下回车键，阻塞信号2" << endl;
	getchar();
	sigemptyset(&old);
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	ret = sigprocmask(SIG_BLOCK, &set, &old);
	if(-1 == ret) {
		perror("sigprocmask");
		return 1;
	}
	cout << "屏蔽信号2" << endl;
	cout << "按下回车键解除信号2的阻塞" << endl;
	getchar();

	ret = sigprocmask(SIG_SETMASK, &old, NULL);
	if(-1 == ret) {
		perror("sigprocmask");
		return 1;
	}
	cout << "按下回车键退出" << endl;
	getchar();
	return 0;
}
