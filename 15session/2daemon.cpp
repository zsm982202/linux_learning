#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

int main() {
	pid_t pid = -1;
	int ret = -1;
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
		system("date >> /tmp/txt.log");
		sleep(1);
	}
	return 0;
}
