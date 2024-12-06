cmake_minimum_required(VERSION 3.10)

project(DesignPatternsDeepLearning)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

add_subdirectory(framework/data)
add_subdirectory(framework/nn)
add_subdirectory(framework/util)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE data nn util ${Python3_LIBRARIES})

target_include_directories(main PRIVATE
    ${CMAKE_SOURCE_DIR}/framework/util
    ${CMAKE_SOURCE_DIR}/framework/data
    ${CMAKE_SOURCE_DIR}/framework/nn
    ${Python3_INCLUDE_DIRS}
)
