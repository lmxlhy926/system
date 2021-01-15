cmake_minimum_required(VERSION 3.15)
project(file_process_thread)

set(CMAKE_CXX_STANDARD 14)

set(link_library fpt_environ
                fpt_fork
                fpt_exec
                fpt_waitpid
                fpt_pipe
                fpt_socket)

include_directories("fpt_environment")
include_directories("fpt_fork")
include_directories("fpt_exec")
include_directories("fpt_waitpid")
include_directories("fpt_pipe")
include_directories("fpt_socket")

add_subdirectory(fpt_environment)
add_subdirectory(fpt_fork)
add_subdirectory(fpt_exec)
add_subdirectory(fpt_waitpid)
add_subdirectory(fpt_pipe)
add_subdirectory(fpt_socket)

add_executable(file_process_thread main.cpp)
target_link_libraries(file_process_thread ${link_library})
