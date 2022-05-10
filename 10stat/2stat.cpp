#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

int show_file_type(struct stat *s) {
	switch(s->st_mode & S_IFMT) {
	case S_IFREG:
		cout << "该文件是普通文件" << endl;
		break;
	case S_IFDIR:
		cout << "该文件是目录" << endl;
		break;
	case S_IFCHR:
		cout << "该文件是字符设备" << endl;
		break;
	case S_IFBLK:
		cout << "该文件是块设备" << endl;
		break;
	case S_IFSOCK:
		cout << "该文件是套接字文件" << endl;
		break;
	case S_IFIFO:
		cout << "该文件是管道" << endl;
		break;
	case S_IFLNK:
		cout << "该文件是符号连接" << endl;
		break;
	default:
		cout << "未知文件类型" << endl;
		break;
	}
	return 0;
}

int show_file_type_v2(struct stat *s) {
	if(S_ISREG(s->st_mode))
		cout << "Is a regular file" << endl;
	if(S_ISDIR(s->st_mode))
		cout << "Is a dictionary" << endl;
	if(S_ISCHR(s->st_mode))
		cout << "Is a character device" << endl;
	if(S_ISBLK(s->st_mode))
		cout << "Is a block device" << endl;
	if(S_ISFIFO(s->st_mode))
		cout << "Is a FIFO" << endl;
	if(S_ISLNK(s->st_mode))
		cout << "Is a symbol link" << endl;
	if(S_ISSOCK(s->st_mode))
		cout << "Is a socket" << endl;
	return 0;
}


int show_file_permission(struct stat *s) {
	if(s->st_mode & S_IRUSR)
		cout << "r";
	else
		cout << "-";
	if(s->st_mode & S_IWUSR)
		cout << "w";
	else
		cout << "-";
	if(s->st_mode & S_IXUSR)
		cout << "x";
	else
		cout << "-";

	if(s->st_mode & S_IRGRP)
		cout << "r";
	else
		cout << "-";
	if(s->st_mode & S_IWGRP)
		cout << "w";
	else
		cout << "-";
	if(s->st_mode & S_IXGRP)
		cout << "x";
	else
		cout << "-";

	if(s->st_mode & S_IROTH)
		cout << "r";
	else
		cout << "-";
	if(s->st_mode & S_IWOTH)
		cout << "w";
	else
		cout << "-";
	if(s->st_mode & S_IXOTH)
		cout << "x";
	else
		cout << "-";
	cout << endl;
	return 0;
}

int main(int argc, char* argv[]) {
	int ret = -1;
	struct stat s;

	if(argc != 2) {
		cout << "usage: ./a.out filename" << endl;
	}

	ret = stat(argv[1], &s);
	if(ret == -1) {
		perror("stat");
		return 1;
	}
	
	show_file_type(&s);
	show_file_type_v2(&s);
	show_file_permission(&s);
	return 0;
}
