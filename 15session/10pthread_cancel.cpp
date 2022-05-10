#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void *fun(void *arg) {
	for(int i = 0;i < 5;i++) {
		cout << "pthread do working.." << i << endl;
		sleep(1);
	}
	pthread_exit(NULL);
//	return NULL;
}

int main() {
	int ret = -1;
	pthread_t tid = -1;
	ret = pthread_create(&tid, NULL, fun, NULL);
	if(0 != ret) {
		cout << "pthread_create failed.." << endl;
		return 1;
	}

	cout << "main thread tid: " << pthread_self() << endl;
	ret = pthread_detach(tid);
	if(0 != ret) {
		cout << "pthread_detach failed.." << endl;
		return 1;
	}
	
	sleep(3);
	
	cout << "主线程睡眠了3s 取消子线程" << endl;
	pthread_cancel(tid);
	cout << "main exit.." << endl;
	return 0;
}
