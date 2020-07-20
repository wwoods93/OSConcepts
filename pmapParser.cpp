/*
 *  pmapParser.cpp
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

int main()
{
    std::ifstream pmapFile("pmapx.txt");
    using AddrSizePair = std::pair<long, long>;

    // vector of <address, mapping size> pairs
    std::vector<AddrSizePair> mappings;
    std::vector<long>RSSValues;
    std::vector<long>dirtyPagesValues;
    std::vector<std::string>modeList;
    std::string numeric = "0123456789";

    int rCount = 0;
    int wCount = 0;
    int xCount = 0;
    int sCount = 0;
    int pCount = 0;
    int noPerms = 0;
    int allPerms = 0;
    

    for (std::string mapping; std::getline(pmapFile, mapping);)
    {
        std::string::iterator itr = mapping.begin();

        // get hex address
        std::string hexAddr = mapping.substr(0, mapping.find(' '));
        std::stringstream hex(hexAddr);
        long decAddr = 0;
        itr += hexAddr.size();

        // convert hex to decimal
        hex >> std::hex >> decAddr;

        // locate mapping size in input line by finding first numeric after hex address
        std::size_t foundMapSize  = mapping.find_first_of(numeric, hexAddr.length() + 1);
        std::string stringMapSize = mapping.substr(foundMapSize, mapping.find(' ', foundMapSize) - foundMapSize);
        std::stringstream mapSizeSS(stringMapSize);
        long mapBytes = 0;
        mapSizeSS >> mapBytes;
        mapBytes *= 1000;
        mappings.push_back(std::make_pair(decAddr, mapBytes));

        // resident set size (RSS)
        std::size_t foundRSS  = mapping.find_first_of(numeric, foundMapSize + stringMapSize.length());
        std::string stringRSS = mapping.substr(foundRSS, mapping.find(' ', foundRSS) - foundRSS);
        std::stringstream setSizeSS(stringRSS);
        long RSS = 0;
        setSizeSS >> RSS;
        RSS *= 1000;
        RSSValues.push_back(RSS);

        // dirty pages
        std::size_t foundDirtyPages  = mapping.find_first_of(numeric, foundRSS + stringRSS.length());
        std::string stringDirtyPages = mapping.substr(foundDirtyPages, mapping.find(' ', foundDirtyPages) - foundDirtyPages);
        std::stringstream dirtyPagesSS(stringDirtyPages);
        long dirtyPages = 0;
        dirtyPagesSS >> dirtyPages;
        dirtyPages *= 1000;
        dirtyPagesValues.push_back(dirtyPages);

        // now parse mode
        // (r)ead (w)rite e(x)ecute (s)hared (p)rivate
        std::string mode = mapping.substr(mapping.find_first_of("-r"), 5);
        modeList.push_back(mode);
        if (mode[0] == 'r')
            ++rCount;
        if (mode[1] == 'w')
            ++wCount;
        if (mode[2] == 'x')
            ++xCount;
        if (mode[3] == 's')
            ++sCount;
        if (mode[4] == 'p')
            ++pCount;
        if (mode == "-----")
            ++noPerms;
        if (mode == "rwxsp")
            ++allPerms;

    }

    for (int i = 0; i < mappings.size(); ++i)
        std::cout << i + 1 << "\t" << mappings[i].first << "\t\t\t" << mappings[i].second << "\t\t" << RSSValues[i] << "\t\t" << dirtyPagesValues[i] << std:: endl;

    std::cout << "____________________________" << std::endl;
    std::cout << "Readable:        " << rCount << std::endl;
    std::cout << "Writable:        " << wCount << std::endl;
    std::cout << "Executable:      " << xCount << std::endl;
    std::cout << "Sharable:        " << sCount << std::endl;
    std::cout << "Private:         " << pCount << std::endl;
    std::cout << "No permissions:  " << noPerms << std::endl;
    std::cout << "All permissions: " << allPerms << std::endl;





    return 0;

}