#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main() {
	pid_t pid = -1;

	pid = getpid();
	cout << "pid: " << pid << endl;
	
	pid = getppid();
	cout << "ppid: " << pid << endl;

	pid = getpgid(getpid());
	cout << "pgid: " << pid << endl;

	return 0;
}
