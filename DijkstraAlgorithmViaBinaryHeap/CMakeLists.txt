cmake_minimum_required (VERSION 3.8)

project ("DijkstraAlgorithmViaBinaryHeap")

ADD_SUBDIRECTORY("Input-Library")

add_executable (DijkstraAlgorithmViaBinaryHeap "main.cpp")
target_link_libraries(DijkstraAlgorithmViaBinaryHeap InputLibrary)
