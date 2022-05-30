//  SPDX-FileCopyrightText: 2022 Kish Jadhav
//  SPDX-License-Identifier: MIT License

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

str2num_errno str2l(long *out, const char *s, char** endptr = nullptr, int base=10) {
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

str2num_errno str2ul(unsigned long *out, const char *s, char** endptr = nullptr, int base=10) {
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

str2num_errno str2ll(long long int *out, const char *s, char** endptr = nullptr, int base = 10) {
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

str2num_errno str2ull(long long unsigned int *out, const char *s, char** endptr = nullptr, int base = 10) {
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

str2num_errno str2d(double *out, const char *s) {
    if (s == nullptr || s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    char *err;
    *out = strtod(s, &err);
    if (s2n_likely(*err == 0)) return STR2NUM_SUCCESS;
    else return STR2NUM_INCONVERTIBLE;
}

str2num_errno str2f(float *out, const char *s) {
    if (s == nullptr || s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    char *err;
    *out = strtof(s, &err);
    if (s2n_likely(*err == 0) ) return STR2NUM_SUCCESS;
    else return STR2NUM_INCONVERTIBLE;
}

#ifdef __cplusplus
#include <string>
#include <optional>
//Exception Free wrappers for the following
/*
stoi
stol
stoul
stoll
stoull
*/

namespace s2n{
    //stoi
    std::optional<int> safe_stoi( const std::string& str, std::size_t* pos = nullptr, int base = 10 ){
        int out;
        char* endptr = nullptr;
        if(str2int(&out, str.c_str(), &endptr, base) == STR2NUM_SUCCESS)
            {   
                if(pos != nullptr)
                    *pos = endptr - str.c_str();
                return out;
            }
        else return std::nullopt;
    }

    //stol
    std::optional<long> safe_stol( const std::string& str, std::size_t* pos = nullptr, int base = 10 ){
        long out;
        char* endptr = nullptr;
        if(str2l(&out, str.c_str(), &endptr, base) == STR2NUM_SUCCESS)
            {   
                if(pos != nullptr)
                    *pos = endptr - str.c_str();
                return out;
            }
        else return std::nullopt;
    }

    //stoul
    std::optional<unsigned long> safe_stoul( const std::string& str, std::size_t* pos = nullptr, int base = 10 ){
        unsigned long out;
        char* endptr = nullptr;
        if(str2ul(&out, str.c_str(), &endptr, base) == STR2NUM_SUCCESS)
            {   
                if(pos != nullptr)
                    *pos = endptr - str.c_str();
                return out;
            }
        else return std::nullopt;
    }

    //stoll
    std::optional<long long> safe_stoll( const std::string& str, std::size_t* pos = nullptr, int base = 10 ){
        long long out;
        char* endptr = nullptr;
        if(str2ll(&out, str.c_str(), &endptr, base) == STR2NUM_SUCCESS)
            {   
                if(pos != nullptr)
                    *pos = endptr - str.c_str();
                return out;
            }
        else return std::nullopt;
    }
};
#endif //__cplusplus

#undef s2n_likely
#undef s2n_unlikely

#endif
