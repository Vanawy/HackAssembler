#include "Code.h"

std::string Code::createACommand(short value)
{
	return "0" + Code::toBinary15(value);
}

std::string Code::createCCommand(std::string destination, std::string computation, std::string jump)
{
	std::string command = "111";

	std::map<std::string, std::string> computations = {
		{"0", "0101010"},
		{"1", "0111111"},
		{"-1", "0111010"},
		{"D", "0001100"},
		{"A", "0110000"},
		{"M", "1110000"},
		{"!D", "0001101"},
		{"!A", "0110001"},
		{"!M", "1110001"},
		{"-D", "0001101"},
		{"-A", "0110011"},
		{"-M", "1110011"},
		{"D+1", "0011111"},
		{"A+1", "0110111"},
		{"M+1", "1110111"},
		{"D-1", "0001110"},
		{"A-1", "0110010"},
		{"M-1", "1110010"},
		{"D+A", "0000010"},
		{"A+D", "0000010"},
		{"D+M", "1000010"},
		{"M+D", "1000010"},
		{"D-A", "0010011"},
		{"D-M", "1010011"},
		{"A-D", "0000111"},
		{"M-D", "1000111"},
		{"D&A", "0000000"},
		{"A&D", "0000000"},
		{"D&M", "1000000"},
		{"M&D", "1000000"},
		{"D|A", "0010101"},
		{"A|D", "0010101"},
		{"D|M", "1010101"},
		{"M|D", "1010101"},
	};

	const std::map<std::string, std::string>::iterator comp_it
		= computations.find(computation);
	if (comp_it == computations.end()) {
		throw std::exception("Computation not found");
	}
	command += comp_it->second;

	short dest = 0;
	for (int i = 0; i < destination.length(); i++)
	{
		if (destination[i] == 'M')
		{
			dest |= 1;
		} 
		else if (destination[i] == 'D')
		{
			dest |= 2;
		}
		else if (destination[i] == 'A')
		{
			dest |= 4;
		}
	}
	command += std::bitset<3>(dest).to_string();

	std::map<std::string, std::string> jumps = {
		{"", "000"},
		{"JGT", "001"},
		{"JEQ", "010"},
		{"JGE", "011"},
		{"JLT", "100"},
		{"JNE", "101"},
		{"JLE", "110"},
		{"JMP", "111"},
	};
	const std::map<std::string, std::string>::iterator jump_it
		= jumps.find(jump);
	if (jump_it == jumps.end()) {
		throw printf("Jump %s not found", jump.c_str());
	}
	command += jump_it->second;

	return command;
}

std::string Code::toBinary15(short number)
{
	return std::bitset<15>(number).to_string();
}
