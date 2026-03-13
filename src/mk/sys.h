#include <lib9.h>
#include <bio.h>
#include <regexp.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/* POSIX compatibility */
#define seek lseek
#define remove unlink
#define nelem(x) (sizeof(x)/sizeof((x)[0]))
#define create(name, mode, perm)	open(name, mode|O_CREAT, perm)
#define exits(x)	exit(x && *(char*)x ? 1 : 0)
typedef uintptr_t uintptr;
