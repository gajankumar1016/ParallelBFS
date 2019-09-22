project(parallel_bfs)

set(HEADER_FILES
        edge.h
        graph.h
        bfs.h
        bfsmultithreaded.h
        randomgraphgenerator.h)

set(SOURCE_FILES
        edge.cpp
        graph.cpp
        bfs.cpp
        bfsmultithreaded.cpp
        randomgraphgenerator.cpp)


add_library(parallel_bfs STATIC ${SOURCE_FILES} ${HEADER_FILES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(parallel_bfs Threads::Threads)
