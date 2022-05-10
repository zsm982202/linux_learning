#include <iostream>
#include <cstdio>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "wrap.h"

using namespace std;

void free_process(int sig) {
	pid_t pid;
	while(1) {
		pid = waitpid(-1, NULL, WNOHANG);
		if(pid <= 0) {
			//<0没有要回收的子进程=0没有子进程退出
			break;
		}
		cout << "child pid: " << pid << endl;
	}
}

int main() {
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGCHLD);
	sigprocmask(SIG_BLOCK, &set, NULL);
	//创建套接字，绑定
	int lfd = tcp4bind(8000, NULL);
	//监听
	Listen(lfd, 128);
	//提取
	//回射
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	while(1) {
		char ip[16];
		//提取连接
		int cfd = Accept(lfd, (struct sockaddr*)&cliaddr, &len);
		cout << "new client ip: " << inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, 16) << endl;
		cout << "new client port: " << ntohs(cliaddr.sin_port) << endl;
		//fork创建子进程
		pid_t pid;
		pid = fork();
		if(pid < 0) {
			perror("fork");
			break;
		}
		if(pid == 0) {
			//关闭lfd
			close(lfd);
			while(1) {
				char buf[1024];
				bzero(buf, sizeof(buf));
				int n = read(cfd, buf, sizeof(buf));
				if(n < 0) {
					perror("read");
					close(cfd);
					exit(0);
				} else if(n == 0) {
					//对方关闭
					cout << "client close" << endl;
					close(cfd);
					exit(0);
				} else {
					cout << buf;
					write(cfd, buf, n);
				}
			}
		} else {
			close(cfd);
			//回收
			//注册信号回调
			struct sigaction act;
			act.sa_flags = 0;
			act.sa_handler = free_process;
			sigemptyset(&act.sa_mask);
			sigaction(SIGCHLD, &act, NULL);
			sigprocmask(SIG_UNBLOCK, &set, NULL);
		}
	}
	//关闭
}
