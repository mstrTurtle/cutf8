# CMakeList.txt : CMake project for cutf8, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source to this project's executable.
add_library (cutf8 "cutf8.cpp")

add_library (conventer "converter.cpp")


# TODO: Add tests and install targets if needed.
