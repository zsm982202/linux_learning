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

	fd = open("txt", O_RDWR | O_CREAT, 0644);
	if(fd == -1) {
		perror("open");
		return 1;
	}

	cout << "fd: " << fd << endl;

	newfd = dup(fd);
	if(newfd == -1) {
		perror("dup");
		return 1;
	}

	cout << "newfd: " << newfd << endl;

	write(fd, "ABCDEFG", 7);
	write(newfd, "1234567", 7);

	close(fd);
	close(newfd);

	return 0;
}
