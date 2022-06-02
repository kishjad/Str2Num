//  SPDX-FileCopyrightText: 2022 Kish Jadhav
//  SPDX-License-Identifier: MIT License

#ifndef STRCONVERT_H
#define STRCONVERT_H

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <cwchar>
#include <cwctype>
#include <math.h>
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

/*
    * Convert a string to an integer.
    *
    * @param out Pointer to the integer to store the result in.
    * @param s The string to convert.
    * @param endptr Pointer to a pointer to the character after the last character
    *              of the string. If the conversion was successful, this will point
    *              to the character after the last character of the converted
    *              integer.
    * @param base The base to use for the conversion.
    *
    * @return The error code.
*/
str2num_errno str2int(int *out, const char *s, char** endptr , int base) {
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
str2num_errno str2int(int *out, const char *s, char** endptr ) {
    return str2int(out, s, endptr, 10);
}
str2num_errno str2int(int *out, const char *s) {
    return str2int(out, s, NULL, 10);
}
str2num_errno str2int(int* out, const wchar_t* s, wchar_t** endptr, int base ){
    if (s == nullptr || s[0] == '\0' || iswspace(s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    long l = wcstol(s, endptr, base);
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
str2num_errno str2int(int *out, const wchar_t *s, wchar_t** endptr) {
    return str2int(out, s, endptr, 10);
}
str2num_errno str2int(int *out, const wchar_t *s) {
    return str2int(out, s, NULL, 10);
}


/*******************************************************************************/
/*
    * Convert a string to an unsigned integer.
    *
    * @param out Pointer to the unsigned integer to store the result in.
    * @param s The string to convert.
    * @param endptr Pointer to a pointer to the character after the last character
    *              of the string. If the conversion was successful, this will point
    *              to the character after the last character of the converted
    *              integer.
    * @param base The base to use for the conversion.
    *
    * @return The error code. 
*/
str2num_errno str2uint(unsigned int *out, const char *s, char** endptr, int base) {
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
str2num_errno str2uint(unsigned int *out, const char *s, char** endptr) {
    return str2uint(out, s, endptr, 10);
}
str2num_errno str2uint(unsigned int *out, const char *s) {
    return str2uint(out, s, NULL, 10);
}
str2num_errno str2uint(unsigned int *out, const wchar_t* s, wchar_t** endptr, int base ){
    if (s == nullptr || s[0] == '\0' || iswspace(s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    unsigned long int l = wcstoul(s, endptr, base);
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
str2num_errno str2uint(unsigned int *out, const wchar_t *s, wchar_t** endptr) {
    return str2uint(out, s, endptr, 10);
}
str2num_errno str2uint(unsigned int *out, const wchar_t *s) {
    return str2uint(out, s, NULL, 10);
}

/*******************************************************************************/
/*
    * Convert a string to a long integer.
    *
    * @param out Pointer to the long integer to store the result in.
    * @param s The string to convert.
    * @param endptr Pointer to a pointer to the character after the last character
    *              of the string. If the conversion was successful, this will point
    *              to the character after the last character of the converted
    *              integer.
    * @param base The base to use for the conversion.
    *
    * @return The error code.
*/
str2num_errno str2l(long *out, const char *s, char** endptr , int base) {
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
str2num_errno str2l(long *out, const char *s, char** endptr ) {
    return str2l(out, s, endptr, 10);
}
str2num_errno str2l(long *out, const char *s) {
    return str2l(out, s, NULL, 10);
}
str2num_errno str2l(long *out, const wchar_t *s, wchar_t** endptr , int base){
    if (s == nullptr || s[0] == '\0' || iswspace(s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    long l = wcstol(s, endptr, base);
    if (s2n_unlikely(errno == ERANGE && l == LONG_MAX))
        return STR2NUM_OVERFLOW;
    if (s2n_unlikely(errno == ERANGE && l == LONG_MIN))
        return STR2NUM_UNDERFLOW;
    if (s2n_unlikely(endptr!=nullptr && **endptr != '\0'))
        return STR2NUM_INCONVERTIBLE;
    *out = l;
    return STR2NUM_SUCCESS;
}
str2num_errno str2l(long *out, const wchar_t *s, wchar_t** endptr ) {
    return str2l(out, s, endptr, 10);
}
str2num_errno str2l(long *out, const wchar_t *s) {
    return str2l(out, s, NULL, 10);
}


/*******************************************************************************/
/*
    * Convert a string to an unsigned long integer.
    *
    * @param out Pointer to the unsigned long integer to store the result in.
    * @param s The string to convert.
    * @param endptr Pointer to a pointer to the character after the last character
    *              of the string. If the conversion was successful, this will point
    *              to the character after the last character of the converted
    *              integer.
    * @param base The base to use for the conversion.
    *
    * @return The error code.
*/
str2num_errno str2ul(unsigned long *out, const char *s, char** endptr, int base) {
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
str2num_errno str2ul(unsigned long *out, const char *s, char** endptr) {
    return str2ul(out, s, endptr, 10);
}
str2num_errno str2ul(unsigned long *out, const char *s) {
    return str2ul(out, s, NULL, 10);
}
str2num_errno str2ul(unsigned long *out, const wchar_t *s, wchar_t** endptr, int base){
    if (s == nullptr || s[0] == '\0' || iswspace(s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    unsigned long l = wcstoul(s, endptr, base);
    if (s2n_unlikely(errno == ERANGE && l == ULONG_MAX))
        return STR2NUM_OVERFLOW;
    if (s2n_unlikely(errno == ERANGE && l == 0))
        return STR2NUM_UNDERFLOW;
    if (s2n_unlikely(endptr!=nullptr && **endptr != '\0'))
        return STR2NUM_INCONVERTIBLE;
    *out = l;
    return STR2NUM_SUCCESS;
}
str2num_errno str2ul(unsigned long *out, const wchar_t *s, wchar_t** endptr) {
    return str2ul(out, s, endptr, 10);
}
str2num_errno str2ul(unsigned long *out, const wchar_t *s) {
    return str2ul(out, s, NULL, 10);
}


/*******************************************************************************/
/*
    * Convert a string to a long long integer.
    *
    * @param out Pointer to the long long integer to store the result in.
    * @param s The string to convert.
    * @param endptr Pointer to a pointer to the character after the last character
    *              of the string. If the conversion was successful, this will point
    *              to the character after the last character of the converted
    *              integer.
    * @param base The base to use for the conversion.
    *
    * @return The error code.
*/
str2num_errno str2ll(long long int *out, const char *s, char** endptr, int base) {
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
str2num_errno str2ll(long long int *out, const char *s, char** endptr) {
    return str2ll(out, s, endptr, 10);
}
str2num_errno str2ll(long long int *out, const char *s) {
    return str2ll(out, s, NULL, 10);
}
str2num_errno str2ll(long long int *out, const wchar_t *s, wchar_t** endptr, int base){
    if (s == nullptr || s[0] == '\0' || iswspace(s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    long long int l = wcstoll(s, endptr, base);
    if (s2n_unlikely(errno == ERANGE && l == LLONG_MAX))
        return STR2NUM_OVERFLOW;
    if (s2n_unlikely(errno == ERANGE && l == LLONG_MIN))
        return STR2NUM_UNDERFLOW;
    if (s2n_unlikely(endptr!=nullptr && **endptr != '\0'))
        return STR2NUM_INCONVERTIBLE;
    *out = l;
    return STR2NUM_SUCCESS;
}
str2num_errno str2ll(long long int *out, const wchar_t *s, wchar_t** endptr) {
    return str2ll(out, s, endptr, 10);
}
str2num_errno str2ll(long long int *out, const wchar_t *s) {
    return str2ll(out, s, NULL, 10);
}


/*******************************************************************************/
/*
    * Convert a string to an unsigned long long integer.
    *
    * @param out Pointer to the unsigned long long integer to store the result in.
    * @param s The string to convert.
    * @param endptr Pointer to a pointer to the character after the last character
    *              of the string. If the conversion was successful, this will point
    *              to the character after the last character of the converted
    *              integer.
    * @param base The base to use for the conversion.
    *
    * @return The error code.
*/
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
str2num_errno str2ull(long long unsigned int *out, const char *s, char** endptr) {
    return str2ull(out, s, endptr, 10);
}
str2num_errno str2ull(long long unsigned int *out, const char *s) {
    return str2ull(out, s, NULL, 10);
}
str2num_errno str2ull(long long unsigned int *out, const wchar_t *s, wchar_t** endptr = nullptr, int base = 10){
    if (s == nullptr || s[0] == '\0' || iswspace(s[0]))
        return STR2NUM_INCONVERTIBLE;
    errno = 0;
    long long unsigned int l = wcstoull(s, endptr, base);
    if (s2n_unlikely(errno == ERANGE && l == ULLONG_MAX))
        return STR2NUM_OVERFLOW;
    if (s2n_unlikely(errno == ERANGE && l == 0))
        return STR2NUM_UNDERFLOW;
    if (s2n_unlikely(endptr!=nullptr && **endptr != '\0'))
        return STR2NUM_INCONVERTIBLE;
    *out = l;
    return STR2NUM_SUCCESS;
}
str2num_errno str2ull(long long unsigned int *out, const wchar_t *s, wchar_t** endptr) {
    return str2ull(out, s, endptr, 10);
}
str2num_errno str2ull(long long unsigned int *out, const wchar_t *s) {
    return str2ull(out, s, NULL, 10);
}


/*******************************************************************************/
/*
    * Convert a string to a double.
    *
    * @param out Pointer to the double to store the result in.
    * @param s The string to convert.
    * @return The error code.
*/
str2num_errno str2d(double *out, const char *s, char** endptr) {
    if (s == nullptr || s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    char* ptr = NULL;
    errno = 0;
    double result = strtod(s, &ptr);
    if (s2n_unlikely(errno == ERANGE && result >= HUGE_VAL))
        return STR2NUM_OVERFLOW;
    if (s2n_unlikely(errno == ERANGE && result <= -HUGE_VAL))
        return STR2NUM_UNDERFLOW;
    if (s2n_unlikely( (ptr!=nullptr && s == ptr) ))
        return STR2NUM_INCONVERTIBLE;
    *out = result;
    if(endptr != NULL) (*endptr = ptr);
    return STR2NUM_SUCCESS;
}
str2num_errno str2d(double *out, const char *s) {
    return str2d(out, s, NULL);
}
str2num_errno str2d(double *out, const wchar_t *s, wchar_t** endptr){
    if (s == nullptr || s[0] == '\0' || iswspace(s[0]))
        return STR2NUM_INCONVERTIBLE;
    wchar_t* ptr = NULL;
    errno = 0;
    double result = wcstod(s, &ptr);
    if (s2n_unlikely(errno == ERANGE && result >= HUGE_VAL))
        return STR2NUM_OVERFLOW;
    if (s2n_unlikely(errno == ERANGE && result <= -HUGE_VAL))
        return STR2NUM_UNDERFLOW;
    if (s2n_unlikely( (ptr!=nullptr && s == ptr) ))
        return STR2NUM_INCONVERTIBLE;
    *out = result;
    if(endptr != NULL) (*endptr = ptr);
    return STR2NUM_SUCCESS;
}
str2num_errno str2d(double *out, const wchar_t *s) {
    return str2d(out, s, NULL);
}


/*******************************************************************************/
/*
    * Convert a string to a float
    *
    * @param out Pointer to the float to store the result in.
    * @param s The string to convert.
    * @return The error code.
*/
str2num_errno str2f(float *out, const char *s, char** endptr) {
    if (s == nullptr || s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2NUM_INCONVERTIBLE;
    char *ptr = NULL;
    errno = 0;
    float result = strtof(s, &ptr);
    if (s2n_unlikely(errno == ERANGE && result >= HUGE_VALF))
        return STR2NUM_OVERFLOW;
    if (s2n_unlikely(errno == ERANGE && result <= -HUGE_VALF))
        return STR2NUM_UNDERFLOW;
    if (s2n_unlikely( (ptr!=nullptr && s == ptr) ))
        return STR2NUM_INCONVERTIBLE;
    *out = result;
    if(endptr != NULL) (*endptr = ptr);
    return STR2NUM_SUCCESS;
}
str2num_errno str2f(float * out, const char *s){
    return str2f(out, s, NULL);
}
str2num_errno str2f(float *out, const wchar_t *s, wchar_t** endptr) {
    if (s == nullptr || s[0] == '\0' || iswspace(s[0]))
        return STR2NUM_INCONVERTIBLE;
    wchar_t *ptr = NULL;
    errno = 0;
    float result = wcstof(s, &ptr);
    if (s2n_unlikely(errno == ERANGE && result >= HUGE_VALF))
        return STR2NUM_OVERFLOW;
    if (s2n_unlikely(errno == ERANGE && result <= -HUGE_VALF))
        return STR2NUM_UNDERFLOW;
    if (s2n_unlikely( (ptr!=nullptr && s == ptr) ))
        return STR2NUM_INCONVERTIBLE;
    *out = result;
    if(endptr != NULL) (*endptr = ptr);
    return STR2NUM_SUCCESS;
}
str2num_errno str2f(float * out, const wchar_t *s){
    return str2f(out, s, NULL);
}


/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/

#ifdef __cplusplus
#include <string>
#include <optional>
#include <locale>
#include <type_traits>
//Exception Free wrappers for the following
/*
stoi,stol,stoul,stoll,stoull,stof,stod
*/

namespace s2n{
    /*
        * Convert a string to an integer.
        *
        * @param str The string to convert.
        * @param pos  If not null, the function also sets the value of idx to the position of the first character in str after 
        *             the number.
        * @param base The base to use for the conversion.
        *
        *  @return std::nullopt if the string is not valid or integer.
    */
    template<typename T, 
        typename = typename std::enable_if<std::is_same<std::string, T>::value || std::is_same<std::wstring, T>::value>::type>
    std::optional<int> safe_stoi( const T& str, std::size_t* pos = nullptr, int base = 10 ) noexcept {
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

    /*
        * Convert a string to an unsigned integer.
        *
        * @param str The string to convert.
        * @param pos  If not null, the function also sets the value of idx to the position of the first character in str after 
        *             the number.
        * @param base The base to use for the conversion.
        *
        * @return std::nullopt if the string is not a valid unsigned integer or unsigned integer.
    */
    template<typename T, 
        typename = typename std::enable_if<std::is_same<std::string, T>::value || std::is_same<std::wstring, T>::value>::type>
    std::optional<long> safe_stol( const T& str, std::size_t* pos = nullptr, int base = 10 ) noexcept {
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

    /*
        * Convert a string to an unsigned integer.
        *
        * @param str The string to convert.
        * @param pos  If not null, the function also sets the value of idx to the position of the first character in str after 
        *             the number.
        * @param base The base to use for the conversion.
        *
        * @return std::nullopt if the string is not valid or unsigned long.
    */
   template<typename T, 
        typename = typename std::enable_if<std::is_same<std::string, T>::value || std::is_same<std::wstring, T>::value>::type>
    std::optional<unsigned long> safe_stoul( const T& str, std::size_t* pos = nullptr, int base = 10 ) noexcept {
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

    /*
        * Convert a string to an unsigned integer.
        *
        * @param str The string to convert.
        * @param pos  If not null, the function also sets the value of idx to the position of the first character in str after 
        *             the number.
        * @param base The base to use for the conversion.
        *
        * @return std::nullopt if the string is not valid or long long.
    */
    template<typename T, 
        typename = typename std::enable_if<std::is_same<std::string, T>::value || std::is_same<std::wstring, T>::value>::type>
    std::optional<long long> safe_stoll( const T& str, std::size_t* pos = nullptr, int base = 10 ) noexcept {
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
    
    /*
        * Convert a string to an unsigned integer.
        *
        * @param str The string to convert.
        * @param pos  If not null, the function also sets the value of idx to the position of the first character in str after 
        *             the number.
        * @param base The base to use for the conversion.
        *
        * @return std::nullopt if the string is not valid or unsigned long long.
    */
    template<typename T, 
        typename = typename std::enable_if<std::is_same<std::string, T>::value || std::is_same<std::wstring, T>::value>::type>
    std::optional<unsigned long long> safe_stoull( const T& str, std::size_t* pos = nullptr, int base = 10 ) noexcept {
        unsigned long long out;
        char* endptr = nullptr;
        if(str2ull(&out, str.c_str(), &endptr, base) == STR2NUM_SUCCESS)
            {   
                if(pos != nullptr)
                    *pos = endptr - str.c_str();
                return out;
            }
        else return std::nullopt;
    }

    /*
        * Convert a string to a double.
        *
        * @param str The string to convert.
        * @param pos  If not null, the function also sets the value of idx to the position of the first character in str after 
        *             the number.
        *
        * @return std::nullopt if the string is not valid or double.
    */
    template<typename T, 
        typename = typename std::enable_if<std::is_same<std::string, T>::value || std::is_same<std::wstring, T>::value>::type>
    std::optional<double> safe_stod( const T& str, std::size_t* pos = nullptr ) noexcept {
        double out;
        char* endptr = nullptr;
        if(str2d(&out, str.c_str(), &endptr) == STR2NUM_SUCCESS)
        {   
            if(pos != nullptr)
                *pos = endptr - str.c_str();
            return out;
        }
        else return std::nullopt;
    }

    /*
        * Convert a string to a float.
        *
        * @param str The string to convert.
        * @param pos  If not null, the function also sets the value of idx to the position of the first character in str after 
        *             the number.
        *
        * @return std::nullopt if the string is not valid or float.
    */
    template<typename T, 
        typename = typename std::enable_if<std::is_same<std::string, T>::value || std::is_same<std::wstring, T>::value>::type>
    std::optional<float> safe_stof( const T& str, std::size_t* pos = nullptr ) noexcept {
        float out;
        if(str2f(&out, str.c_str()) == STR2NUM_SUCCESS)
        {   
            if(pos != nullptr)
                *pos = str.size();
            return out;
        }
        else return std::nullopt;
    }
};
#endif //__cplusplus

#undef s2n_likely
#undef s2n_unlikely

#endif
