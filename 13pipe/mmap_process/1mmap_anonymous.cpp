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
	int ret = -1;
	pid_t pid = -1;
	void *addr = NULL;
	
	addr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(addr == MAP_FAILED) {
		perror("mmap");
		return 1;
	}

	cout << "匿名文件存储映射ok" << endl;
	
	pid = fork();
	if(pid < 0) {
		perror("fork");
		munmap(addr, 1024);
		return 1;
	}
	if(pid == 0) {
		//子进程
		memcpy(addr, "1234567890", 10);
	} else {
		//父进程
		wait(NULL);
		cout << (char*)addr << endl;
	}

	munmap(addr, 1024);
	return 0;
}
