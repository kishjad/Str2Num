<h align="center"> 
<h1> Str2Num </h1>
</h>
<p align="center">
    <img src=https://img.shields.io/github/license/kshitej/str2Num>
    <img src=https://img.shields.io/badge/Powered%20By-C%2B%2B-blue>
    <img src=https://img.shields.io/github/languages/code-size/kshitej/str2Num?color=purple>
</p>
Safe conversions for C/C++ style string to numbers

## Functions
| Function   | Supported Language | Description |
| ----------- | ----------- | ----------- |
| `str2int` | C/C++ | Converts a string to an integer |
| `str2uint` | C/C++ | Converts a string to an unsigned integer |
| `str2l` | C/C++ | Converts a string to a long integer |
| `str2ul` | C/C++ | Converts a string to an unsigned long integer |
| `str2ll` | C/C++ | Converts a string to a long long integer |
| `str2ull` | C/C++ | Converts a string to an unsigned long long integer |
| `str2f` | C/C++ | Converts a string to a float |
| `str2d` | C/C++ | Converts a string to a double |
|  |  |  |
| `safe_stoi` | C++ | Exception free wrapper for stoi |
| `safe_stol` | C++ | Exception free wrapper for stol |
| `safe_stoul` | C++ | Exception free wrapper for stoul |
| `safe_stoll` | C++ | Exception free wrapper for stoll |
| `safe_stoull` | C++ | Exception free wrapper for stoull |
| `safe_stof` | C++ | Exception free wrapper for stof |
| `safe_stod` | C++ | Exception free wrapper for stod |


Notes about C++ only functions (start with `safe_`): 
 - Functions are exception free.
 - Return value is either `std::nullopt` or the converted value.
    - If the conversion fails, the return value is `std::nullopt`.
    - If the conversion succeeds, the return value is the converted value.
 - Function parameters are as follows: 
    `std::optional<> function(const T& str, std::size_t* pos = nullptr, int base = 10)`
    - `str` is the string to convert, can be `std::string` or `std::wstring` only
    - `pos` if not null, the function also sets the value of idx to the position of the first character in str after the number
    - `base` is the base of the number, default is 10

Notes about C/C++ only functions (start with `str2`): 
 - Functions are exception free and return an error or success code.
 - Function parameters are as follows: 
    `str2num_errno function(<intergral_type> *out, const char *s, char** endptr , int base)`
    - `out` Pointer to the integeral type to store the result in, ex: int, float, double, etc.
    - `s` C-style string to convert.
    - `endptr` Pointer to a pointer to the character after the last character
    of the string. If the conversion was successful, this will point
    to the character after the last character of the converted integer.
    - `base` Base of the number, default is 10.
    - `str2num_errno` error code returned by the function.

## Examples
Safe conversions for C++
```cpp
std::string s = "123";
auto i = s2n::safe_stoi(s);
// i == 123 if s is a valid integer
// or i  == std::nullopt if s is not a valid integer
```

Safe conversions for C/C++
```c
char s[] = "123";
int i = 0;
if( str2int(&i, s) == STR2NUM_SUCCESS){
    // i == 123
};
else{
    // Conversion failed, i == 0
};
```

Extended examples are included in the `examples` directory.
