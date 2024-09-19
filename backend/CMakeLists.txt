set(APPLICATION_NAME ${PROJECT_NAME})

find_package(
     Qt5
     COMPONENTS Widgets
     REQUIRED
)

# Применяем интересную методику сохранения полезных свойств
# в фиктивных целях для последующего многократного использования
# в разных местах преокта.
#
# @see https://palikar.github.io/posts/cmake_structure/
#
add_library(ENABLE_ALL_WARNINGS_AS_ERROR INTERFACE)
target_compile_options(
     ENABLE_ALL_WARNINGS_AS_ERROR
     INTERFACE
          -Wall
          -Werror
          -pedantic
)
add_library(ENABLE_CPP_STANDARD INTERFACE)
set_target_properties(
     ENABLE_CPP_STANDARD
     PROPERTIES
          CXX_STANDARD 17
          CXX_STANDARD_REQUIRED ON
)


add_executable(${APPLICATION_NAME})
target_sources(
     ${APPLICATION_NAME}
     PRIVATE
          io_tools.cpp
          request_listener.cpp
          response_sender.cpp
          application.cpp
          main.cpp
)
target_link_libraries(
     ${APPLICATION_NAME}
     PRIVATE
          ENABLE_CPP_STANDARD
          ENABLE_ALL_WARNINGS_AS_ERROR
          Qt5::Widgets
)
set_target_properties(
     ${APPLICATION_NAME}
     PROPERTIES
          AUTOUIC ON
          AUTOMOC ON
          AUTORCC ON
          CXX_STANDARD 17
          CXX_STANDARD_REQUIRED ON
)
target_include_directories(
     ${APPLICATION_NAME}
     PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
