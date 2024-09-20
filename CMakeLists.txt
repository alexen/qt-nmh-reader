cmake_minimum_required(VERSION 3.15)

project(
     qt_nmh_reader
     VERSION 0.1
     DESCRIPTION "Qt based NMH reader/writer"
     LANGUAGES CXX
)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
     set(CMAKE_INSTALL_PREFIX $ENV{HOME}/.local/${PROJECT_NAME} CACHE PATH "" FORCE)
endif()

include(CTest)
if(BUILD_TESTING)
     find_package(GTest REQUIRED)
endif()

add_subdirectory(backend)
add_subdirectory(extension)
