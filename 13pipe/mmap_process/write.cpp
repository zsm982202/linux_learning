#include <iostream>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>

using namespace std;

int main() {
	int fd = -1;
	int ret = -1;
	pid_t pid = -1;
	void *addr = NULL;
	
	fd = open("txt", O_RDWR);
	if(fd == -1) {
		perror("open");
		return 1;
	}

	addr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(addr == MAP_FAILED) {
		perror("mmap");
		return 1;
	}

	cout << "文件存储映射ok" << endl;
	close(fd);
	
	memcpy(addr, "ABCDEFGHIJ", 10);
	munmap(addr, 1024);
	return 0;
}
