CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
set(PROJECT_NAME_STR allocators_test)
project(${PROJECT_NAME_STR})

include(FindCUDA)

if (MSVC)
    option(gtest_force_shared_crt 
            "Use shared (DLL) run-time lib even when Google Test is built as static lib." ON)
    option(gmock_force_shared_crt 
            "Use shared (DLL) run-time lib even when Google Test is built as static lib." ON)
endif()

include_directories(${allocators_include}
                    ${CUDA_INCLUDE_DIRS}
                    ${gtest_SOURCE_DIR}/include)

file(GLOB tests ${PROJECT_SOURCE_DIR}/*test.cpp)

foreach(test_file ${tests})
  get_filename_component(test_name ${test_file} NAME_WE)
  add_executable(${test_name} ${test_file})
  target_link_libraries(${test_name} ${CUDA_LIBRARIES} gtest gtest_main)
endforeach()
