cmake_minimum_required(VERSION 2.8.3)

project(any_json)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall")

set(3rdpary 3rdparty)

include_directories(
    include
    ${3rdparty}/rapidjson
    )

aux_source_directory(src src_dir)
set(src_list ${src_dir} main.cpp)

add_executable(${PROJECT_NAME} ${src_list})
