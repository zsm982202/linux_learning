#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <event.h>
#include "wrap.h"

using namespace std;

unordered_map<int, struct event*> cfd_map;

void cfdcb(int cfd, short events, void *arg) {
	char buf[1500] = "";
	int n = Read(cfd, buf, sizeof(buf));
	if(n <= 0) {
		perror("err or close");
		event_del(cfd_map[cfd]);
		cfd_map.erase(cfd);
	} else {
		cout << buf;
		Write(cfd, buf, n);
	}
}

void lfdcb(int lfd, short events, void *arg) {
	struct event_base* base = (struct event_base*)arg;
	//提取新的cfd
	int cfd = Accept(lfd, NULL, NULL);
	//将cfd上树
	struct event* ev = event_new(base, cfd, EV_READ | EV_PERSIST, cfdcb, NULL);
	cfd_map[cfd] = ev;
	event_add(ev, NULL);
}

int main() {
	//创建套接字
	//绑定
	int lfd = tcp4bind(8000, NULL);
	//监听
	Listen(lfd, 128);
	//创建event_base根节点
	struct event_base* base = event_base_new();
	//初始化上树节点
	struct event* ev = event_new(base, lfd, EV_READ | EV_PERSIST, lfdcb, base);
	//上树
	event_add(ev, NULL);
	//监听
	event_base_dispatch(base);//阻塞
	//收尾
	close(lfd);
	event_base_free(base);
	return 0;
}
