//
//  FileParser.hpp
//  Exchanger
//
//  Created by Laurence Burden on 11/14/25.
//

#ifndef FileParser_hpp
#define FileParser_hpp

#include <fstream>
#include <string>
#include <vector>
#include "OrderBookEntry.hpp"

class FileParser {
    private:
        std::ifstream csvFile;
        std::string filepath;
        std::vector<OrderBookEntry> orders;
        
        bool fileIsOpen();
        void openFile();
        void closeFile();
        void parseLines();
        std::vector<std::string> tokenise(std::string, char);
        void parseAndAddOrder(std::vector<std::string>);
    
    public:
        FileParser(std::string fileName);
        ~FileParser();
        std::vector<OrderBookEntry> getOrders();
        
        
};

#endif /* FileParser_hpp */
