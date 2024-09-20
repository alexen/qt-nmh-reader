set(APPLICATION_NAME ${PROJECT_NAME})

find_package(
     Qt5
     COMPONENTS Widgets
     REQUIRED
)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})


add_subdirectory(nmh)


add_executable(${APPLICATION_NAME})
target_sources(
     ${APPLICATION_NAME}
     PRIVATE
          request_listener.cpp
          response_sender.cpp
          request_router.cpp
          application.cpp
          main.cpp
)
target_link_libraries(
     ${APPLICATION_NAME}
     PRIVATE
          Qt5::Widgets
          nmh
)
target_compile_options(
     ${APPLICATION_NAME}
     PRIVATE
          -Wall
          -Werror
          -pedantic
          $<$<CONFIG:DEBUG>:-ggdb3 -O0 -fno-inline>
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
     PUBLIC
          ${CMAKE_CURRENT_SOURCE_DIR}
)

include(GNUInstallDirs)
set_target_properties(
     ${APPLICATION_NAME}
     PROPERTIES
          INSTALL_RPATH $ORIGIN/../${CMAKE_INSTALL_LIBDIR}
)


install(TARGETS ${APPLICATION_NAME})


add_subdirectory(google-chrome)
