#include <iostream>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <signal.h>
#include <dirent.h>
#include "wrap.h"
#include "pub.h"

using namespace std;

#define PORT 8889

void send_header(int cfd, int code, char *info, char *filetype, int length) {
	//发送状态行
	char buf[1024] = "";
	int n = sprintf(buf, "HTTP/1.1 %d %s\r\n", code, info);
	send(cfd, buf, n, 0);
	//发送消息头
	n = sprintf(buf, "Content-Type:%s\r\n", filetype);
	send(cfd, buf, n, 0);
	if(length > 0) {
		n = sprintf(buf, "Content-Length:%d\r\n", length);
		send(cfd, buf, n, 0);
	}
	//空行
	send(cfd, "\r\n", 2, 0);
}

void send_file(int cfd, char *path, struct epoll_event *ev, int epfd, int flag) {
	int fd = open(path, O_RDONLY);
	if(fd < 0) {
		perror("open");
		return;
	}
	int n = 0;
	char buf[1024] = "";
	while(1) {
		n = read(fd, buf, sizeof(buf));
		if(n < 0) {
			perror("read");
			break;
		}
		if(n == 0) {
			break;
		}
		send(cfd, buf, n, 0);
	}
	if(flag == 1) {
		close(fd);
		epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, ev);
	}
}

int is_begin_with(const char *str1, char *str2) {
	if(str1 == NULL || str2 == NULL)
		return -1;
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	return 0;
}

void send_file1(int cfd, char *path, struct epoll_event *ev, int epfd, int flag) {
	int fd = open(path, O_RDONLY);
	if(fd < 0) {
		perror("open");
		return;
	}
	int n = 0;
	char buf[1024] = "";
	while(1) {
		n = Readline(fd, buf, sizeof(buf));
		if(n < 0) {
			perror("read");
			break;
		}
		if(n == 0) {
			break;
		}
		send(cfd, buf, n, 0);
		string s1 = buf;
		string s2 = "  var ret = [];";
		
		if(s1.find(s2) == 0) {
			int len = sprintf(buf, "  ret[0] = 1;\n");
			cout << buf;
			send(cfd, buf, len, 0);
		}
	}
	if(flag == 1) {
		close(fd);
		epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, ev);
	}
}

void read_client_request(int epfd, struct epoll_event *ev) {
	//读取请求（先读取一行，再把其他行读取，扔掉）
	char buf[1024] = "";
	char temp[1024] = "";
	int n = Readline(ev->data.fd, buf, sizeof(buf));
	if(n <= 0) {
		//perror("Readline");
		cout << "close or err" << endl;
		epoll_ctl(epfd, EPOLL_CTL_DEL, ev->data.fd, ev);
		close(ev->data.fd);
		return;
	}
	cout << buf;
	int ret = 0;
	while((ret = Readline(ev->data.fd, temp, sizeof(temp))) > 0);
	cout << "read ok" << endl;
	char method[256] = "";
	char content[256] = "";
	char protocol[256] = "";
	sscanf(buf, "%[^ ] %[^ ] %[^ \r\n]", method, content, protocol);
	cout << "[" << method << "]" << endl;
	cout << "[" << content << "]" << endl;
	cout << "[" << protocol << "]" << endl;
	if(strcasecmp(method, "get") == 0) {
		char *strfile = content + 1;
		strdecode(strfile, strfile);
		if(*strfile == 0) {
			strfile = (char*)"./";
		}
		//判断请求的文件在不在
		struct stat s;
		if(stat(strfile, &s) < 0) {
			cout << "file not found" << endl;
			send_header(ev->data.fd, 404, "NOT FOUND", get_mime_type("*.html"), 0);
			send_file1(ev->data.fd, "error.html", ev, epfd, 1);
		} else {
			//请求的是一个普通文件
			if(S_ISREG(s.st_mode)) {
				cout << "reg" << endl;
				//先发送报头（状态行 消息头 空行）
				send_header(ev->data.fd, 200, "OK", get_mime_type(strfile), s.st_size);
				send_file1(ev->data.fd, strfile, ev, epfd, 1);
			} else if(S_ISDIR(s.st_mode)) {//请求的是一个目录
				cout << "dir" << endl;
				send_header(ev->data.fd, 200, "OK", get_mime_type(".html"), s.st_size);
				send_file(ev->data.fd, "dir_header.html", ev, epfd, 0);
				struct dirent **mylist = NULL;
				int n = scandir(strfile, &mylist, NULL, alphasort);
				char buf[1024] = "";
				for(int i = 0;i < n;i++) {
					char c[2] = "";
					if(mylist[i]->d_type == DT_DIR)
						c[0] = '/';
					int len = sprintf(buf, "<li><a href=\"%s%s\">%s</a></li>", mylist[i]->d_name, c, mylist[i]->d_name);
					send(ev->data.fd, buf, len, 0);
//					cout << mylist[i]->d_name << endl;
					free(mylist[i]);
				}
				free(mylist);
				send_file(ev->data.fd, "dir_tail.html", ev, epfd, 1);
			}
		}
	}
}

int main() {
	signal(SIGPIPE, SIG_IGN);
	//切换工作目录
	char pwd_path[256] = "";
	char *path = getenv("PWD");
	strcpy(pwd_path, path);
	strcat(pwd_path, "/web-http");
	chdir(pwd_path);
	//创建套接字
	int lfd = tcp4bind(PORT, NULL);
	//监听
	Listen(lfd, 128);
	//创建树
	int epfd = epoll_create(1);
	//将fd上树
	struct epoll_event ev, evs[1024];
	ev.data.fd = lfd;
	ev.events = EPOLLIN;
	epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
	//循环监听
	while(1) {
		int nready = epoll_wait(epfd, evs, 1024, -1);
		if(nready < 0) {
			perror("epoll_wait");
			break;
		}
		for(int i = 0;i < nready;i++) {
			//判断是否是lfd
			if(evs[i].data.fd == lfd && evs[i].events & EPOLLIN) {
				struct sockaddr_in cliaddr;
				char ip[16] = "";
				socklen_t len = sizeof(cliaddr);
				int cfd = Accept(lfd, (struct sockaddr*)&cliaddr, &len);
				cout << "new client ip: " << inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, 16) << endl;;
				cout << "new client port: " << ntohs(cliaddr.sin_port) << endl;
				int flag = fcntl(cfd, F_GETFL);
				flag |= O_NONBLOCK;
				fcntl(cfd, F_SETFL, flag);
				ev.data.fd = cfd;
				ev.events = EPOLLIN;
				epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
			} else if(evs[i].events & EPOLLIN) {
				read_client_request(epfd, &evs[i]);
			}
		}
	}
	//收尾
	return 0;
}
