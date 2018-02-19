# MyOrderBook
OrderBook

To Generate Makefile:

    mkdir build
    cd build
    cmake ..

To Build:

    cd build
    make


Following are few notes.

1. I have used Google Test framework for unit test cases.
2. I have used cmake to to generate Makefiles. So Makefile is not part of the repository, but it can be generated from CMakeList.txt
3. Source files are in MyOrderBook/OrderBook folder and unit testing code is in MyOrderBook/OrderBookTests
4. OrderBook/order_book.cpp/.h - Implements OrderBook class for a single security
    OrderBook/symbol_order_book.cpp/.h - Wraps around OrderBook and is used for order book for multiple securities.
5. OrderBookTests/order_book_tests.cpp - Tests OrderBook (single security) functionality. Most of the test cases are implemented here.
    OrderBookTests/symbol_order_book_tests.cpp - Tests OrderBook for multiple securities
