cmake_minimum_required(VERSION 3.15)

project(
     qt-nmh-reader
     VERSION 0.1
     DESCRIPTION "Qt based NMH reader/writer"
     LANGUAGES CXX
)

add_subdirectory(extension)
add_subdirectory(backend)
