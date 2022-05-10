#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>

using namespace std;

int main() {
	pid_t pid = -1;
	int ret = -1;
	time_t t = -1;
	struct tm *pT = NULL;
	//1.创建子进程，父进程退出
	pid = fork();
	if(-1 == pid) {
		perror("fork");
		return 1;
	}

	if(pid > 0) {
		exit(0);
	}
	//2.创建新的会话，完全脱离控制终端
	pid = setsid();
	if(-1 == pid) {
		perror("setsid");
		return 1;
	}
	//3.改变当前工作目录
	ret = chdir("/");
	if(-1 == ret) {
		perror("chdir");
		return 1;
	}
	//4.设置权限掩码
	umask(0);
	//5.关闭文件描述符
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	//6.执行核心的任务
	//每隔一秒输出当前时间到/tmp/txt.log
	while(1) {
		t = time(NULL);
		pT = localtime(&t);
		if(NULL == pT) {
			cout << "localtime failed.." << endl;
			return 1;
		}
		string s = "date >> ~/linux/15session/log/";
		string str = to_string(pT->tm_year + 1900) + "-" + to_string(pT->tm_mon + 1) + "-" + 
			to_string(pT->tm_mday) + "-" + to_string(pT->tm_hour) + "-" + 
			to_string(pT->tm_min) + "-" + to_string(pT->tm_sec);
		s += str;
		s += ".log";
		system(s.c_str());
		sleep(1);
	}
	return 0;
}
