//
// Created by Hanuma Munjuluri on 2/19/18.
//

#pragma once

#include "order_book.h"
#include "types.h"
#include <map>


class SymbolOrderBook {
private:
    std::map<Symbol, OrderBook> symbolOrderBook;

public:
    SymbolOrderBook()  {}

    ~SymbolOrderBook() {}

    SymbolOrderId addOrder(const Symbol &symbol, Order order);
    void updateOrder(SymbolOrderId symbolOrderId, Size newSize);
    void cancelOrder(SymbolOrderId symbolOrderId);


    //Helper functions
    OrderId getCurrentOrderId(const Symbol &s);
    Price getMinAskPrice(const Symbol &s);
    Price getMaxBidPrice(const Symbol &s);
    Price getBidsSize(const Symbol &s);
    Price getAsksSize(const Symbol &s);

    boost::optional<Size> getOrderSize(const SymbolOrderId &soid);
    Size getTotalSizeAtPrice(const Symbol &symbol, Price price, Side side);
};
