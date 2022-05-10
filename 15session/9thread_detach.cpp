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
	return NULL;
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

	ret = pthread_join(tid, NULL);
	if(0 != ret) {
		cout << "pthread_join failed.." << endl;
//		return 1;
	} else {
		cout << "pthread_join ok.." << endl;
	}
	cout << "按下任意键退出" << endl;
	getchar();
	cout << "main exit.." << endl;
	return 0;
}
