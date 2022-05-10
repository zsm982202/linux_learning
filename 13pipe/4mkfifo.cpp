#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int main() {
	int ret = -1;
	ret = mkfifo("fifo", 0644);
	if(ret == -1) {
		perror("mkfifo");
		return 1;
	}
	cout << "创建有名管道成功" << endl;
	return 0;
}
