#include <iostream>
#include <arpa/inet.h>

using namespace std;

int main() {
	cout << sizeof(int) << endl;
	cout << sizeof(long) << endl;
	cout << sizeof(long long) << endl;
	
	char buf[4] = {192, 168, 131, 134};
	int num = *(int*)buf;
	int ret = htonl(num);
	unsigned char *p = (unsigned char*)&ret;
	for(int i = 0;i < 4;i++) {
		cout << (int)*(p + i) << " ";
	}
	cout << endl;
	num = ntohl(ret);
	p = (unsigned char*)&num;
	for(int i = 0;i < 4;i++) {
		cout << (int)*(p + i) << " ";
	}
	cout << endl;
	
	unsigned short a = 0x0112;
	unsigned short b = htons(a);
	cout << hex << b << endl;
	cout << hex << ntohs(b) << endl;

	return 0;
}
