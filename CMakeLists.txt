cmake_minimum_required(VERSION 3.26)
project(AiZO_2)

set(CMAKE_CXX_STANDARD 17)


set (SOURCE_FILES
        src/main.cpp
        src/algorithms/Dijkstra.cpp
        src/algorithms/BellmanFord.cpp
        src/algorithms/Prim.cpp
        src/algorithms/Kruskal.cpp
        src/graph/IncidenceMatrix.cpp
        src/graph/Edge.cpp
        src/io/GraphLoader.cpp
        src/io/ResultWriter.cpp
        src/timer/Timer.cpp
        src/utils/Generator.cpp
        src/utils/CParser.cpp
        src/graph/AdjacencyList.cpp
)

add_executable(AiZO_2 ${SOURCE_FILES})

target_include_directories(AiZO_2 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/algorithms
        ${CMAKE_CURRENT_SOURCE_DIR}/include/graph
        ${CMAKE_CURRENT_SOURCE_DIR}/include/io
        ${CMAKE_CURRENT_SOURCE_DIR}/include/utils
        ${CMAKE_CURRENT_SOURCE_DIR}/include/timer
)
