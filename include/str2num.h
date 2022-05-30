#ifndef STRCONVERT_H
#define STRCONVERT_H

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#if (defined(__GNUC__) || defined(__clang__))
#define s2n_likely(x)      __builtin_expect(!!(x), 1)
#define s2n_unlikely(x)    __builtin_expect(!!(x), 0)
#else
#define s2n_likely(x)      (x)
#define s2n_unlikely(x)    (x)
#endif

typedef enum {
    STR2NUM_SUCCESS,
    STR2NUM_OVERFLOW,
    STR2NUM_UNDERFLOW,
    STR2NUM_INCONVERTIBLE
} str2num_errno;

str2num_errno str2int(int *out, const char *s, char** endptr = nullptr, int base=10) {
    if (s == nullptr || s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    long l = strtol(s, endptr, base);
    /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
    if (s2n_unlikely(l > INT_MAX || (errno == ERANGE && l == LONG_MAX)))
        return STR2NUM_OVERFLOW;
    if (s2n_unlikely(l < INT_MIN || (errno == ERANGE && l == LONG_MIN)))
        return STR2NUM_UNDERFLOW;
    if (s2n_unlikely(endptr!=nullptr && **endptr != '\0'))
        return STR2NUM_INCONVERTIBLE;
    *out = l;
    return STR2NUM_SUCCESS;
}

str2num_errno str2uint(unsigned int *out, const char *s, char** endptr = nullptr, int base=10) {
    if (s == nullptr || s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    unsigned long int l = strtoul(s, endptr, base);
    /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
    if (s2n_unlikely(errno == ERANGE && l == ULONG_MAX))
        return STR2NUM_OVERFLOW;
    if (s2n_unlikely(errno == ERANGE && l == 0))
        return STR2NUM_UNDERFLOW;
    if (s2n_unlikely(endptr!=nullptr && **endptr != '\0'))
        return STR2NUM_INCONVERTIBLE;
    *out = l;
    return STR2NUM_SUCCESS;
}

str2num_errno str2long(long *out, const char *s, char** endptr = nullptr, int base=10) {
    if (s == nullptr || s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    long l = strtol(s, endptr, base);
    if (s2n_unlikely(errno == ERANGE && l == LONG_MAX))
        return STR2NUM_OVERFLOW;
    if (s2n_unlikely(errno == ERANGE && l == LONG_MIN))
        return STR2NUM_UNDERFLOW;
    if (s2n_unlikely(endptr!=nullptr && **endptr != '\0'))
        return STR2NUM_INCONVERTIBLE;
    *out = l;
    return STR2NUM_SUCCESS;
}

str2num_errno str2ulong(unsigned long *out, const char *s, char** endptr = nullptr, int base=10) {
    if (s == nullptr || s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    long l = strtoul(s, endptr, base);
    if (s2n_unlikely(errno == ERANGE && l == LONG_MAX))
        return STR2NUM_OVERFLOW;
    if (s2n_unlikely((errno == ERANGE ) || (endptr!=nullptr && **endptr != '\0') ))
        return STR2NUM_INCONVERTIBLE;
    *out = l;
    return STR2NUM_SUCCESS;
}

str2num_errno str2lglgint(long long int *out, char *s, char** endptr = nullptr, int base = 10) {
    if (s == nullptr || s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    long long int l = strtoll(s, endptr, base);
    /* Both checks are needed because l == LONG_MAX or l == LLONG_MIN is possible. */
    if (s2n_unlikely(errno == ERANGE && l == LLONG_MAX))
        return STR2NUM_OVERFLOW;
    if (s2n_unlikely(errno == ERANGE && l == LLONG_MIN))
        return STR2NUM_UNDERFLOW;
    if (s2n_unlikely(endptr!=nullptr && **endptr != '\0'))
        return STR2NUM_INCONVERTIBLE;
    *out = l;
    return STR2NUM_SUCCESS;
}

str2num_errno str2lglguint(long long unsigned int *out, char *s, char** endptr = nullptr, int base = 10) {
    if (s == nullptr || s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    long long unsigned int l = strtoull(s, endptr, base);
    /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
    if (s2n_unlikely(errno == ERANGE && l == ULLONG_MAX))
        return STR2NUM_OVERFLOW;
    if (s2n_unlikely(errno == ERANGE && l == 0))
        return STR2NUM_UNDERFLOW;
    if (s2n_unlikely(endptr!=nullptr && **endptr != '\0'))
        return STR2NUM_INCONVERTIBLE;
    *out = l;
    return STR2NUM_SUCCESS;
}

str2num_errno str2doub(double *out, const char *s) {
    if (s == nullptr || s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    char *err;
    *out = strtod(s, &err);
    if (s2n_likely(*err == 0)) return STR2NUM_SUCCESS;
    else return STR2NUM_INCONVERTIBLE;
}

str2num_errno str2float(float *out, const char *s) {
    if (s == nullptr || s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    char *err;
    *out = strtof(s, &err);
    if (s2n_likely(*err == 0) ) return STR2NUM_SUCCESS;
    else return STR2NUM_INCONVERTIBLE;
}

#undef s2n_likely
#undef s2n_unlikely

#endif
