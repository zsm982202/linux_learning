#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

using namespace std;

void show_set(sigset_t *set) {
	for(int i = 1;i < 32;i++) {
		if(sigismember(set, i))
			cout << "1";
		else
			cout << "0";
	}
	cout << endl;
}

int main() {
	sigset_t set;
	sigemptyset(&set);
	show_set(&set);
	sigfillset(&set);
	show_set(&set);
	sigdelset(&set, SIGINT);
	sigdelset(&set, SIGQUIT);
	show_set(&set);
	sigaddset(&set, SIGINT);
	show_set(&set);
	return 0;
}
