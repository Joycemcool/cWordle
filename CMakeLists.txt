cmake_minimum_required(VERSION 3.21)
project(ASSIGN5 C)

set(CMAKE_C_STANDARD 17)
#
include_directories("C:/cmake/curl-8.0.1_9-win64-mingw/include")
link_directories("C:/cmake/curl-8.0.1_9-win64-mingw/lib")

#add_executable(ASSIGN5 src/main.c inc/wordle.h src/wordle.c)

#set( LIBS libcurl )
#target_link_libraries(ASSIGN5 ${LIBS})

set(CMAKE_SOURCE_DIR C:/Users/joyce/AppData/Local/JetBrains/Toolbox/apps/CLion/ch-0/223.8617.54/bin/curl-8.0.1_9-win64-mingw)
set(CURL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(CURL_LIBRARY ${CMAKE_SOURCE_DIR}/lib/libcurl.dll.a)

add_definitions(-DCURL_STATICLIB)
find_package(CURL REQUIRED)
include_directories(${CMAKE_SOURCE_DIR})
add_executable(ASSIGN5 src/main.c inc/wordle.h src/wordle.c)
target_link_libraries(ASSIGN5 ${CURL_LIBRARY})
