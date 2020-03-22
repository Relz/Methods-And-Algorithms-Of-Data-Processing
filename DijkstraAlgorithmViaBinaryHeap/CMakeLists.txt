cmake_minimum_required (VERSION 3.8)

project ("DijkstraAlgorithmViaBinaryHeap")

add_subdirectory("Input-Library")

add_executable (DijkstraAlgorithmViaBinaryHeap "main.cpp" "Relation/Relation.cpp" "Relation/Relation.h")
target_link_libraries(DijkstraAlgorithmViaBinaryHeap InputLibrary)
