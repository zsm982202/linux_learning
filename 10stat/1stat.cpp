#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

#if 0
struct stat {
	dev_t     st_dev;         /* ID of device containing file */
	ino_t     st_ino;         /* inode number */
	mode_t    st_mode;        /* protection */
	nlink_t   st_nlink;       /* number of hard links */
	uid_t     st_uid;         /* user ID of owner */
	gid_t     st_gid;         /* group ID of owner */
	dev_t     st_rdev;        /* device ID (if special file) */
	off_t     st_size;        /* total size, in bytes */
	blksize_t st_blksize;     /* blocksize for filesystem I/O */
	blkcnt_t  st_blocks;      /* number of 512B blocks allocated */
	/* Since Linux 2.6, the kernel supports nanosecond
	   precision for the following timestamp fields.
	   For the details before Linux 2.6, see NOTES. */
	struct timespec st_atim;  /* time of last access */
	struct timespec st_mtim;  /* time of last modification */
	struct timespec st_ctim;  /* time of last status change */
	#define st_atime st_atim.tv_sec      /* Backward compatibility */
	#define st_mtime st_mtim.tv_sec
	#define st_ctime st_ctim.tv_sec
};
#endif

int main() {
	int ret = -1;
	struct stat s;

	ret = stat("txt", &s);
	if(ret == -1) {
		perror("stat:");
		return 1;
	}
	
	printf("std_dev: %llu\n", s.st_dev);
	printf("st_ino: %ld\n", s.st_ino);
	printf("st_nlink: %u\n", s.st_nlink);
	printf("st_uid: %d\n", s.st_uid);
	printf("st_gid: %d\n", s.st_gid);
	printf("st_size: %ld\n", s.st_size);



	return 0;
}
