//
// Created by Hanuma Munjuluri on 2/18/18.
//

#pragma once

#include "types.h"
#include <boost/noncopyable.hpp>
#include <boost/intrusive/slist.hpp>
#include <boost/optional.hpp>
#include <vector>
#include <unordered_map>

class OrderBook {
private:
    struct OrderSize : public boost::intrusive::slist_base_hook<> {
        Size size = {0};
    };

    typedef boost::intrusive::slist<OrderSize, boost::intrusive::cache_last<true> > OrdersAtPrice;
    typedef std::vector<OrdersAtPrice> PricePoints;
    PricePoints bids, asks;

    std::unordered_map<OrderId, OrderSize> ordersMap;

    OrderId currentOrderId;
    // Minimum Ask price
    Price minAskPrice;
    // Maximum Bid price
    Price maxBidPrice;

public:
    ~OrderBook();
    OrderBook();

    OrderId addOrder(Order order);
    void updateOrder(OrderId orderId, Size newSize);
    void cancelOrder(OrderId orderId);
    inline Price getMinAskPrice() { return minAskPrice; }
    inline Price getMaxBidPrice() { return maxBidPrice; }
    std::vector<Order> getOrdersInPriceRange(Price start, Price end, Side side);


    //Helper functions
    inline OrderId getCurrentOrderId() { return currentOrderId; }
    inline Price getBidsSize() { return bids.size(); }
    inline Price getAsksSize() { return asks.size(); }
    boost::optional<Size> getOrderSize(OrderId orderId);
    Size getTotalSizeAtPrice(Price price, Side side);



};
