// Assembler for "Hack" computer of nand2tetris.org course
// Written by vanawy<saharchuk999@gmail.com> in 2020

#include <iostream>
#include <fstream>
#include <exception>
#include <regex>
#include "parser.h"
#include "code.h"
#include "symbol-table.h";


// Get last parsed instruction as machine code
std::string GetCode(Parser& parser, SymbolTable& symbol_table);

// arg[1] - path to input file with program in hack assembly languange (.hack)
// arg[2] (optional) - path to output file where program in hack machine language
// will be stored (.asm)
int main(int argc, char **argv)
{
  try {
    if (argc < 2) {
      throw std::exception("Specify input file as first argument");
    }

    std::ifstream input;
    const char* input_filename = argv[1];
    input.open(input_filename);
    if (!input.is_open())
    {
      throw std::exception(
        std::string("Cant open input file: ").append(input_filename).c_str()
      );
    }

    std::ofstream output;
    std::string out(input_filename);
    out = out + ".hack";
    const char* output_filename;
    output_filename = out.c_str();
    if (argc > 2) {
      output_filename = argv[2];
    }
    output.open(output_filename, std::ios::trunc | std::ios::out);
    if (!output.is_open())
    {
      throw std::exception(
        std::string("Cant open output file: ").append(output_filename).c_str()
      );
    }

    // Actual parsing

    Parser parser = Parser();
    SymbolTable symbol_table = SymbolTable();

    std::string instruction = "";
    short command_counter = 0;
    while (std::getline(input, instruction))
    {
      if (parser.parse(instruction))
      {
        if (parser.getType() == Parser::InstructionType::kLabel)
        {
          symbol_table.Set(parser.getValue(), command_counter);
        }
        else
        {
          command_counter++;
        }
      }
    }
    input.clear();
    input.seekg(0);

    while (std::getline(input, instruction))
    {
      if (parser.parse(instruction))
      {
        std::string code = GetCode(parser, symbol_table);
        //std::cout << instruction << "\t->\t" << code << std::endl;
        if (code != "") {
          output << code << std::endl;
        }
      }
    }

    input.close();
    output.close();
    return 0;
  }
  catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
    return -1;
  }
}

std::string GetCode(Parser& parser, SymbolTable& symbol_table)
{
  std::string code = "";

  Parser::InstructionType type = parser.getType();

  if (type == Parser::InstructionType::kA)
  {
    const std::regex symbol_regex("\\D");
    std::string value = parser.getValue();
    bool is_symbol = std::regex_search(value, symbol_regex);
    short address;
    if (is_symbol)
    {
      address = symbol_table.Insert(value);
    }
    else {
      address = atoi(value.c_str());
    }
    code = Code::createACommand(address);
  }
  else if (type == Parser::InstructionType::kC)
  {
    code = Code::createCCommand(
      parser.getDestination(),
      parser.getComputation(),
      parser.getJump()
    );
  }

  return code;
}

// Parser: unpacks each instruction into its underlying fields
// Code: translates each field into its corresponding binary value 
// SymbolTable: manages the symbol table 
// Main: initializes the I/O files and drives the process
