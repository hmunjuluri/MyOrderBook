cmake_minimum_required(VERSION 3.9)
project(OrderBook)

find_package(Boost 1.66 COMPONENTS REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )

set(HEADER_FILES order_book.h symbol_order_book.h types.h)
set(SOURCE_FILES order_book.cpp symbol_order_book.cpp)

add_library(OrderBook STATIC ${SOURCE_FILES} ${HEADER_FILES})