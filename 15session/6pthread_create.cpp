#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>

using namespace std;

int num = 100;

void *fun(void *arg) {
	int *pn = (int*)arg;
	cout << "before fun num = " << num << " *p = " << *pn << endl;
	num++;
	(*pn)++;
	cout << "after fun num = " << num << " *p = " << *pn << endl;
	return NULL;
}

int main() {
	int ret = -1;
	pthread_t tid;
	memset(&tid, 0, sizeof(tid));
	
	//int *p = NULL;
	//p = malloc((int*)sizeof(int));
	int* p = new int();
	*p = 88;

	ret = pthread_create(&tid, NULL, fun, (void*)p);
	if(0 != ret) {
		cout << "pthread_create failed.." << endl;
		return 1;
	}
	cout << "按下任意键继续.." << endl;
	getchar();
	cout << "main num: " << num << endl;
	cout << "main *p: " << *p << endl;
	delete p;
	return 0;
}
