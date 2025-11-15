//
//  FileParser.cpp
//  Exchanger
//
//  Created by Laurence Burden on 11/14/25.
//

#include "FileParser.hpp"

FileParser::FileParser(std::string _filepath) : filepath(_filepath){
    openFile();
    parseLines();
}
FileParser::~FileParser() {
    if (csvFile.is_open()) {
        csvFile.close();
    }
}

std::vector<OrderBookEntry> FileParser::getOrders() {
    if (orders.size() == 0) {
        openFile();
        parseLines();
    }
        
    return orders;
}

void FileParser::openFile() {
    csvFile.open(filepath);
}

void FileParser::parseLines() {
    std::string line;
    std::vector<std::string> orderData;
    
    // Loop through each csv line, tokenise, parse it, and add it to the orders vector
    if (csvFile.is_open()) {
        while(std::getline(csvFile, line)) {
            orderData = tokenise(line, ',');
            if (orderData.size() == 5) {
                parseAndAddOrder(orderData);
            }
        }
    }
}

void FileParser::parseAndAddOrder(std::vector<std::string> orderTokens) {
    OrderBookType orderType = OrderBookEntry::stoobt(orderTokens[2]);
    
    orders.push_back(OrderBookEntry(stod(orderTokens[3]), stod(orderTokens[4]), orderTokens[0], orderTokens[1], orderType));
}

std::vector<std::string> FileParser::tokenise(std::string csvLine, char separator) {
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
    
    start = static_cast<int>(csvLine.find_first_not_of(separator, 0));
    
    do {
        end = static_cast<int>(csvLine.find_first_of(separator, start));

        if(start == csvLine.length() || start == end) {
            break;
        }else if(end >= 0) {
            token = csvLine.substr(start, end - start);
        } else {
            token = csvLine.substr(start, csvLine.length() - start);
        }
            
        tokens.push_back(token);
        start = end + 1;
        
    }while(end > 0);
    
    return tokens;
}
