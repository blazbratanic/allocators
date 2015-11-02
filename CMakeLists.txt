CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
set(PROJECT_NAME_STR allocators)
PROJECT(${PROJECT_NAME_STR})

include(FindCUDA)

include_directories(${PROJECT_SOURCE_DIR}/src
                    ${CUDA_INCLUDE_DIRS})

file (GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file (GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/src/*.hpp)

add_executable(${PROJECT_NAME_STR} ${SRC_FILES} ${HEADER_FILES})

message(STATUS ${CUDA_LIBRARIES})
target_link_libraries(${PROJECT_NAME_STR} ${CUDA_LIBRARIES})
