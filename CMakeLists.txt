cmake_minimum_required (VERSION 3.25)
project (dlib)

option (DLIB_BUILD_TESTS "Build tests" ON)
add_library (dlib source/dlib.cpp)
target_include_directories (dlib PUBLIC include)
set_target_properties (dlib PROPERTIES CXX_STANDARD 17)

if (DLIB_BUILD_TESTS)
enable_testing()
add_subdirectory (tests)
endif()
