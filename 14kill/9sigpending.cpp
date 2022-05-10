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
	
	cout << "按下回车键，阻塞信号2,3" << endl;
	getchar();
	sigemptyset(&old);
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	ret = sigprocmask(SIG_BLOCK, &set, &old);
	if(-1 == ret) {
		perror("sigprocmask");
		return 1;
	}
	cout << "屏蔽信号2,3" << endl;

	cout << "按下回车键获取未决的信号" << endl;
	getchar();

	sigemptyset(&set);
	ret = sigpending(&set);
	if(-1 == ret) {
		perror("sigpending");
		return 1;
	}
	cout << "未决信号：";
	for(int i = 1;i < 32;i++) {
		if(sigismember(&set, i))
			cout << i << " ";
	}
	cout << endl;

	cout << "按下回车键解除信号2,3的阻塞" << endl;
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
