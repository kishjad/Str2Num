add_executable(str2num_test test_conversion.cpp)

set_property(TARGET str2num_test PROPERTY
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

add_executable(str2num_test_cpp test_cpp_conversions.cpp)

set_property(TARGET str2num_test_cpp PROPERTY
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)