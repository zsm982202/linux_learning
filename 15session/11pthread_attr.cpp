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
	pthread_attr_t attr;

	ret = pthread_attr_init(&attr);
	if(0 != ret) {
		cout << "pthread_attr_init failed.." << endl;
		return 1;
	}
	cout << "线程属性初始化ok.." << endl;

	ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if(0 != ret) {
		cout << "pthread_attr_setdetachstate failed.." << endl;
		return 1;
	}

	ret = pthread_create(&tid, NULL, fun, NULL);
//	ret = pthread_create(&tid, &attr, fun, NULL);
	if(0 != ret) {
		cout << "pthread_create failed.." << endl;
		return 1;
	}

	ret = pthread_join(tid, NULL);
	if(0 != ret) {
		cout << "当前线程为分离状态" << endl;
	} else {
		cout << "当前线程为非分离状态" << endl;
	}

	ret = pthread_attr_destroy(&attr);
	if(0 != ret) {
		cout << "pthread_attr_destroy failed.." << endl;
		return 1;
	}
	cout << "线程属性销毁ok.." << endl;
	cout << "按下任意键退出.." << endl;
	getchar();
	return 0;
}
