#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main() {
	int fd = -1;

	//1.以只读方式打开文件，如果文件不存在则报错
	//fd = open("txt", O_RDONLY);

	//2.以只写方式打开文件，如果文件存在直接打开，如果文件不存在就新建
	//fd = open("txt", O_WRONLY | O_CREAT, 0644);

	//3.以只写方式打开文件，如果文件存在就报错，如果文件不存在就新建
	//fd = open("txt", O_WRONLY | O_CREAT | O_EXCL, 0644);

	//4.以读写方式打开文件，如果文件存在就打开，如果文件不存在就新建
	//fd = open("txt", O_RDWR | O_CREAT, 0644);

	//5.以读写方式打开文件，如果文件存在就清空打开，如果文件不存在就新建
	//fd = open("txt", O_WRONLY | O_TRUNC  | O_CREAT, 0644);

	//6.以只写和追加方式打开文件，如果文件不存在就报错
	fd = open("txt", O_WRONLY | O_APPEND, 0644);
	if(fd == -1) {
		perror("open");
		return 1;
	}

	cout << "fd: " << fd << endl;

	close(fd);
	return 0;
}
