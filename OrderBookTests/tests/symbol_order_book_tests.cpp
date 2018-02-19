//
// Created by Hanuma Munjuluri on 2/19/18.
//

#include <types.h>
#include "symbol_order_book.h"
#include "gtest/gtest.h"

TEST(OrderBookTests, TestSymbolAddOrder)
{
    SymbolOrderBook sob;
    EXPECT_TRUE(sob.isEmpty());

    Order order1 = { Side::BID, 100, 500 };
    SymbolOrderId soid = sob.addOrder(Symbol("ABC"), order1);

    EXPECT_FALSE(sob.isEmpty());
    EXPECT_EQ("ABC", soid.symbol);
    boost::optional<Size> orderSize1 = sob.getOrderSize(soid);
    EXPECT_TRUE(orderSize1.is_initialized());
    EXPECT_EQ(Size(500), orderSize1.get());
}

TEST(OrderBookTests, TestSumbolUpdateOrder)
{
    SymbolOrderBook sob;

    Order order1 = { Side::BID, 100, 500 };
    SymbolOrderId soid = sob.addOrder(Symbol("ABC"), order1);
    boost::optional<Size> orderSize1 = sob.getOrderSize(soid);
    EXPECT_TRUE(orderSize1.is_initialized());
    EXPECT_EQ(Size(500), orderSize1.get());

    sob.updateOrder(soid, Size(400));
    orderSize1 = sob.getOrderSize(soid);
    EXPECT_TRUE(orderSize1.is_initialized());
    EXPECT_EQ(Size(400), orderSize1.get());
}

TEST(OrderBookTests, TestSymbolCancelOrder)
{
    SymbolOrderBook sob;

    Order order1 = { Side::BID, 100, 500 };
    SymbolOrderId soid = sob.addOrder(Symbol("ABC"), order1);
    boost::optional<Size> orderSize1 = sob.getOrderSize(soid);
    EXPECT_TRUE(orderSize1.is_initialized());
    EXPECT_EQ(Size(500), orderSize1.get());

    sob.cancelOrder(soid);
    orderSize1 = sob.getOrderSize(soid);
    EXPECT_TRUE(orderSize1.is_initialized());
    EXPECT_EQ(Size(0), orderSize1.get());
}