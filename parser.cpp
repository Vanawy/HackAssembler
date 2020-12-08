#include "Parser.h"

bool Parser::parse(std::string instruction)
{
	const char comment = '/';
	std::string current_symbol = "";
	type_ = InstructionType::kNotDefined;
	value_ = "";
	computation_ = "";
	destination_ = "";
	jump_ = "";

	if (instruction.length() == 0) {
		return false;
	}

	bool is_computation_parsed = false;

	for (int i = 0; i < instruction.length(); i++)
	{
		const char character = instruction[i];
		// Get rid of space charecters 
		if (character == ' ' || character == '\t') continue;

		// Determine type of current instruction
		if (type_ == Parser::InstructionType::kNotDefined)
		{
			if (character == '@')
			{
				type_ = Parser::InstructionType::kA;
				continue;
			}
			else if (character == '(')
			{
				type_ = Parser::InstructionType::kLabel;
				continue;
			}
			else
			{
				type_ = Parser::InstructionType::kC;
			}
		}

		// Parse symbols of C-instruction
		if (type_ == Parser::InstructionType::kC)
		{
			if (character == '=')
			{
				destination_ = current_symbol;
				current_symbol = "";
				continue;
			}
			if (character == ';')
			{
				computation_ = current_symbol;
				current_symbol = "";
				is_computation_parsed = true;
				continue;
			}
		}

		if (type_ == InstructionType::kLabel && character == ')')
		{
			break;
		}

		if (character == '\n' || character == comment)
		{
			if (current_symbol == "")
			{
				return false;
			}
			break;
		}
		current_symbol += character;

	}

	if (type_ == Parser::InstructionType::kC)
	{
		if (is_computation_parsed)
		{
			jump_ = current_symbol;
		}
		else
		{
			computation_ = current_symbol;
			is_computation_parsed = true;
		}
	}
	else
	{
		value_ = current_symbol;
	}
	return true;
}

Parser::InstructionType Parser::getType()
{
	return type_;
}

std::string Parser::getValue()
{
	return value_;
}

std::string Parser::getComputation()
{
	return computation_;
}

std::string Parser::getDestination()
{
	return destination_;
}

std::string Parser::getJump()
{
	return jump_;
}
