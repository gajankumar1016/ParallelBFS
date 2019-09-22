cmake_minimum_required(VERSION 3.10)
project(ParallelBFS)

set(CMAKE_CXX_STANDARD 17)


set(SOURCE_FILES main.cpp)
add_executable(parallel_bfs_run ${SOURCE_FILES})


include_directories(src)

add_subdirectory(src)
# add_subdirectory(test)

target_link_libraries(parallel_bfs_run parallel_bfs)
