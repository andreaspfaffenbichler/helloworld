cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

project(hello_virtual_void)

message("VCPKG_ROOT: " $ENV{VCPKG_ROOT}/)

find_package(virtual_void CONFIG REQUIRED)

add_executable(hello_virtual_void hello_virtual_void.cpp)

target_link_libraries(hello_virtual_void PRIVATE virtual_void::virtual_void)
