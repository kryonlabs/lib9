#include "lib9.h"
#include "fcall.h"

void
nulldir(Dir *d)
{
	memset(d, ~0, sizeof(Dir));
	d->name = d->uid = d->gid = d->muid = "";
}
