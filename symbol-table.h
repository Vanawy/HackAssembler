#pragma once
#include <string>
#include <map>
#include <sstream>

class SymbolTable
{
public:
  // Add new symbol with specified address
  void Set(std::string symbol, short address);
  // Add new symbol if not find and return its address
  short Insert(std::string symbol);
  // Find address of specified symbol
  short Get(std::string symbol);
  SymbolTable();
private:
  std::map<std::string, short> symbols_;
  short counter_ = 16;
};

