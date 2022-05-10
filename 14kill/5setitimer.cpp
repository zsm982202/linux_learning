#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

using namespace std;

void fun(int signum) {
	cout << "捕捉到信号：" << signum << endl;
}

int main() {
	int ret = -1;
	struct itimerval tmo;
	tmo.it_value.tv_sec = 3;
	tmo.it_value.tv_usec = 0;

	tmo.it_interval.tv_sec = 2;
	tmo.it_interval.tv_usec = 0;

	signal(SIGALRM, fun);

	ret = setitimer(ITIMER_REAL, &tmo, NULL);

	if(-1 == ret) {
		perror("setitimer");
		return 1;
	}
	
	cout << "按下任意键继续..." << endl;
	getchar();

	return 0;
}
