CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
set(PROJECT_NAME_STR template_matching)
PROJECT(${PROJECT_NAME_STR})

FIND_PACKAGE(CUDA REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/src
                    ${CUDA_INCLUDE_DIRS})

file (GLOB files ${PROJECT_SOURCE_DIR}/src/*.cu)

cuda_add_library(${PROJECT_NAME_STR} ${files})

add_subdirectory(perf)
add_subdirectory(test)
