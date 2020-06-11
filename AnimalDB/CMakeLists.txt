cmake_minimum_required(VERSION 3.16)
project(AnimalDB)

set(CMAKE_CXX_STANDARD 11)

add_executable(AnimalDB main.cpp Zoo.h Animal.h)

set(Boost_INCLUDE_DIR /usr/include/boost)
set(Boost_LIBRARY_DIR /usr/lib/x86_64-linux-gnu)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(AnimalDB ${Boost_LIBRARIES})

set(Mysqlpp_INCLUDE_DIR /usr/include/mysql++)
set(Mysql_INCLUDE_DIR /usr/include/mysql)
include_directories(${Mysqlpp_INCLUDE_DIR})
include_directories(${Mysql_INCLUDE_DIR})
target_link_libraries(AnimalDB /usr/lib/x86_64-linux-gnu/libmysqlclient.so)
target_link_libraries(AnimalDB /usr/lib/x86_64-linux-gnu/libmysqlpp.so)


find_package(CppKafka REQUIRED)
target_link_libraries(AnimalDB CppKafka::cppkafka)