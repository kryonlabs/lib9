#include "lib9.h"
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

vlong
seek(int fd, vlong where, int from)
{
	return lseek(fd, where, from);
}
