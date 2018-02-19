cmake_minimum_required(VERSION 3.9)
project(OrderBook)

find_package(Boost 1.66 COMPONENTS REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )

set(HEADER_FILES order_book.h)
set(SOURCE_FILES order_book.cpp types.h)

add_library(OrderBook STATIC ${SOURCE_FILES})