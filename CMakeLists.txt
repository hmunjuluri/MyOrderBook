cmake_minimum_required(VERSION 3.9)
project(MyOrderBook)

set(CMAKE_CXX_STANDARD 11)

add_executable(MyOrderBook main.cpp)

include_directories(OrderBook)

add_subdirectory(OrderBook)
add_subdirectory(OrderBookTests)

target_link_libraries(MyOrderBook OrderBook)