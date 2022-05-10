#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <sys/epoll.h>

using namespace std;

int main() {
	int fd[2];
	pipe(fd);
	pid_t pid = -1;
	pid = fork();
	if(pid < 0) {
		perror("fork");
		return 1;
	}
	if(pid == 0) {
		close(fd[0]);
		char buf[5];
		char ch = 'a';
		while(1) {
			memset(buf, ch++, sizeof(buf));
			write(fd[1], buf, 5);
			sleep(2);
		}
	} else {
		close(fd[1]);
		int epfd = epoll_create(1);
		struct epoll_event ev, evs[1];
		ev.data.fd = fd[0];
		ev.events = EPOLLIN;
		epoll_ctl(epfd, EPOLL_CTL_ADD, fd[0], &ev);
		while(1) {
			int n = epoll_wait(epfd, evs, 1, -1);
			if(n == 1) {
				char buf[5] = "";
				int ret = read(fd[0], buf, sizeof(buf));
				if(ret <= 0) {
					close(fd[0]);
					epoll_ctl(epfd, EPOLL_CTL_DEL, fd[0], &ev);
					break;
				} else {
					cout << "read: " << buf << endl;
				}
			}
		}
	}
}
