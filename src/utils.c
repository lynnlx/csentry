/*
 * Created 190622 lynnl
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "utils.h"

/**
 * @return  Check if given string s1 starts with s2
 * XXX:     Always return 1 if s2 is empty
 *
 * Taken from xnu/osfmk/device/subrs.c#strprefix()
 */
int strprefix(const char *s1, const char *s2)
{
    int c;

    assert_nonnull(s1);
    assert_nonnull(s2);

    while ((c = *s2++) != '\0') {
        if (c != *s1++) return 0;
    }

    return 1;
}

#define ISO_8601_BUFSZ      20

/**
 * Format ISO 8601 datetime without trailing timezone
 */
void format_iso_8601_time(char *str)
{
    time_t now;

    assert_nonnull(str);
    (void) time(&now);

    *str = '\0';
    /* gmtime(3) should never return NULL in such case */
    (void) strftime(str, ISO_8601_BUFSZ, "%Y-%m-%dT%H:%M:%S", gmtime(&now));
}

/**
 * Convert an input UUID string(without hyphens) into binary representation
 * @param in        Input UUID string(must be 32-length long)
 * @param uu        [OUT] Binary UUID representation
 * @return          0 if success  -1 otherwise
 */
int uuid_parse32(const char *in, uuid_t uu)
{
    uuid_string_t str;

    assert_nonnull(in);
    assert_nonnull(uu);

    if (strlen(in) != 32) return -1;
    (void) sprintf(str, "%.*s-%.*s-%.*s-%.*s-%s",
            8, in,
            4, in + 8,
            4, in + 12,
            4, in + 16,
            in + 20);

    return uuid_parse(str, uu);
}

void pmtx_lock(pthread_mutex_t *mtx)
{
    int e;
    assert_nonnull(mtx);
    e = pthread_mutex_lock(mtx);
    assert(e == 0);
}

void pmtx_unlock(pthread_mutex_t *mtx)
{
    int e;
    assert_nonnull(mtx);
    e = pthread_mutex_unlock(mtx);
    assert(e == 0);
}

