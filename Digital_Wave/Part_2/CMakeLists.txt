cmake_minimum_required(VERSION 3.29)
project(Part_2)

set(CMAKE_CXX_STANDARD 20)
#set($ENV{CURL} "C:\\Users\\Demonic\\.vcpkg-clion\\vcpkg\\packages\\curl_x64-mingw-dynamic\\lib")
#find_package(CURL REQUIRED)
#add_executable(Part_2 main.cpp)
#target_link_libraries(Part_2 CURL::libcurl)
#target_include_directories(Part_2 PRIVATE ${CURL_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -lcurl")
set(libcurl_INCLUDE_DIR "C:\\Users\\Demonic\\.vcpkg-clion\\vcpkg\\packages\\curl_x64-mingw-dynamic\\include")
include_directories(${libcurl_INCLUDE_DIR})
add_executable(Part_2 main.cpp
        parser.cpp
        parser.h)
target_link_libraries(Part_2 "C:\\Users\\Demonic\\.vcpkg-clion\\vcpkg\\packages\\curl_x64-mingw-dynamic\\lib\\libcurl.dll.a")