#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main() {
	pid_t pid = -1;
	int ret = -1;
	int status = -1;

	pid = fork();
	if(pid == -1) {
		perror("fork");
		return 1;
	}

	if(pid == 0) {
		//子进程
		for(int i = 0;i < 5;i++) {
			cout << "子进程 " << i << " pid: " << getpid() << endl;
			sleep(1);
		}
		exit(10);
	}
	//父进程
	cout << "父进程等待子进程退出，回收其资源" << endl;
	ret = waitpid(-1, &status, WNOHANG);
	//ret = wait(&status);
	if(ret == -1) {
		perror("wait");
		return 1;
	}
	cout << "父进程回收了子进程资源" << endl;
	if(WIFEXITED(status))
		cout << "子进程退出状态码: " << WEXITSTATUS(status) << endl;
	else if(WIFSIGNALED(status))
		cout << "子进程被信号" << WTERMSIG(status) << "杀死了" << endl;
	else if(WIFSTOPPED(status))
		cout << "子进程被信号" << WSTOPSIG(status) << "暂停" << endl;

	return 0;
}
