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

	newfd = fcntl(fd, F_DUPFD, 20);
	if(newfd == -1) {
		perror("fcntl");
		return 1;
	}
	cout << "newfd: " << newfd << endl;

	write(fd, "123456789", 9);
	write(newfd, "ABCDEFGH", 8);

	close(fd);
	close(newfd);

	return 0;
}
