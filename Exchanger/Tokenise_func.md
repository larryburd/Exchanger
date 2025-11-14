string csvLine = 'thing,thing2,thing3'
string vector tokens
char seperator = ','

int start, end

start = csvLine.find_first_not_of(separator)
do
    end = next 'separator' after start
    if start == csvLine.length or start == end ## Nothing more to find
        break
    if end >= 0 ## found next separator
        token = csvLine.substr(start, end - start)
    else
        token = csvLine.substr(start, csvLine.length - start)
        
    tokens.push_back(token)
    start = end + 1
while (end > 0)
