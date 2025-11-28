cmake_minimum_required(VERSION 3.10)
project(CryptoTool C)

set(CMAKE_C_STANDARD 17)

include_directories(include)

file(GLOB SOURCES "*.c")

add_executable(cryptotool ${SOURCES})

target_link_libraries(cryptotool crypt32)
