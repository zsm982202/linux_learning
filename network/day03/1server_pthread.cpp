#include <iostream>
#include <pthread.h>
#include "wrap.h"

using namespace std;

typedef struct c_info {
	int cfd;
	struct sockaddr_in cliaddr;
} CINFO;

void *client_fun(void *arg) {
	CINFO *info = (CINFO*)arg;
	char ip[16];
	cout << "new client ip: " << inet_ntop(AF_INET, &(info->cliaddr.sin_addr.s_addr), ip, 16) << endl;
	cout << "new client port: " << ntohs(info->cliaddr.sin_port) << endl;
	while(1) {
		char buf[1024] = "";
		int count = 0;
		count = read(info->cfd, buf, sizeof(buf));
		if(count < 0) {
			perror("read");
			break;
		} else if(count == 0) {
			cout << "client close" << endl;
			break;
		} else {
			cout << buf;
			write(info->cfd, buf, count);
		}
	}
	free(info);
	close(info->cfd);
}

int main(int argc, char** argv) {
	if(argc < 2) {
		cout << "argc < 2" << endl << argv[0] << " 8000" << endl;
		return 0;
	}
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	short port = atoi(argv[1]);
	int lfd = tcp4bind(port, NULL);
	Listen(lfd, 128);
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	CINFO *info;
	while(1) {
		int cfd = Accept(lfd, (struct sockaddr*)&cliaddr, &len);
		pthread_t pthid;
		info = (CINFO*)malloc(sizeof(CINFO));
		info->cfd = cfd;
		info->cliaddr = cliaddr;
		pthread_create(&pthid, &attr, client_fun, info);
	}
	return 0;
}
