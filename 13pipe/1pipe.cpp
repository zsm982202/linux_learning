#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

using namespace std;

int main() {
	int fds[2];
	int ret = -1;

	ret = pipe(fds);
	if(ret == -1) {
		perror("pipe");
		return 1;
	}
	cout << "fd[0]: " << fds[0] << "  fd[1]: " << fds[1] << endl;
	
	cout << "pipe size(read): " << fpathconf(fds[0], _PC_PIPE_BUF) << endl;
	cout << "pipe size(write): " << fpathconf(fds[1], _PC_PIPE_BUF) << endl;

	close(fds[0]);
	close(fds[1]);

	return 0;
}
