#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main() {
	fork();
	cout << "hello world!" << "pid: " << getpid() << " ppid: " << getppid() << endl;
	
	return 0;
}
