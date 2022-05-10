#include <iostream>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

using namespace std;

int main() {
	pid_t pid = -1;
	pid = fork();
	if(pid < 0) {
		perror("fork");
		return 1;
	}
	if(pid == 0) {
		while(1) {
			cout << "child process do work..." << endl;
			sleep(1);
		}
		return 0;
	}
	sleep(5.5);
	kill(pid, 15);
	cout << "parent process kills child process" << endl;
	return 0;
}
