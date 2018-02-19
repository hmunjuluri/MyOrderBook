//
// Created by Hanuma Munjuluri on 2/19/18.
//

#include "order_book.h"
#include "gtest/gtest.h"

TEST(OrderBookTests, TestCreation)
{
    OrderBook ob;
    EXPECT_EQ(OrderId(0), ob.getCurrentOrderId());
    EXPECT_EQ(MAX_PRICE, ob.getBidsSize());
    EXPECT_EQ(MAX_PRICE, ob.getAsksSize());
    EXPECT_EQ(MAX_PRICE, ob.getMinAskPrice());
    EXPECT_EQ(Price(1), ob.getMaxBidPrice());
}

TEST(OrderBookTests, TestAddOrderNoFill)
{
    OrderBook ob;

    //Test bids
    Order order1 = { Side::BID, 100, 500 };
    OrderId orderId1 = ob.addOrder(order1);
    boost::optional<Size> orderSize1 = ob.getOrderSize(orderId1);
    EXPECT_TRUE(orderSize1.is_initialized());
    EXPECT_EQ(Size(500), orderSize1.get());

    Order order2 = { Side::BID, 100, 1000 };
    OrderId orderId2 = ob.addOrder(order2);
    boost::optional<Size> orderSize2 = ob.getOrderSize(orderId2);
    EXPECT_EQ(Size(1000), orderSize2.get());

    Size totalBidSize = ob.getTotalSizeAtPrice(100, Side::BID);
    EXPECT_EQ(Size(1500), totalBidSize);

    //Test asks
    Order order3 = { Side::ASK, 101, 500 };
    OrderId orderId3 = ob.addOrder(order3);
    boost::optional<Size> orderSize3 = ob.getOrderSize(orderId3);
    EXPECT_EQ(Size(500), orderSize3.get());

    Order order4 = { Side::ASK, 101, 1000 };
    OrderId orderId4 = ob.addOrder(order4);
    boost::optional<Size> orderSize4 = ob.getOrderSize(orderId4);
    EXPECT_EQ(Size(1000), orderSize4.get());

    Size totalAskSize = ob.getTotalSizeAtPrice(101, Side::ASK);
    EXPECT_EQ(Size(1500), totalAskSize);
}

TEST(OrderBookTests, TestAddOrderPartialFillIncoming)
{
    OrderBook ob;

    // Buy Order for 500 shares offering 100
    Order order1 = { Side::BID, 100, 500 };
    OrderId orderId1 = ob.addOrder(order1);
    boost::optional<Size> orderSize1 = ob.getOrderSize(orderId1);
    EXPECT_TRUE(orderSize1.is_initialized());
    EXPECT_EQ(Size(500), orderSize1.get());

    // Sell order for 1000 shares asking 99.
    Order order2 = { Side::ASK, 99, 1000 };
    OrderId orderId2 = ob.addOrder(order2);
    boost::optional<Size> orderSize2 = ob.getOrderSize(orderId2);
    EXPECT_TRUE(orderSize2.is_initialized());
    EXPECT_EQ(Size(500), orderSize2.get());

    // Sell order should be partially filled with remaining shares 500
    Size totalAskSize = ob.getTotalSizeAtPrice(99, Side::ASK);
    EXPECT_EQ(Size(500), totalAskSize);

    // Buy order should be completely filled
    Size totalBidSize = ob.getTotalSizeAtPrice(100, Side::BID);
    EXPECT_EQ(Size(0), totalBidSize);
}

TEST(OrderBookTests, TestAddOrderPartialFillExisting)
{
    OrderBook ob;

    // Buy Order for 1000 shares offering 100
    Order order1 = { Side::BID, 100, 1000 };
    OrderId orderId1 = ob.addOrder(order1);
    boost::optional<Size> orderSize1 = ob.getOrderSize(orderId1);
    EXPECT_TRUE(orderSize1.is_initialized());
    EXPECT_EQ(Size(1000), orderSize1.get());

    // Sell order for 500 shares asking 99. This order should be completely filled
    // Without adding to Order Book
    Order order2 = { Side::ASK, 99, 500 };
    OrderId orderId2 = ob.addOrder(order2);
    boost::optional<Size> orderSize2 = ob.getOrderSize(orderId2);
    EXPECT_FALSE(orderSize2.is_initialized());

    // Sell order should be completely filled
    Size totalAskSize = ob.getTotalSizeAtPrice(99, Side::ASK);
    EXPECT_EQ(Size(0), totalAskSize);

    // Buy order should be partially filled
    Size totalBidSize = ob.getTotalSizeAtPrice(100, Side::BID);
    EXPECT_EQ(Size(500), totalBidSize);

}


TEST(OrderBookTests, TestAddOrderCompleteFill)
{
    OrderBook ob;

    //Test bids
    Order order1 = { Side::BID, 100, 500 };
    OrderId orderId1 = ob.addOrder(order1);
    boost::optional<Size> orderSize1 = ob.getOrderSize(orderId1);
    EXPECT_TRUE(orderSize1.is_initialized());
    EXPECT_EQ(Size(500), orderSize1.get());

    //Test asks
    Order order2 = { Side::ASK, 100, 500 };
    OrderId orderId2 = ob.addOrder(order2);
    boost::optional<Size> orderSize2 = ob.getOrderSize(orderId2);
    EXPECT_FALSE(orderSize2.is_initialized());


    Size totalAskSize = ob.getTotalSizeAtPrice(100, Side::ASK);
    EXPECT_EQ(Size(0), totalAskSize);
    Size totalBidSize = ob.getTotalSizeAtPrice(100, Side::BID);
    EXPECT_EQ(Size(0), totalBidSize);

    //OrderId1 should still be existing with zero size
    orderSize1 = ob.getOrderSize(orderId1);
    EXPECT_TRUE(orderSize1.is_initialized());
    EXPECT_EQ(Size(0), orderSize1.get());
}

TEST(OrderBookTests, TestUpdateOrder)
{
    OrderBook ob;

    Order order1 = { Side::BID, 100, 500 };
    OrderId orderId1 = ob.addOrder(order1);
    boost::optional<Size> orderSize1 = ob.getOrderSize(orderId1);
    EXPECT_TRUE(orderSize1.is_initialized());
    EXPECT_EQ(Size(500), orderSize1.get());

    ob.updateOrder(orderId1, Size(400));
    orderSize1 = ob.getOrderSize(orderId1);
    EXPECT_TRUE(orderSize1.is_initialized());
    EXPECT_EQ(Size(400), orderSize1.get());
}

TEST(OrderBookTests, TestCancelOrder)
{
    OrderBook ob;

    Order order1 = { Side::BID, 100, 500 };
    OrderId orderId1 = ob.addOrder(order1);
    boost::optional<Size> orderSize1 = ob.getOrderSize(orderId1);
    EXPECT_TRUE(orderSize1.is_initialized());
    EXPECT_EQ(Size(500), orderSize1.get());

    ob.cancelOrder(orderId1);
    orderSize1 = ob.getOrderSize(orderId1);
    EXPECT_TRUE(orderSize1.is_initialized());
    EXPECT_EQ(Size(0), orderSize1.get());
}