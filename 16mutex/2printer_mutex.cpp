#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t mutex;

void *fun1(void *arg) {
	pthread_mutex_lock(&mutex);
	for(int i = 'A';i <= 'Z';i++) {
		putchar(i);
		fflush(stdout);
		usleep(100000);//100ms
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void *fun2(void *arg) {
	pthread_mutex_lock(&mutex);
	for(int i = 'a';i <= 'z';i++) {
		putchar(i);
		fflush(stdout);
		usleep(100000);//100ms
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main() {
	int ret = -1;
	pthread_t tid1, tid2;
	
	ret = pthread_mutex_init(&mutex, NULL);
	if(0 != ret) {
		cout << "pthread_mutex_init failed.." << endl;
		return 1;
	}
	cout << "初始化互斥量成功.." << endl;

	pthread_create(&tid1, NULL, fun1, NULL);
	pthread_create(&tid2, NULL, fun2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	cout << endl;
	ret = pthread_mutex_destroy(&mutex);
	if(0 != ret) {
		cout << "pthread_mutex_destroy failed.." << endl;
		return 1;
	}
	cout << "销毁互斥量成功.." << endl;
	cout << "main thread exit.." << endl;
	
	return 0;
}
