//
//  OrderBookEntry.hpp
//  Exchanger
//
//  Created by Laurence Burden on 11/13/25.
//

#ifndef OrderBookEntry_hpp
#define OrderBookEntry_hpp

#include <string>
#include "OrderBookType.hpp"

class OrderBookEntry {
    private:
        double amount, price;
        std::string timestamp, products;
        OrderBookType orderType;

    public:
        OrderBookEntry(double, double, std::string, std::string, OrderBookType);
        double getAmount();
        double getPrice();
        std::string getTimestamp();
        std::string getProducts();
        OrderBookType getOrderType();
        std::string getOrderTypeText();

        void setAmount(double);
        void setPrice(double);
        void setTimestamp(std::string);
        void setProducts(std::string);
        void setOrderType(OrderBookType);
};

#endif /* OrderBookEntry_hpp */
