#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
using namespace std;

#define SIZE 128

int main() {
	int fd = -1;
	int ret = -1;

	char buf[SIZE];

	fd = open("txt", O_RDWR | O_CREAT, 0644);
	if(fd == -1) {
		perror("open");
		return 1;
	}
	cout << "fd: " << fd << endl;

	write(fd, "ABCDEFG", 7);
	ret = lseek(fd, 32, SEEK_SET);
	if(ret == -1) {
		perror("lseek");
		return 1;
	}

	write(fd, "1234567890", 10);
	lseek(fd, 0, SEEK_SET);
	memset(buf, 0, SIZE);
	read(fd, buf, SIZE);
	cout << "read buf: " << buf << endl;

	close(fd);
	return 0;
}
