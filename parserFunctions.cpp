/*
 *  parserFunctions.cpp
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "parserFunctions.hpp"

struct MapEntries
{
    long addr = 0;
    int size = 0;
    int rss = 0;
    int dirtyPages = 0;
    std::string modes = "";
    std::string mapping = "";
};

struct Permissions
{
    int r = 0;
    int w = 0;
    int x = 0;
    int s = 0;
    int p = 0;
    int none = 0;
    int all = 0;
};

int convertStr(std::string input)
{
    std::stringstream inputSS(input);
    int outputLong = 0;
    inputSS >> outputLong;
    return outputLong * 1000;
}

long convertHex(std::string hexString)
{
    std::stringstream hex(hexString);
    long decAddr = 0;
    hex >> std::hex >> decAddr;
    return decAddr;
}

void countMode(std::string mode, Permissions& perms)
{
    if (mode[0] == 'r')
        ++perms.r;
    if (mode[1] == 'w')
        ++perms.w;
    if (mode[2] == 'x')
        ++perms.x;
    if (mode[3] == 's')
        ++perms.s;
    if (mode[4] == 'p')
        ++perms.p;
    if (mode == "-----")
        ++perms.none;
    if (mode == "rwxsp")
        ++perms.all;
}

void printOutput(const Permissions& perms)
{
    std::cout << "____________________________" << std::endl;
    std::cout << "Readable:        " << perms.r << std::endl;
    std::cout << "Writable:        " << perms.w << std::endl;
    std::cout << "Executable:      " << perms.x << std::endl;
    std::cout << "Sharable:        " << perms.s << std::endl;
    std::cout << "Private:         " << perms.p << std::endl;
    std::cout << "No permissions:  " << perms.none << std::endl;
    std::cout << "All permissions: " << perms.all << std::endl;
}