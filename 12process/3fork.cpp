#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main() {
	pid_t pid = -1;

	pid = fork();
	
	if(pid == 0) {
		//子进程
		while(1) {
			cout << "子进程hello itcast pid: " << getpid() << " ppid: " << getppid() << endl;
			sleep(1);
		}
	} else {
		//父进程
		while(1) {
			cout << "父进程hello world pid: " << getpid() << " cpid: " << pid << endl;
			sleep(1);
		}
	}

	return 0;
}
