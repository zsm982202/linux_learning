#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int num = 100;

void *fun(void *arg) {
	for(int i = 0;i < 5;i++) {
		cout << "fun thread do working.." << i << endl;
		sleep(1);
	}
	return (void*)0x7;
}

int main() {
	int ret = -1;
	void *retp = NULL;
	pthread_t tid;
	memset(&tid, 0, sizeof(tid));
	
	ret = pthread_create(&tid, NULL, fun, NULL);
	if(0 != ret) {
		cout << "pthread_create failed.." << endl;
		return 1;
	}
	cout << "main thread running.." << endl;

	ret = pthread_join(tid, &retp);
	if(0 != ret) {
		cout << "pthread_join failed.." << endl;
		return 1;
	}
	cout << "retp: " << (int*)retp << endl;
//	printf("retp: %p\n", retp);
	cout << "main exit.." << endl;

	return 0;
}
