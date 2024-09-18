cmake_minimum_required(VERSION 3.15)

project(
     qt-nmh-reader
     VERSION 0.1
     DESCRIPTION "Qt based NMH reader/writer"
     LANGUAGES CXX
)

find_package(
     Qt5
     COMPONENTS Widgets
     REQUIRED
)

add_executable(${PROJECT_NAME})
target_sources(
     ${PROJECT_NAME}
     PRIVATE
          application.ui
          application.h
          application.cpp
          main.cpp
)
target_link_libraries(
     ${PROJECT_NAME}
     PRIVATE
          Qt5::Widgets
)
set_target_properties(
     ${PROJECT_NAME}
     PROPERTIES
          AUTOUIC ON
          AUTOMOC ON
          AUTORCC ON
          CXX_STANDARD 17
          CXX_STANDARD_REQUIRED ON
)
target_include_directories(
     ${PROJECT_NAME}
     PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
