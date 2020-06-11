cmake_minimum_required(VERSION 3.16)
project(MainApp)

set(CMAKE_CXX_STANDARD 11)

add_executable(MainApp main.cpp Visitor.cpp Visitor.h Admin.cpp Admin.h forConnect.h)
find_package(CppKafka REQUIRED)
target_link_libraries(MainApp CppKafka::cppkafka)


set(Boost_INCLUDE_DIR /usr/include/boost)
set(Boost_LIBRARY_DIR /usr/lib/x86_64-linux-gnu)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

