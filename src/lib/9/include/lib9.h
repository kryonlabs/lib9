#ifndef _LIB9_H_
#define _LIB9_H_

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

/* Basic types */
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef long intptr;
typedef unsigned long uintptr;
typedef int64_t vlong;
typedef uint64_t uvlong;
#define nil ((void*)0)

/* Utility macros */
#define USED(x) ((void)(x))  /* Mark variable as used to suppress warnings */
#define nelem(x) (sizeof(x)/sizeof((x)[0]))  /* Number of elements in array */

/* Endianness macros - for direct buffer access */
#define GBIT8(p) (*(uint8_t*)(p))
#define GBIT16(p) ((uint16_t)((uint8_t*)(p))[0] | ((uint16_t)((uint8_t*)(p))[1] << 8))
#define GBIT32(p) ((uint32_t)GBIT16(p) | ((uint32_t)GBIT16((p)+2) << 16))
#define GBIT64(p) ((uint64_t)GBIT32(p) | ((uint64_t)GBIT32((p)+4) << 32))

#define PBIT8(p, v) (*(uint8_t*)(p) = (uint8_t)(v))
#define PBIT16(p, v) (PBIT8((p), (v)), PBIT8((p)+1, (v) >> 8))
#define PBIT32(p, v) (PBIT16((p), (v)), PBIT16((p)+2, (v) >> 16))
#define PBIT64(p, v) (PBIT32((p), (v)), PBIT32((p)+4, (v) >> 32))

/* Size constants */
#define BIT8SZ 1
#define BIT16SZ 2
#define BIT32SZ 4
#define BIT64SZ 8
#define QIDSZ (BIT8SZ + BIT32SZ + BIT64SZ)

/* Error buffer size */
#define ERRMAX 128

/* Open constants (Plan 9 compatibility) */
#define OREAD 0
#define OWRITE 1
#define ORDWR 2
#define OEXEC 3
#define OTRUNC 16
#define OCEXEC O_CLOEXEC  /* Close on exec */
#define ORCLOSE O_CLOEXEC /* Remove on close */

/* Timezone structure */
typedef struct Tzone Tzone;
struct Tzone {
    char *tzname;      /* Timezone name */
    int tzoff;         /* Offset from UTC in seconds */
};

/* Time structure */
typedef struct Tm Tm;
struct Tm {
    int sec;           /* Seconds */
    int min;           /* Minutes */
    int hour;          /* Hours */
    int mday;          /* Day of month */
    int mon;           /* Month */
    int year;          /* Year */
    int wday;          /* Day of week */
    int yday;          /* Day of year */
    char zone[16];     /* Timezone name */
    int tzoff;         /* Timezone offset */
};

/* Global variables */
extern char *argv0;  /* Program name */

/* Error string functions */
void rerrstr(char *err, uint n);
int errstr(char *buf, uint n);
void werrstr(char *fmt, ...);

/* Process exit */
void sysfatal(char *fmt, ...);
void exits(char*);

/* String functions - strdup provided by plan9port, others we implement */
char* strecpy(char*, char*, char*);
char* cleanname(char*);
long readn(int, void*, long);
int tokenize(char*, char**, int);
int cistrcmp(char*, char*);
int cistrncmp(char*, char*, int);
char* cistrstr(char*, char*);

/* Include formatting support (provides print, snprint, etc.) */
#include "fmt.h"

/* Time functions */
extern Tzone* tzload(const char*);
extern vlong tmnorm(Tm*);
extern char* tmfmt(Tm*, const char*);
extern Tm* tmtime(Tm*, vlong, Tzone*);
extern void tmfmtinstall(void);

#endif
