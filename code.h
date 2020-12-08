#pragma once
#include <string>
#include <bitset>
#include <map>
#include <regex>
#include <sstream>
#include <cstdlib>

class Code
{
public:
	static std::string createACommand(short address);
	static std::string createCCommand(std::string destination, std::string computation, std::string jump);
private:
	static std::string toBinary15(short number);
};

