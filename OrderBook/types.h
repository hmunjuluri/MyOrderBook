//
// Created by Hanuma Munjuluri on 2/19/18.
//

#pragma once

#include <boost/serialization/strong_typedef.hpp>
#include <limits>
#include <string>
#include <stdint.h>

typedef unsigned long OrderId;
typedef unsigned long Size;
typedef unsigned short Price;
typedef std::string Symbol;
enum class Side {ASK,BID};

typedef struct {
    Side side;
    Price price;
    Size size;
} Order;

typedef struct {
    Symbol symbol;
    OrderId orderId;
} SymbolOrderId;

const Price MAX_PRICE = std::numeric_limits<Price>::max();
const Price MIN_PRICE = Price(1);

