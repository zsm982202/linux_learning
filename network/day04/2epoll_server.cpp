#include <iostream>
#include <cstdio>
#include <sys/epoll.h>
#include <fcntl.h>
#include "wrap.h"

using namespace std;

int main() {
	//创建套接字
	int lfd = tcp4bind(8000, NULL);
	//监听
	Listen(lfd, 128);
	//创建树
	int epfd = epoll_create(1);
	//将lfd上树
	struct epoll_event ev,evs[1024];
	ev.data.fd = lfd;
	ev.events = EPOLLIN;
	epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
	//while监听
	while(1) {
		int nready = epoll_wait(epfd, evs, 1024, -1);
		cout << "|epoll_wait___" << endl;
		if(nready < 0) {
			perror("epoll_wait");
			break;
		}
		if(nready == 0) {
			continue;
		}
		//有文件描述符变化
		for(int i = 0;i < nready;i++) {
			//判断lfd是读事件变化
			if(evs[i].data.fd == lfd && evs[i].events & EPOLLIN) {
				struct sockaddr_in cliaddr;
				char ip[16];
				socklen_t len = sizeof(cliaddr);
				int cfd = Accept(lfd, (struct sockaddr*)&cliaddr, &len);
				cout << "new client ip: " << inet_ntop(AF_INET,&cliaddr.sin_addr.s_addr, ip, 16) << endl;
				cout << "new client port: " << ntohs(cliaddr.sin_port) << endl;
				//设置cfd为非阻塞
				int flag = fcntl(cfd, F_GETFL);
				flag |= O_NONBLOCK;
				fcntl(cfd, F_SETFL, flag);
				//将cfd上树
				ev.data.fd = cfd;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
			} else if(evs[i].events & EPOLLIN) {
				while(1) {
					char buf[4];
					memset(buf, 0, 4);
					//如果读一个缓冲区，缓冲区没有数据，如果带阻塞就是阻塞等待
					//如果非阻塞就返回-1并将errno设置为EAGAIN
					int n = read(evs[i].data.fd, buf, sizeof(buf));
					if(n < 0) {
						if(errno == EAGAIN) {
							break;
						}
						perror("raed");
						epoll_ctl(epfd, EPOLL_CTL_DEL, evs[i].data.fd, &evs[i]);
						return 1;
					}
					if(n == 0) {
						cout << "client close" << endl;
						close(evs[i].data.fd);
						epoll_ctl(epfd, EPOLL_CTL_DEL, evs[i].data.fd, &evs[i]);
						break;
					} else {
						//cout << "server receive: " << buf;
						write(STDOUT_FILENO, buf, n);
						write(evs[i].data.fd, buf, n);
					}
				}
			}
		}
	}
}
