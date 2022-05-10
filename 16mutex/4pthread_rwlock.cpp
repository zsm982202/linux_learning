#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int num = 0;

pthread_rwlock_t rwlock;

void *fun_read(void *arg) {
	int index = (int)(long)arg;

	while(1) {
		pthread_rwlock_rdlock(&rwlock);
		cout << "线程" << index << "读取num: " << num << endl;
		pthread_rwlock_unlock(&rwlock);
		sleep(random() % 3 + 1);
	}
	return NULL;
}

void *fun_write(void *arg) {
	int index = (int)(long)arg;

	while(1) {
		pthread_rwlock_wrlock(&rwlock);
		num++;
		cout << "线程" << index << "写入num: " << num << endl;
		pthread_rwlock_unlock(&rwlock);
		sleep(random() % 3 + 1);
	}
}

int main() {
	srandom(getpid());
	pthread_t tid[8];
	int ret = -1;
	ret = pthread_rwlock_init(&rwlock, NULL);
	if(0 != ret) {
		cout << "pthread_rwlock_init failed.." << endl;
		return 1;
	}
	cout << "读写锁初始化成功" << endl;

	for(int i = 0;i < 8;i++) {
		if(i < 6) {
			pthread_create(&tid[i], NULL, fun_read, (void*)(long)i);
		} else {
			pthread_create(&tid[i], NULL, fun_write, (void*)(long)i);
		}
	}

	for(int i = 0;i < 8;i++) {
		pthread_join(tid[i], NULL);
	}
	ret = pthread_rwlock_destroy(&rwlock);
	if(0 != ret) {
		cout << "pthread_rwlock_destroy failed.." << endl;
		return 1;
	}
	cout << "读写锁初始化成功.." << endl;
	return 0;
}
