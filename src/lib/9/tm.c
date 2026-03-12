/*
 * Time functions for lib9
 * C89/C90 compliant
 *
 * Plan 9 time manipulation functions
 */

#include "lib9.h"
#include <time.h>
#include <string.h>
#include <stdio.h>

/* Days per month */
static char dmsize[] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

/*
 * Check if year is a leap year
 */
static int
isleap(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

/*
 * Normalize Tm structure - validate and fix overflow
 */
vlong
tmnorm(Tm *tm)
{
    vlong t;
    int i, d;

    if (tm == nil) {
        return 0;
    }

    /* Normalize seconds */
    while (tm->sec >= 60) {
        tm->sec -= 60;
        tm->min++;
    }
    while (tm->sec < 0) {
        tm->sec += 60;
        tm->min--;
    }

    /* Normalize minutes */
    while (tm->min >= 60) {
        tm->min -= 60;
        tm->hour++;
    }
    while (tm->min < 0) {
        tm->min += 60;
        tm->hour--;
    }

    /* Normalize hours */
    while (tm->hour >= 24) {
        tm->hour -= 24;
        tm->mday++;
    }
    while (tm->hour < 0) {
        tm->hour += 24;
        tm->mday--;
    }

    /* Normalize months */
    while (tm->mon >= 12) {
        tm->mon -= 12;
        tm->year++;
    }
    while (tm->mon < 0) {
        tm->mon += 12;
        tm->year--;
    }

    /* Normalize days (handle month overflow) */
    while (1) {
        int dim;

        if (tm->mon == 1 && isleap(tm->year + 1900)) {
            dim = 29;
        } else {
            dim = dmsize[tm->mon];
        }

        if (tm->mday > dim) {
            tm->mday -= dim;
            tm->mon++;
            if (tm->mon >= 12) {
                tm->mon -= 12;
                tm->year++;
            }
            continue;
        }

        if (tm->mday < 1) {
            tm->mon--;
            if (tm->mon < 0) {
                tm->mon += 12;
                tm->year--;
            }
            if (tm->mon == 1 && isleap(tm->year + 1900)) {
                tm->mday += 29;
            } else {
                tm->mday += dmsize[tm->mon];
            }
            continue;
        }
        break;
    }

    /* Convert to Unix timestamp */
    {
        struct timespec ts;
        struct tm stm;

        memset(&stm, 0, sizeof(stm));
        stm.tm_sec = tm->sec;
        stm.tm_min = tm->min;
        stm.tm_hour = tm->hour;
        stm.tm_mday = tm->mday;
        stm.tm_mon = tm->mon;
        stm.tm_year = tm->year;
        stm.tm_wday = tm->wday;
        stm.tm_yday = tm->yday;

        t = (vlong)timegm(&stm);
    }

    return t;
}

/*
 * Convert Unix timestamp to Tm structure
 */
Tm*
tmtime(Tm *tm, vlong secs, Tzone *tz)
{
    time_t t = (time_t)secs;
    struct tm *stm;
    const char *zone_name;

    if (tm == nil) {
        return nil;
    }

    if (tz != nil && tz->tzoff == 0) {
        stm = gmtime(&t);  /* UTC */
        zone_name = "GMT";
    } else {
        stm = localtime(&t);  /* Local time */
        zone_name = "local";
    }

    /* Fill Tm structure */
    tm->sec = stm->tm_sec;
    tm->min = stm->tm_min;
    tm->hour = stm->tm_hour;
    tm->mday = stm->tm_mday;
    tm->mon = stm->tm_mon;
    tm->year = stm->tm_year;
    tm->wday = stm->tm_wday;
    tm->yday = stm->tm_yday;

    snprintf(tm->zone, sizeof(tm->zone), "%s",
             tz != nil ? tz->tzname : zone_name);
    tm->tzoff = tz != nil ? tz->tzoff : 0;

    return tm;
}
