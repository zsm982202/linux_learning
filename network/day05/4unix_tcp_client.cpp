#include <iostream>
#include <cstdio>
#include <cstddef>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>

using namespace std;

int main() {
	unlink("sock.c");
	//创建unix流式套接字
	int cfd = socket(AF_UNIX, SOCK_STREAM, 0);
	//绑定
	struct sockaddr_un myaddr;
	myaddr.sun_family = AF_UNIX;
	strcpy(myaddr.sun_path, "sock.c");
	int ret = bind(cfd, (struct sockaddr*)&myaddr, sizeof(myaddr));
	if(ret < 0) {
		perror("bind");
		return 1;
	}
	//连接
	struct sockaddr_un seraddr;
	seraddr.sun_family = AF_UNIX;
	strcpy(seraddr.sun_path, "sock.s");
	connect(cfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
	//读写
	char buf[1500] = "";
	while(1) {
		bzero(buf, sizeof(buf));
		int n = read(STDIN_FILENO, buf, sizeof(buf));
		send(cfd, buf, n, 0);
		bzero(buf, sizeof(buf));
		n = recv(cfd, buf, sizeof(buf), 0);
		if(n <= 0) {
			cout << "err or client close" << endl;
			break;
		}
		cout << buf;
	}
	//关闭
	close(cfd);
	return 0;
}
