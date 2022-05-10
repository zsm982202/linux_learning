#include <iostream>
#include <cstdio>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main() {
	//创建套接字
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	//绑定
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	addr.sin_addr.s_addr = INADDR_ANY;//绑定的是通配地址
	//inet_pton(AF_INET,  "192.168.21.37", &addr.sin_addr.s_addr);
	bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
	//监听
	listen(lfd, 128);
	//提取
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &len);
	char ip[16] = "";
	cout << "new client ip: " << inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, 16) << endl;
	cout << "new client port: " << ntohs(cliaddr.sin_port) << endl;
	//读写
	char buf[1024] = "";
	while(1) {
		bzero(buf, sizeof(buf));
		int n = read(STDIN_FILENO, buf, sizeof(buf));
		write(cfd, buf, n);
		read(cfd, buf, sizeof(buf));
		cout << buf << endl;
	}
	//关闭
	close(lfd);
	close(cfd);
	return 0;
}
