#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>

using namespace std;

void *fun(void *arg) {
	cout << "new pthread do work..tid: " << pthread_self() << endl;
	return NULL;
}

void *fun2(void *arg) {
	int var = (int)(long)arg;
	cout << "pthread2 var = " << var << endl;
	return NULL;
}

int main() {
	pthread_t tid = -1;
	pthread_t tid2 = -1;
	int ret = -1;

	ret = pthread_create(&tid, NULL, fun, NULL);
	if(0 != ret) {
		cout << "pthread_create failed." << endl;
		return 1;
	}
	ret = pthread_create(&tid2, NULL, fun2, (void*)0x3);
	if(0 != ret) {
		cout << "pthread_create failed." << endl;
		return 1;
	}
	cout << "main thread tid: " << pthread_self() << endl;
	
	cout << "按下任意键退出..." << endl;
	getchar();

	return 0;
}
