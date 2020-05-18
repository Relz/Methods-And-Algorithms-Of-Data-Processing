cmake_minimum_required(VERSION 3.8)
project(MultipleSampleTextSearch)

set(CMAKE_CXX_STANDARD 20)

add_executable(MultipleSampleTextSearch main.cpp Bohr/Bohr.cpp Bohr/Bohr.h Bohr/BohrNode.h Bohr/BohrResult.h Bohr/TextFilePosition.h)
