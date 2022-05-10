#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main() {
	int fd = -1;
	int newfd = -1;
	int ret = -1;

	fd = open("txt", O_WRONLY | O_CREAT, 0644);
	if(fd == -1) {
		perror("open");
		return 1;
	}
	cout << "fd: " << fd << endl;

	ret = fcntl(fd, F_GETFL);
	if(ret == -1) {
		perror("fcntl");
		return 1;
	}

	if(ret & O_APPEND)
		cout << "before append" << endl;
	else
		cout << "before not append" << endl;

	ret = ret | O_APPEND;
	ret = fcntl(fd, F_SETFL, ret);
	if(ret == -1) {
		perror("fcntl");
		return 1;
	}
	ret = fcntl(fd, F_GETFL);

	if(ret & O_APPEND)
		cout << "after append" << endl;
	else
		cout << "after not append" << endl;
	close(fd);

	return 0;
}
