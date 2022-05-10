#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <pthread.h>

using namespace std;

int main() {
	pthread_t tid = 0;

	tid = pthread_self();
	cout << "tid: " << tid << endl;

	if(pthread_equal(tid, pthread_self()))
		cout << "equal.." << endl;
	else
		cout << "not equal.." << endl;

	return 0;
}
