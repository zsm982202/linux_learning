#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

using namespace std;

int main() {
	pid_t pid = -1;
	int ret = -1;

	pid = getsid(0);
	if(-1 == pid) {
		perror("getsid");
		return 1;
	}
	cout << "sid: " << pid << endl;
	
	ret = fork();
	if(-1 == ret) {
		perror("fork");
		return 1;
	}
	if(0 == ret) {
		//新建一个会话
		pid = setsid();
		if(-1 == pid) {
			perror("setsid");
			return 1;
		}
		cout << "sid: " << pid << endl;
	}
	return 0;
}
