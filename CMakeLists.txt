cmake_minimum_required(VERSION 3.10)

project(HelloWorld)

message("VCPKG_ROOT: " $ENV{VCPKG_ROOT}/)

find_package(fmt CONFIG REQUIRED)
#find_package(my_sample_lib CONFIG REQUIRED)

add_executable(HelloWorld helloworld.cpp)

target_link_libraries(HelloWorld PRIVATE fmt::fmt)
#target_link_libraries(HelloWorld PRIVATE my_sample_lib::my_sample_lib)