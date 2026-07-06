#pragma once
#include <string>
#include <vector>

struct Variable {
	std::string VName;
	std::string Type;
	std::string Value;
};

extern std::vector<Variable> Variables;

bool FindVariables(std::string Filepath);