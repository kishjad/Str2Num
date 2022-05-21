#ifndef STRCONVERT_H
#define STRCONVERT_H

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <optional>
#include <string>
#include <type_traits>

typedef enum {
    STR2NUM_SUCCESS,
    STR2NUM_OVERFLOW,
    STR2NUM_UNDERFLOW,
    STR2NUM_INCONVERTIBLE
} str2num_errno;

str2num_errno str2int(int *out, const char *s, char* endptr, int base) {
    if (s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    long l = strtol(s, &endptr, base);
    /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
    if (l > INT_MAX || (errno == ERANGE && l == LONG_MAX))
        return STR2NUM_OVERFLOW;
    if (l < INT_MIN || (errno == ERANGE && l == LONG_MIN))
        return STR2NUM_UNDERFLOW;
    if (*endptr != '\0')
        return STR2NUM_INCONVERTIBLE;
    *out = l;
    return STR2NUM_SUCCESS;
}

str2num_errno str2uint(unsigned int *out, char *s, char* endptr, int base) {
    char* end = endptr;
    if (s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    unsigned long int l = strtoul(s, &end, base);
    /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
    if (errno == ERANGE && l == ULONG_MAX)
        return STR2NUM_OVERFLOW;
    if (errno == ERANGE && l == 0)
        return STR2NUM_UNDERFLOW;
    if (*end != '\0')
        return STR2NUM_INCONVERTIBLE;
    *out = l;
    return STR2NUM_SUCCESS;
}


str2num_errno str2lglgint(long long int *out, char *s, char* endptr, int base) {
    char *end = endptr;
    if (s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    long long int l = strtoll(s, &end, base);
    /* Both checks are needed because l == LONG_MAX or l == LLONG_MIN is possible. */
    if (errno == ERANGE && l == LLONG_MAX)
        return STR2NUM_OVERFLOW;
    else if (errno == ERANGE && l == LLONG_MIN)
        return STR2NUM_UNDERFLOW;
    else if (*end != '\0')
        return STR2NUM_INCONVERTIBLE;
    *out = l;
    return STR2NUM_SUCCESS;
}

str2num_errno str2lglguint(long long unsigned int *out, char *s, char* endptr, int base) {
    char* end = endptr;
    if (s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    long long unsigned int l = strtoull(s, &end, base);
    /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
    if (errno == ERANGE && l == ULLONG_MAX)
        return STR2NUM_OVERFLOW;
    else if (errno == ERANGE && l == 0)
        return STR2NUM_UNDERFLOW;
    else if (*end != '\0')
        return STR2NUM_INCONVERTIBLE;
    *out = l;
    return STR2NUM_SUCCESS;
}

str2num_errno str2doub(double *out, char *s) {
    if (s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    char *err;
    *out = strtod(s, &err);
    if (*err == 0) { /* very probably ok */
        return STR2NUM_SUCCESS;
    }
    else{
        return STR2NUM_INCONVERTIBLE;
    }
}

str2num_errno str2float(float *out, char *s) {
    if (s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    char *err;
    *out = strtof(s, &err);
    if (*err == 0) { /* very probably ok */
        return STR2NUM_SUCCESS;
    }
    else{
        return STR2NUM_INCONVERTIBLE;
    }
}

#endif
