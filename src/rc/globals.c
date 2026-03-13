#include "rc.h"
#include "io.h"
#include "exec.h"
#include "fns.h"
#include "getflags.h"

/* Global variable definitions */

var *gvar[NVAR];		/* hash for globals */
int mypid;
char **argp;
char **args;
int nerror;			/* number of errors encountered during compilation */
int doprompt = 1;		/* is it time for a prompt? */
int ndot;			/* How many dot commands have we executed? */
int lastc;
int lastword;
char *promptstr;
char tok[NTOK + UTFmax];
tree *cmdtree;
io *err;
thread *runq;
code *codebuf;			/* compiler output */
int ntrap;			/* number of outstanding traps */
int trap[NSIG];			/* number of outstanding traps per type */
int eflagok;			/* kludge flag so that -e doesn't exit in startup */
int havefork = 1;
char *Rcmain = "/usr/lib/rcmain";
char *Fdprefix = "/dev/fd/";
