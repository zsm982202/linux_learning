#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int num = 100;

void *fun1(void *arg) {
	for(int i = 'A';i <= 'Z';i++) {
		putchar(i);
		fflush(stdout);
		usleep(100000);//100ms
	}
	return NULL;
}

void *fun2(void *arg) {
	for(int i = 'a';i <= 'z';i++) {
		putchar(i);
		fflush(stdout);
		usleep(100000);//100ms
	}
	return NULL;
}

int main() {
	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, fun1, NULL);
	pthread_create(&tid2, NULL, fun2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	cout << endl << "main thread exit.." << endl;
	
	return 0;
}
