/*
 * Time formatting functions for lib9
 * C89/C90 compliant
 *
 * Plan 9 time formatting functions
 */

#include "lib9.h"
#include <stdio.h>
#include <string.h>

char*
tmfmt(Tm *tm, const char *fmt)
{
    static char buf[256];
    char *p = buf;

    if (tm == nil || fmt == nil) {
        return nil;
    }

    /* Simple format string parsing */
    while (*fmt && p < buf + sizeof(buf) - 1) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
            case 'Y':  /* Year */
                p += snprintf(p, buf + sizeof(buf) - p, "%04d", tm->year + 1900);
                break;
            case 'M':  /* Month */
                p += snprintf(p, buf + sizeof(buf) - p, "%02d", tm->mon + 1);
                break;
            case 'D':  /* Day */
                p += snprintf(p, buf + sizeof(buf) - p, "%02d", tm->mday);
                break;
            case 'h':  /* Hour */
                p += snprintf(p, buf + sizeof(buf) - p, "%02d", tm->hour);
                break;
            case 'm':  /* Minute */
                p += snprintf(p, buf + sizeof(buf) - p, "%02d", tm->min);
                break;
            case 's':  /* Second */
                p += snprintf(p, buf + sizeof(buf) - p, "%02d", tm->sec);
                break;
            case 'z':  /* Timezone */
                p += snprintf(p, buf + sizeof(buf) - p, "%s", tm->zone);
                break;
            case '\0':  /* Trailing % */
                *p++ = '%';
                goto done;
            default:
                *p++ = *fmt;
                break;
            }
            fmt++;
        } else {
            *p++ = *fmt++;
        }
    }
done:
    *p = '\0';

    return buf;
}

void
tmfmtinstall(void)
{
    /* Install custom time formatters for fmtprint */
    /* This integrates with the fmt library in lib9 */
    /* TODO: Implement proper integration with fmt library */
}
