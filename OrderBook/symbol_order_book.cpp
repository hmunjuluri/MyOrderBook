//
// Created by Hanuma Munjuluri on 2/19/18.
//

#include "symbol_order_book.h"
#include "types.h"


OrderId SymbolOrderBook::getCurrentOrderId(const Symbol &s) {
    return symbolOrderBook[s].getCurrentOrderId();
}
Price SymbolOrderBook::getMinAskPrice(const Symbol &s) {
    return symbolOrderBook[s].getMinAskPrice();
}
Price SymbolOrderBook::getMaxBidPrice(const Symbol &s) {
    return symbolOrderBook[s].getMaxBidPrice();
}
Price SymbolOrderBook::getBidsSize(const Symbol &s) {
    return symbolOrderBook[s].getBidsSize();
}
Price SymbolOrderBook::getAsksSize(const Symbol &s) {
    return symbolOrderBook[s].getAsksSize();
}

boost::optional<Size> SymbolOrderBook::getOrderSize(const SymbolOrderId &soid) {
    return symbolOrderBook[soid.symbol].getOrderSize(soid.orderId);
}
Size SymbolOrderBook::getTotalSizeAtPrice(const Symbol &symbol, Price price, Side side) {
    return symbolOrderBook[symbol].getTotalSizeAtPrice(price, side);
}

SymbolOrderId SymbolOrderBook::addOrder(const Symbol &symbol, Order order) {
    SymbolOrderId symbolOrderId;
    symbolOrderId.symbol = symbol;
    symbolOrderId.orderId = symbolOrderBook[symbol].addOrder(order);

    return symbolOrderId;
}

void SymbolOrderBook::updateOrder(SymbolOrderId symbolOrderId, Size newSize) {
    return symbolOrderBook[symbolOrderId.symbol].updateOrder(symbolOrderId.orderId, newSize);
}

void SymbolOrderBook::cancelOrder(SymbolOrderId symbolOrderId) {
    return symbolOrderBook[symbolOrderId.symbol].cancelOrder(symbolOrderId.orderId);
}
