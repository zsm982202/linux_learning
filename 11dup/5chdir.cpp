#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 32

using namespace std;

int main() {
	int ret = -1;
	char* cret = NULL;
	char buf[SIZE];
	memset(buf, 0, SIZE);
	cret = getcwd(buf, SIZE);
	
	if(cret == NULL) {
		perror("getcwd");
		return 1;
	}
	cout << "before chdir buf: "  << buf << endl;
	cout << "before chdir ret: " << cret << endl;

	ret = chdir("/home/zsm");
	if(ret == -1) {
		perror("chdir");
		return 1;
	}

	memset(buf, 0, SIZE);
	cret = getcwd(buf, SIZE);
	
	if(cret == NULL) {
		perror("getcwd");
		return 1;
	}
	cout << "after buf: "  << buf << endl;
	cout << "after ret: " << cret << endl;
	return 0;
}
