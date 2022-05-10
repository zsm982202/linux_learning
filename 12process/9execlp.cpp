#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main() {
	cout << "hello itcast" << endl;

//	execlp("ls", "ls", "-l", "/home", NULL);
//	execl("/bin/ls", "ls", "-l", "/home", NULL);
//	execlp("./8zombie", "8zombie", NULL);
//	execl("./8zombie", "8zombie", NULL);
	char *envp[] = {(char*)"ADDR=BEIJING", NULL};
	char *argvs[] = {(char*)"ls", (char*)"-l", (char*)"/home", NULL};
	execvpe("ls", argvs, envp);
	cout << "hello world" << endl;

	return 0;
}
