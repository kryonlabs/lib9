#ifndef _FCALL_H_
#define _FCALL_H_

#include "lib9.h"

/* Message types - 9P2000 */
#define Tversion 100
#define Rversion 101
#define Tauth 102
#define Rauth 103
#define Tattach 104
#define Rattach 105
#define Terror 106
#define Rerror 107
#define Tflush 108
#define Rflush 109
#define Twalk 110
#define Rwalk 111
#define Topen 112
#define Ropen 113
#define Tcreate 114
#define Rcreate 115
#define Tread 116
#define Rread 117
#define Twrite 118
#define Rwrite 119
#define Tclunk 120
#define Rclunk 121
#define Tremove 122
#define Rremove 123
#define Tstat 124
#define Rstat 125
#define Twstat 126
#define Rwstat 127

/* Special tag value */
#define NOTAG (uint16_t)~0
#define NOFID (uint32_t)~0

/* Qid type bits */
#define QTDIR 0x80
#define QTAPPEND 0x40
#define QTEXCL 0x20
#define QTAUTH 0x08
#define QTTMP 0x04
#define QTFILE 0x00

/* Dir mode bits */
#define DMDIR 0x80000000
#define DMAPPEND 0x40000000
#define DMEXCL 0x20000000
#define DMMOUNT 0x10000000
#define DMAUTH 0x08000000
#define DMTMP 0x04000000
#define DMREAD 0x4
#define DMWRITE 0x2
#define DMEXEC 0x1

/* Size constants */
#define BIT8SZ 1
#define BIT16SZ 2
#define BIT32SZ 4
#define BIT64SZ 8
#define QIDSZ (BIT8SZ + BIT32SZ + BIT64SZ)

/* STATFIXLEN includes leading 16-bit count */
/* The count, however, excludes itself; total size is BIT16SZ+count */
#define STATFIXLEN (BIT16SZ + QIDSZ + 5*BIT16SZ + 4*BIT32SZ + 1*BIT64SZ)
#define OREAD 0
#define OWRITE 1
#define ORDWR 2
#define OEXEC 3
#define OTRUNC 16
#define OCEXEC 32
#define ORCLOSE 64
#define OEXCL 0x1000

/* Maximum walk elements */
#define MAXWELEM 16

/* Structures */
typedef struct Qid {
    uint8_t type;
    uint32_t vers;
    uint64_t path;
} Qid;

typedef struct Dir {
    uint16_t type;
    uint32_t dev;
    Qid qid;
    uint32_t mode;
    uint32_t atime;
    uint32_t mtime;
    uint64_t length;
    char *name;
    char *uid;
    char *gid;
    char *muid;
} Dir;

typedef struct Fcall {
    uint8_t type;
    uint16_t tag;
    uint16_t oldtag;  /* Tflush */
    uint32_t fid;
    uint32_t msize;
    char *version;
    char *ename;  /* Rerror */
    Qid qid;  /* Rattach, Ropen, Rcreate */
    uint32_t iounit;  /* Ropen, Rcreate */
    Qid aqid;  /* Rauth */
    uint32_t afid;  /* Tauth, Tattach */
    char *uname;  /* Tauth, Tattach */
    char *aname;  /* Tauth, Tattach */
    uint32_t perm;  /* Tcreate */
    char *name;  /* Tcreate */
    uint8_t mode;  /* Tcreate, Topen */
    uint32_t newfid;  /* Twalk */
    uint16_t nwname;  /* Twalk */
    char *wname[MAXWELEM];  /* Twalk */
    uint16_t nwqid;  /* Rwalk */
    Qid wqid[MAXWELEM];  /* Rwalk */
    uint64_t offset;  /* Tread, Twrite */
    uint32_t count;  /* Tread, Twrite, Rread */
    char *data;  /* Twrite, Rread */
    uint16_t nstat;  /* Twstat, Rstat */
    uchar *stat;  /* Twstat, Rstat */
} Fcall;

/* Function prototypes - implemented in lib9 */
uint convM2S(uchar*, uint, Fcall*);
uint convS2M(Fcall*, uchar*, uint);
uint sizeS2M(Fcall*);
uint convD2M(Dir*, uchar*, uint);
uint convM2D(uchar*, uint, Dir*, char*);
uint sizeD2M(Dir*);

#endif
