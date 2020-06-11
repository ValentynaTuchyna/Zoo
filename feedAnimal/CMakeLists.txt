cmake_minimum_required(VERSION 3.16)
project(feedAnimal)

set(CMAKE_CXX_STANDARD 11)

add_executable(feedAnimal main.cpp)
find_package(CppKafka REQUIRED)
target_link_libraries(feedAnimal CppKafka::cppkafka)