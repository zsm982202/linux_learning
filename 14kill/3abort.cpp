#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

using namespace std;

int main() {
	int i = 0;
	while(1) {
		cout << "do working " << i++ << endl;
		if(i == 4) {
			abort();
		}
		sleep(1);
	}
	return 0;
}
