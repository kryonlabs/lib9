#include "lib9.h"
#include <stdlib.h>
#include <unistd.h>

void
exits(char *s)
{
	if(s == 0 || *s == 0)
		exit(0);
	exit(1);
}

void
_exits(char *s)
{
	if(s == 0 || *s == 0)
		_exit(0);
	_exit(1);
}
