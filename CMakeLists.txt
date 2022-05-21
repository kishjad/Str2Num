cmake_minimum_required (VERSION 3.1)

project (str2num VERSION 1.0 LANGUAGES CXX)

message(${CMAKE_CXX_COMPILER_ID})
set(STR2NUM_TARGET_NAME ${PROJECT_NAME})
set(STR2NUM_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

message(STATUS ${CMAKE_BUILD_TYPE})
include_directories(${STR2NUM_INCLUDE_DIRS})
add_subdirectory(test)