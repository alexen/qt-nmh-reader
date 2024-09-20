set(LIBRARY_NAME nmh)

add_library(${LIBRARY_NAME})
target_sources(
     ${LIBRARY_NAME}
     PRIVATE
          io.cpp
)
target_link_libraries(
     ${LIBRARY_NAME}
     PRIVATE
          Qt5::Core
)
target_include_directories(
     ${LIBRARY_NAME}
     PRIVATE
          ${CMAKE_SOURCE_DIR}/backend
)
if(BUILD_TESTING)
     set(UT_NAME test-${LIBRARY_NAME})
     add_executable(${UT_NAME})
     target_sources(
          ${UT_NAME}
          PRIVATE
               test/test_io.cpp
     )
     target_link_libraries(
          ${UT_NAME}
          PRIVATE
               ${LIBRARY_NAME}
               Qt5::Core
               GTest::gtest
               GTest::gtest_main
     )
     add_test(${LIBRARY_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${UT_NAME})
endif()
