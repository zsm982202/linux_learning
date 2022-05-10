#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

sem_t sem;

void *fun1(void *arg) {
	sem_wait(&sem);
	for(int i = 'A';i <= 'Z';i++) {
		putchar(i);
		fflush(stdout);
		usleep(100000);//100ms
	}
	sem_post(&sem);
	return NULL;
}

void *fun2(void *arg) {
	sem_wait(&sem);
	for(int i = 'a';i <= 'z';i++) {
		putchar(i);
		fflush(stdout);
		usleep(100000);//100ms
	}
	sem_post(&sem);
	return NULL;
}

int main() {
	int ret = -1;
	pthread_t tid1, tid2;
	
	ret = sem_init(&sem, 0, 1);
	if(0 != ret) {
		cout << "sem_init failed.." << endl;
		return 1;
	}
	cout << "初始化信号量成功.." << endl;

	pthread_create(&tid1, NULL, fun1, NULL);
	pthread_create(&tid2, NULL, fun2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	cout << endl;
	ret = sem_destroy(&sem);
	if(0 != ret) {
		cout << "sem_destroy failed.." << endl;
		return 1;
	}
	cout << "销毁信号量成功.." << endl;
	cout << "main thread exit.." << endl;
	
	return 0;
}
