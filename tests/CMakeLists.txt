cmake_minimum_required(VERSION 3.0)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY    https://github.com/google/googletest.git
    GIT_TAG           release-1.11.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


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