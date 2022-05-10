#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <signal.h>
#include <unistd.h>

using namespace std;

void fun(int signo) {
	cout << "捕捉到信号" << signo << endl;
}

void fun1(int signo, siginfo_t *info, void *context) {
	cout << "捕捉到信号" << signo << endl;
}

int main() {
	int ret = -1;
#if 0
	struct sigaction act;
	//使用旧的信号处理函数指针
	act.sa_handler = fun;
	//标志为默认，默认使用旧的信号处理函数指针
	act.sa_flags = 0;
#else
	struct sigaction act;
	//使用新的信号处理函数指针
	act.sa_sigaction = fun1;
	act.sa_flags = SA_SIGINFO;
#endif
	ret = sigaction(SIGINT, &act, NULL);
	if(-1 == ret) {
		perror("sigaction");
		return 1;
	}

	cout << "按下回车键退出" << endl;
	while(1) {
		sleep(1);
	}
	//getchar();

}
