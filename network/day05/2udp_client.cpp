#include <iostream>
#include <cstdio>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>

using namespace std;

int main() {
	//创建套接字
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	//绑定
	struct sockaddr_in myaddr;
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(8000);
	myaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int ret = bind(fd, (struct sockaddr*)&myaddr, sizeof(myaddr));
	if(ret < 0) {
		perror("bind");
		return 1;
	}
	//读写
	char buf[1500] = "";
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	struct sockaddr_in dstaddr;
	dstaddr.sin_family = AF_INET;;
	dstaddr.sin_port = htons(8888);
	dstaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	while(1) {
		memset(buf, 0, sizeof(buf));
		read(STDIN_FILENO, buf, sizeof(buf));
		sendto(fd, buf, sizeof(buf), 0, (struct sockaddr*)&dstaddr, sizeof(dstaddr));
		int n = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*)&cliaddr, &len);
		if(n < 0) {
			perror("recvfrom");
			break;
		}
		cout << buf;
	}
	//关闭
	return 0;
}
