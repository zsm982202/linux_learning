#include <iostream>
#include <cstdio>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main() {
	//创建套接字
	int sock_fd;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	//连接服务器
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	inet_pton(AF_INET, "192.168.226.1", &addr.sin_addr.s_addr);
	connect(sock_fd, (struct sockaddr*)&addr, sizeof(addr));
	//读写数据
	char buf[1024] = "";
	int ret = fork();
	if(0 > ret) {
		perror("fork");
		return 1;
	}
	if(0 == ret) {
		while(1) {
			int n = read(STDIN_FILENO, buf, sizeof(buf));
			write(sock_fd, buf, n);
		}
	} else {
		while(1) {
			int n = read(sock_fd, buf, sizeof(buf));
			write(STDOUT_FILENO, buf, n);
		}
	}
	//关闭
	close(sock_fd);
	return 0;
}
