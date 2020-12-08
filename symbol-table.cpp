#include "symbol-table.h"

SymbolTable::SymbolTable()
{
  symbols_ = {
    {"SP", 0},
    {"LCL", 1},
    {"ARG", 2},
    {"THIS", 3},
    {"THAT", 4}
  };

  for (int i = 0; i < 16; i++)
  {
    std::stringstream ss;
    ss << "R" << i;
    SymbolTable::Set(ss.str(), i);
  }

  counter_ = 16;
}

void SymbolTable::Set(std::string symbol, short address)
{
  symbols_[symbol] = address;
}

short SymbolTable::Get(std::string symbol)
{
  std::map<std::string, short>::const_iterator si = symbols_.find(symbol);
  if (si == symbols_.end())
  {
    throw std::exception("Can't find address for this symbol");
  }
  return si->second;
}

short SymbolTable::Insert(std::string symbol)
{
  try 
  {
    return SymbolTable::Get(symbol);
  }
  catch (std::exception& e)
  {
    SymbolTable::Set(symbol, counter_);
    return counter_++;
  }
}