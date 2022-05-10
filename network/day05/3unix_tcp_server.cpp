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
	unlink("sock.s");
	//创建unix流式套接字
	int lfd = socket(AF_UNIX, SOCK_STREAM, 0);
	//绑定
	struct sockaddr_un myaddr;
	myaddr.sun_family = AF_UNIX;
	strcpy(myaddr.sun_path, "sock.s");
	bind(lfd, (struct sockaddr*)&myaddr, sizeof(myaddr));
	//监听
	listen(lfd, 128);
	//提取
	struct sockaddr_un cliaddr;
	socklen_t len_c;
	int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &len_c);
	cout << "new client file: " << cliaddr.sun_path << endl;
	//读写
	char buf[1500] = "";
	while(1) {
		bzero(buf, sizeof(buf));
		int n = recv(cfd, buf, sizeof(buf), 0);
		if(n <= 0) {
			cout << "err or client close" << endl;
			break;
		}
		cout << buf;
		send(cfd, buf, n, 0);
	}
	//关闭
	close(lfd);
	close(cfd);
	return 0;
}
