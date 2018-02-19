//
// Created by Hanuma Munjuluri on 2/18/18.
//

#include "order_book.h"

OrderBook::OrderBook() {
    /* Initialize bids and asks array */
    bids.resize(MAX_PRICE);
    for (auto& b : bids) {
        b.clear();
    }
    asks.resize(MAX_PRICE);
    for (auto& a : asks) {
        a.clear();
    }

    currentOrderId = 0;
    minAskPrice = MAX_PRICE;
    maxBidPrice = MIN_PRICE;
}

OrderId OrderBook::addOrder(Order order) {
    Price price = order.price;
    Size orderSize = order.size;

    bool isPriceCrossing = (order.side == Side::BID) ? (price >= minAskPrice) : (price <= maxBidPrice);
    PricePoints &pricePoints = (order.side == Side::BID) ? asks : bids;
    Price &offset = (order.side == Side::BID) ? minAskPrice : maxBidPrice;

    // Can this order be immediately filled without adding to orderbook
    // This order is offering more than someone willing to accept to sell
    while (isPriceCrossing) {
        auto priceIter = pricePoints.begin() + offset;
        OrdersAtPrice &ordersAtPrice = *priceIter;

        auto orderIter = ordersAtPrice.begin();

        //Iterate through all sizes at this price level
        while (orderIter != ordersAtPrice.end()) {
            if (orderSize > orderIter->size) {
                // Case 1: Incoming order size is greater than current order size
                // Order not fully filled yet
                orderSize -= orderIter->size;
                ++orderIter;
            } else {
                //Case 2: Order can be fully filled. No need to add to OrderBook
                if( orderSize < orderIter->size ) {
                    orderIter->size -= orderSize;
                } else {
                    orderIter->size = Size(0);
                    ++orderIter;
                }

                while (ordersAtPrice.begin() != orderIter) {
                    ordersAtPrice.pop_front();
                }
                return ++currentOrderId;
            }
        }

        // At this point we ran out of shares at this price. Try the next best price
        ordersAtPrice.clear();

        if(order.side == Side::BID) {
            priceIter++;
            offset++;
            isPriceCrossing =  (price >= minAskPrice);
        } else {
            priceIter--;
            maxBidPrice--;
            isPriceCrossing = (price <= maxBidPrice);
        }
    }

    // Add any remaining size to orderbook
    OrderSize &entry = ordersMap[++currentOrderId];
    entry.size = orderSize;
    if(order.side == Side::BID) {
        bids[price].push_back(entry);
        if (price > maxBidPrice) maxBidPrice = price;
    } else {
        asks[price].push_back(entry);
        if (price < minAskPrice) minAskPrice = price;
    }
    return currentOrderId;
}


void OrderBook::updateOrder(OrderId orderId, Size newSize) {
    ordersMap[orderId].size = newSize;
}

void OrderBook::cancelOrder(OrderId orderId) {
    ordersMap[orderId].size = 0;
}

boost::optional<Size> OrderBook::getOrderSize(OrderId orderId) {
    boost::optional<Size> result;
    auto iter = ordersMap.find(orderId);
    if( iter != ordersMap.end() )
    {
        result = iter->second.size;
    }
    return result;
}

Size OrderBook::getTotalSizeAtPrice(Price price, Side side) {
    Size totalSize=0;
    PricePoints &pricePoints = (side == Side::BID) ? bids : asks;
    auto priceIter = pricePoints.begin() + price;
    OrdersAtPrice &ordersAtPrice = *priceIter;

    for(OrdersAtPrice::iterator it=ordersAtPrice.begin(); it!= ordersAtPrice.end(); ++it)
    {
        totalSize += it->size;
    }
    return totalSize;
}

OrderBook::~OrderBook() {
    bids.clear();
    asks.clear();
}

