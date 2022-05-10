#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

using namespace std;

int main() {
	unsigned int ret = 0;
	ret = alarm(5);
	cout << "上次闹钟剩下的时间" << ret << endl;
	sleep(2);
	ret = alarm(8);
	cout << "上次闹钟剩下的时间" << ret << endl;
	int i = 0;
	while(1) {
		cout << i++ << endl;
		sleep(1);
	}
	return 0;
}
