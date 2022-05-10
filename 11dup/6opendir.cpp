#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

using namespace std;

#if 0
struct dirent {
	ino_t          d_ino;       /* inode number */
	off_t          d_off;       /* not an offset; see NOTES */
	unsigned short d_reclen;    /* length of this record */
	unsigned char  d_type;      /* type of file; not supported
								   by all filesystem types */
	char           d_name[256]; /* filename */
};
#endif

int main() {
	DIR *dir = NULL;
	struct dirent *d = NULL;
	dir = opendir("test");
	if(dir == NULL) {
		perror("opendir");
		return 1;
	}
	cout << "open successfully" << endl;
	
	while(1) {
		d = readdir(dir);
		if(d == NULL) {
			//perror("readdir");
			break;
		}
		cout << "d_type: "  << int(d->d_type) << "  d_name: " << d->d_name << endl;
	}
	
	closedir(dir);
	return 0;
}
