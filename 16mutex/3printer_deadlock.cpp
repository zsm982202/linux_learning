#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void *fun1(void *arg) {
	pthread_mutex_lock(&mutex1);
	cout << "线程1加锁资源1ok.." << endl;
	pthread_mutex_lock(&mutex2);
	cout << "线程1加锁资源2ok.." << endl;
	for(int i = 'A';i <= 'Z';i++) {
		putchar(i);
		fflush(stdout);
		usleep(100000);//100ms
	}
	cout << endl;
	pthread_mutex_unlock(&mutex1);
	pthread_mutex_unlock(&mutex2);
	return NULL;
}

void *fun2(void *arg) {
	pthread_mutex_lock(&mutex2);
	cout << "线程2加锁资源2ok.." << endl;
	pthread_mutex_lock(&mutex1);
	cout << "线程2加锁资源1ok.." << endl;
	for(int i = 'a';i <= 'z';i++) {
		putchar(i);
		fflush(stdout);
		usleep(100000);//100ms
	}
	cout << endl;
	pthread_mutex_unlock(&mutex1);
	pthread_mutex_unlock(&mutex2);
	return NULL;
}

int main() {
	int ret = -1;
	pthread_t tid1, tid2;
	
	ret = pthread_mutex_init(&mutex1, NULL);
	if(0 != ret) {
		cout << "pthread_mutex_init1 failed.." << endl;
		return 1;
	}
	ret = pthread_mutex_init(&mutex2, NULL);
	if(0 != ret) {
		cout << "pthread_mutex_init2 failed.." << endl;
		return 1;
	}
	cout << "初始化2个互斥量成功.." << endl;

	pthread_create(&tid1, NULL, fun1, NULL);
	pthread_create(&tid2, NULL, fun2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	ret = pthread_mutex_destroy(&mutex1);
	if(0 != ret) {
		cout << "pthread_mutex_destroy1 failed.." << endl;
		return 1;
	}
	ret = pthread_mutex_destroy(&mutex2);
	if(0 != ret) {
		cout << "pthread_mutex_destroy2 failed.." << endl;
		return 1;
	}
	cout << "销毁互斥量成功.." << endl;
	cout << "main thread exit.." << endl;
	
	return 0;
}
