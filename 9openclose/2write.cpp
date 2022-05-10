#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

using namespace std;

int main() {
	int fd = -1;
	int ret = -1;

	char *str = (char*)("hello itcast\n");

	//1.以只读方式打开文件
	fd = open("txt", O_WRONLY | O_CREAT, 0644);

	if(fd == -1) {
		perror("open");
		return 1;
	}

	cout << "fd: " << fd << endl;

	//2.写文件
	ret = write(fd, str, strlen(str));
	cout << "strlen: " << strlen(str) << endl;
	if(ret == -1) {
		perror("write");
		return 1;
	}


	//3.关闭文件
	close(fd);
	return 0;
}
