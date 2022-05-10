#include <iostream>
using namespace std;

void fun() {
	for(int i = 0;i < 10;i++)
		cout << "fun=>" << i << endl;
}

int main(int argc, char* argv[]) {
	for(int i = 0;i < argc;i++) {
		cout << argv[i] << endl;
	}
	fun();
	cout << "hello world!" << endl;
	return 0;
}
