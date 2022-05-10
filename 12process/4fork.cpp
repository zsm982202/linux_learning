#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int num = 100;

int main() {
	int var = 88;
	pid_t pid = -1;
	int *p = new int();
	//int *p;
	//p = (int*)malloc(sizeof(int));
	if(p == NULL) {
		cout << "malloc failed" << endl;
		return 1;
	}
	//memset(p, 0, sizeof(int));
	*p = 200;
	pid = fork();
	if(pid == -1) {
		perror("fork");
		return 1;
	}	
	if(pid == 0) {
		//子进程
		sleep(1);
		cout << "子进程唤醒之后var: " << var << " num: " << num << endl;// " *p: " << *p << endl;
		//free(p);
		delete p;
	} else {
		//父进程
		cout << "父进程之前var: " << var << " num: " << num << endl; //" *p: " << *p << endl;
		var++;
		num++;
		(*p)++;
		cout << "父进程之后var: " << var << "num: " << num << endl;// " *p: " << *p << endl;
		//free(p);
		delete p;
	}

	//delete p;
	return 0;
}
