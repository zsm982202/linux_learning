#include <iostream>
#include <arpa/inet.h>

using namespace std;

int main() {
	char buf[] = "192.168.1.4";
	unsigned int num = 0;
	int ret = inet_pton(AF_INET, buf, &num);
	unsigned char *p = (unsigned char*)&num;
	for(int i = 0;i < 4;i++) {
		cout << (int)*(p + i) << " ";
	}
	cout << endl;
	char ip[16];
	cout << inet_ntop(AF_INET, &num, ip, 16) << endl;
	cout << ip << endl;
	return 0;
}
