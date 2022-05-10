#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int flag = 0;

pthread_mutex_t mutex;
pthread_cond_t cond;

void *fun1(void *arg) {
	while(1) {
		pthread_mutex_lock(&mutex);
		flag = 1;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond);
		sleep(2);
	}
	return NULL;
}

void *fun2(void *arg) {
	while(1) {
		pthread_mutex_lock(&mutex);
		if(0 == flag) {
			pthread_cond_wait(&cond, &mutex);
		}
		cout << "线程2条件满足，开始运行.." << endl;
		flag = 0;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main() {
	int ret = -1;
	pthread_t tid1, tid2;

	ret = pthread_cond_init(&cond, NULL);
	if(0 != ret) {
		cout << "pthread_cond_init failed.." << endl;
		return 1;
	}
	ret = pthread_mutex_init(&mutex, NULL);
	if(0 != ret) {
		cout << "pthread_mutex_init failed.." << endl;
		return 1;
	}

	pthread_create(&tid1, NULL, fun1, NULL);
	pthread_create(&tid2, NULL, fun2, NULL);
	ret = pthread_join(tid1, NULL);
	if(0 != ret) {
		cout << "pthread_join failed.." << endl;
		return 1;
	}
	ret = pthread_join(tid2, NULL);
	if(0 != ret) {
		cout << "pthread_join failed.." << endl;
		return 1;
	}
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	
	return 0;
}
