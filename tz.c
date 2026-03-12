/*
 * Timezone functions for lib9
 * C89/C90 compliant
 *
 * Plan 9 timezone support
 */

#include "lib9.h"
#include <time.h>
#include <string.h>

static Tzone tz_local;
static Tzone tz_gmt;
static int tz_inited = 0;

static void
tzinit(void)
{
    if (tz_inited)
        return;

    /* Initialize GMT timezone */
    tz_gmt.tzname = "GMT";
    tz_gmt.tzoff = 0;

    /* Initialize local timezone */
    tz_local.tzname = "local";
    time_t t = time(nil);
    struct tm *tm = localtime(&t);
#ifdef __GLIBC__
    tz_local.tzoff = tm->tm_gmtoff;
#else
    /* Fallback: calculate offset manually */
    struct tm *gmt = gmtime(&t);
    tz_local.tzoff = (int)(mktime(tm) - mktime(gmt));
#endif

    tz_inited = 1;
}

Tzone*
tzload(const char *name)
{
    tzinit();

    if (strcmp(name, "local") == 0) {
        return &tz_local;
    }

    if (strcmp(name, "GMT") == 0 || strcmp(name, "UTC") == 0) {
        return &tz_gmt;
    }

    /* Try loading from /sys/share/zoneinfo or /etc/localtime */
    /* For now, return nil for unknown timezones */
    /* TODO: Implement proper timezone loading from zoneinfo files */
    return nil;
}
