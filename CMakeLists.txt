cmake_minimum_required(VERSION 3.0)

# set the project name and version
project(lgff VERSION 0.0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LGFF_TARGET_NAME lgff)


add_library(
    ${LGFF_TARGET_NAME}
    STATIC
)

target_include_directories(
    ${LGFF_TARGET_NAME}
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_sources(
    ${LGFF_TARGET_NAME}
    PRIVATE
    src/LogitechForceFeedback.cpp
    src/LogitechG29.cpp
)

target_link_libraries(
    ${LGFF_TARGET_NAME}
    libhid
)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
include(cmake/libhid.cmake)



# add tests
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    enable_testing()
    add_subdirectory(tests)
endif()