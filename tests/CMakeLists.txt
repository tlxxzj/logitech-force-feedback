include(../cmake/gtest.cmake)

add_executable(
    LogitechG29Test
    src/LogitechG29Test.cpp
)
target_link_libraries(
    LogitechG29Test
    lgff
    gtest_main
)
gtest_discover_tests(
    LogitechG29Test
)