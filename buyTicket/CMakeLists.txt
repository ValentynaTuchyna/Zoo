cmake_minimum_required(VERSION 3.16)
project(buyTicket)

set(CMAKE_CXX_STANDARD 11)

add_executable(buyTicket main.cpp)
find_package(CppKafka REQUIRED)
target_link_libraries(buyTicket CppKafka::cppkafka)