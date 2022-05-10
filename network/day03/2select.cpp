#include <iostream>
#include <cstdio>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include "wrap.h"

using namespace std;

#define PORT 8888

int main() {
	//创建套接字，绑定
	int lfd = tcp4bind(PORT, NULL);
	//监听
	Listen(lfd, 128);
	int maxfd = lfd;//最大的文件描述符，初始是3
	fd_set oldset, rset;
	FD_ZERO(&oldset);
	FD_ZERO(&rset);
	//将lfd添加到oldset中
	FD_SET(lfd, &oldset);
	while(1) {
		//select监听
		rset = oldset;
		int n = select(maxfd + 1, &rset, NULL, NULL, NULL);
		if(n < 0) {
			perror("select");
			break;
		} else if(n == 0) {
			continue;
		} else {
			//lfd
			if(FD_ISSET(lfd, &rset)) {
				struct sockaddr_in cliaddr;
				socklen_t len = sizeof(cliaddr);
				char ip[16];
				int cfd = Accept(lfd, (struct sockaddr*)&cliaddr, &len);
				cout << "new client ip: " << inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, 16) << endl;
				cout << "new client port: " << ntohs(cliaddr.sin_port) << endl;
				//将cfd添加至oldset中，以下次监听
				FD_SET(cfd, &oldset);
				if(cfd > maxfd)
					maxfd = cfd;
				//如果只有lfd变化continue
				if(--n == 0)
					continue;
			}
			//cfd 遍历lfd之后的文件描述符是否在rset中，如果在则cfd变化
			for(int i = lfd + 1;i <= maxfd;i++) {
				if(FD_ISSET(i, &rset)) {
					char buf[1500] = "";
					int ret = Read(i, buf, sizeof(buf));
					if(ret < 0) {
						perror("Read");
						//出错，将cfd关闭，从oldset中删除cfd
						close(i);
						FD_CLR(i, &oldset);
					} else if(ret == 0) {
						cout << "client close" << endl;
						close(i);
						FD_CLR(i, &oldset);
					} else {
						cout << "buf: " << buf;
						Write(i, buf, ret);
					}
				}
			}
		}
	}
	return 0;
}
