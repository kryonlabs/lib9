# lib9 - Plan 9 API library for TaijiOS
# Copied from Inferno, configured for Linux

<../mkfile.common

LIB=liblib9.a
LIBDIR=$ROOT/lib

# Common files (all platforms)
COMMON=\
	convD2M.$O\
	convM2D.$O\
	convM2S.$O\
	convS2M.$O\
	fcallfmt.$O\
	runestrchr.$O\
	runestrlen.$O\
	runetype.$O\
	rune.$O\
	strtoll.$O\
	strtoull.$O\

# Core library files
CORE=\
	argv0.$O\
	charstod.$O\
	cistrcmp.$O\
	cistrncmp.$O\
	cistrstr.$O\
	cleanname.$O\
	create.$O\
	dirwstat.$O\
	dofmt.$O\
	dorfmt.$O\
	errfmt.$O\
	exits.$O\
	fmt.$O\
	fmtfd.$O\
	fmtlock.$O\
	fmtprint.$O\
	fmtquote.$O\
	fmtrune.$O\
	fmtstr.$O\
	fmtvprint.$O\
	fprint.$O\
	getfields.$O\
	nulldir.$O\
	pow10.$O\
	print.$O\
	readn.$O\
	rerrstr.$O\
	runeseprint.$O\
	runesmprint.$O\
	runesnprint.$O\
	runevseprint.$O\
	runevsmprint.$O\
	runevsnprint.$O\
	seek.$O\
	seprint.$O\
	smprint.$O\
	snprint.$O\
	sprint.$O\
	strdup.$O\
	strecpy.$O\
	sysfatal.$O\
	tokenize.$O\
	u16.$O\
	u32.$O\
	u64.$O\
	utflen.$O\
	utfnlen.$O\
	utfrrune.$O\
	utfrune.$O\
	utfecpy.$O\
	vfprint.$O\
	vseprint.$O\
	vsmprint.$O\
	vsnprint.$O\

# POSIX-specific files (Linux)
POSIX=\
	dirstat-posix.$O\
	errstr-posix.$O\
	getuser-posix.$O\
	getcallerpc-Linux-amd64.$O\
	getwd-posix.$O\
	sbrk-posix.$O\
	isnan-posix.$O\
	mallocz.$O\

OFILES=$COMMON $CORE $POSIX

all:V: $LIB

install:V: $LIB
	mkdir -p $LIBDIR
	cp $LIB $LIBDIR/

$LIB: $OFILES
	ar rvc $target $OFILES

%.$O: %.c
	$CC $CFLAGS -Iinclude -c $stem.c -o $target

clean:V:
	rm -f $OFILES $LIB

# Dependencies (now using local headers)
convD2M.$O: include/fcall.h
convM2D.$O: include/fcall.h
convM2S.$O: include/fcall.h
convS2M.$O: include/fcall.h
fcallfmt.$O: include/fcall.h
