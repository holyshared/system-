cmake_minimum_required(VERSION 3.9)
project(system C)

set(CMAKE_C_STANDARD 99)

add_executable(read_file file/read_file.c)
add_executable(readv file/readv.c)

add_executable(write_file file/write_file.c)
add_executable(writev file/writev.c)

add_executable(poll io/poll.c)
add_executable(select io/select.c)
add_executable(stream io/stream.c)
add_executable(stream_n io/stream_n.c)
