#pragma once
#include <string>
#include <iostream>

class Parser
{
public:
	enum class InstructionType
	{
		kNotDefined,
		kA,
		kC,
		kLabel
	};

	bool parse(std::string instruction);

	InstructionType getType();

	std::string getValue();
	std::string getComputation();
	std::string getDestination();
	std::string getJump();

private:
	InstructionType type_ = InstructionType::kNotDefined;
	std::string value_ = "";
	std::string computation_ = "";
	std::string destination_ = "";
	std::string jump_ = "";
};

