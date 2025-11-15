//
//  main.cpp
//  Exchanger
//
//  Created by Laurence Burden on 11/13/25.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "src/OrderBookType.hpp"
#include "src/OrderBookEntry.hpp"
#include "src/ExchangerMain.hpp"
#include "src/FileParser.hpp"

std::vector<std::string> readOrderData();
void processOrderData(std::vector<std::string>*, std::vector<OrderBookEntry>*);
OrderBookType stoobt(std::string);

int main() {
    const std::string filepath = "/Users/laurenceburden/Documents/Development/Exchanger/Exchanger/data/market_data.csv";
    std::vector<std::string> orderDataText = readOrderData();
    FileParser parser{filepath};
    std::vector<OrderBookEntry> orders;
    
    //processOrderData(&orderDataText, &orders);
    orders = parser.getOrders();
    ExchangerMain main(orders);

    main.init();

    return 0;
}

// REGION: Function implementations
std::vector<std::string> readOrderData() {
    std::vector<std::string> orderData;
    std::ifstream csvFile{};
    std::string line;
    
    csvFile.open("/Users/laurenceburden/Documents/Development/Exchanger/Exchanger/data/market_data.csv");
    
    if (csvFile.is_open()) {
        while(std::getline(csvFile, line)) {
            orderData.push_back(line);
        }
    } else {
        std::cout << "ERROR READING FILE" << std::endl;
    }
    
    csvFile.close();

    return orderData;
}

void processOrderData(std::vector<std::string> *ptrOrderDataText, std::vector<OrderBookEntry> *ptrOrders) {
    std::vector<std::string> tempOO; //temporary Order object
    std::string::size_type n;
    OrderBookType orderType;
    char del = ','; // Delimiter

    for (int i = 0; i < (*ptrOrderDataText).size(); i++) {
        n = (*ptrOrderDataText)[i].find(del);
        
        while(n != std::string::npos) {
            tempOO.push_back((*ptrOrderDataText)[i].substr(0, n));
            (*ptrOrderDataText)[i].erase(0, n + 1);
            n = (*ptrOrderDataText)[i].find(del);
        }

        if ((*ptrOrderDataText)[i].length() >= 1) {
            // Get the text after the last deliminator
            tempOO.push_back((*ptrOrderDataText)[i]);
        }

        if (tempOO.size() == 5) { // We have the right amount of info
            orderType = stoobt(tempOO[2]);
            (*ptrOrders).push_back(OrderBookEntry{
                stod(tempOO[3]), stod(tempOO[4]), tempOO[0], tempOO[1], orderType
            });
        }

        tempOO.clear(); // Reset for next run
    }
}

/**
 * Transforms a string of value "ask" or "bid" to the corrisponding OrderBookType value
 */
OrderBookType stoobt(std::string orderTypeText) {
    if (orderTypeText == "bid") {
        return OrderBookType::bid;
    } else if (orderTypeText == "ask"){
        return OrderBookType::ask;
    } else {
        return OrderBookType::error;
    }
}

