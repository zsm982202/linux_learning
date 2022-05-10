#include <iostream>
#include <cstdio>
#include <fstream>
#include <cerrno>
#include <cstring>

using namespace std;

int main() {
	ifstream d;
	d.open("d.txt", ios::in);
	if(d)
		cout << "success" << endl;
	else
		cout << "fail" << endl;
	cout << strerror(errno) << endl;
	perror("ifstream open");
	return 0;
}
