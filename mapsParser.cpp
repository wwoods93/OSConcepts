/*
 *  pmapParser.cpp
 */

#include "parserFunctions.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

int main()
{
    std::ifstream pmapFile("pmapx.txt");
    std::vector <MapEntries> mapEntries;
    Permissions perms;
    int pos = 0;

    for (std::string entry; std::getline(pmapFile, entry);)
    {
        if (pos > 20)
            break;
        mapEntries.push_back(MapEntries());

        // parse hex address
        std::string hexAddr = entry.substr(0, entry.find(' '));
        // locate mapping size in input line by finding first numeric after hex address
        std::size_t bytesPos = entry.find_first_of(numeric, hexAddr.length() + 1);
        std::string bytes    = entry.substr(bytesPos, entry.find(' ', bytesPos) - bytesPos);
        mapEntries[pos].addr = convertHex(hexAddr);
        mapEntries[pos].size = convertStr(bytes);

        // parse resident set size (RSS)
        std::size_t RSSPos = entry.find_first_of(numeric, bytesPos + bytes.length());
        std::string RSS    = entry.substr(RSSPos, entry.find(' ', RSSPos) - RSSPos);
        mapEntries[pos].rss = convertStr(RSS);

        // parse dirty pages
        std::size_t dirtyPos = entry.find_first_of(numeric, RSSPos + RSS.length());
        std::string dirty    = entry.substr(dirtyPos, entry.find(' ', dirtyPos) - dirtyPos);
        mapEntries[pos].dirty = convertStr(dirty);

        // parse mode
        std::string mode = entry.substr(entry.find_first_of("-r"), 5);
        mapEntries[pos].modes = mode;
        countMode(mode, perms);

        // parse mapping
        std::string mapping = entry.substr(entry.rfind(' '), entry.size() - entry.rfind(' '));
        mapEntries[pos].mapping = mapping;
        std::cout << mapping << std::endl;

        ++pos;
    }
/*
    for (int i = 0; i < mapEntries.size(); ++i)
        std::cout << i + 1 << "\t" << mapEntries[i].addr << "\t\t\t" << mapEntries[i].size << "\t\t" << mapEntries[i].rss << "\t\t" << mapEntries[i].dirty << std:: endl;
*/
    printOutput(perms);

    return 0;
}