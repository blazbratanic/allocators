CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
set(PROJECT_NAME_STR allocators)
PROJECT(${PROJECT_NAME_STR} CXX)

option(build_tests "Build tests for allocators" ON)

set(${PROJECT_NAME_STR}_include ${PROJECT_SOURCE_DIR}/include/allocators)

file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/include/allocators/*.hpp)
set(SRC_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_executable(${PROJECT_NAME_STR} ${SRC_FILES} ${HEADER_FILES})

if(${build_tests})
    add_subdirectory(ext/googletest)
    add_subdirectory(test)
endif()
