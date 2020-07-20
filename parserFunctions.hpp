/*
 *  parserFunctions.hpp
 */
#ifndef PARSER_FUNCTIONS_HPP
#define PARSER_FUNCTIONS_HPP
#include <iostream>
#include <string>
#include <vector>

struct MapEntries;
struct Permissions;
const std::string numeric = "0123456789";

int convertStr(std::string input);
long convertHex(std::string hexString);
void countMode(std::string mode, Permissions& perms);
void printOutput(const Permissions& perms);

#endif