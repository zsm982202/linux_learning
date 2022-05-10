#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

#define SIZE 128	

using namespace std;

int main() {
	int fd = -1;
	int ret = -1;

	char buf[SIZE];

	//1.以只读方式打开文件
	fd = open("txt", O_RDONLY);

	if(fd == -1) {
		perror("open");
		return 1;
	}

	cout << "fd: " << fd << endl;

	//2.读文件
	memset(buf, 0, SIZE);
	ret = read(fd, buf, SIZE);
	if(ret == -1) {
		perror("read");
		return 1;
	}
	cout << "ret: " << ret << endl;
	cout << "buf: " << buf << endl;

	//3.关闭文件
	close(fd);
	return 0;
}
