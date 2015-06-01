cmake_minimum_required(VERSION 3.2)
project(json_validation_example)

set(STATIC_LIB ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES src/main.cpp)

include_directories(./deps/wjelement/include)

add_executable(json_validation_example ${SOURCE_FILES})
target_link_libraries(json_validation_example wjreader wjelement)

add_subdirectory(./deps/wjelement)