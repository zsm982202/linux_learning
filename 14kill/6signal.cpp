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
	//ctrl + C
	signal(SIGINT, fun1);
	//ctrl + "\"
	signal(SIGQUIT,	fun2);
	while(1) {
		sleep(1);
	}
	return 0;
}
