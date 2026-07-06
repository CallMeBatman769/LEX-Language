#include <iostream>
#include <vector>
#include <mutex>
#include <fstream>
#include <sstream>
#include "Parse.h"

std::mutex VariablesMutex;
std::vector<Variable> Variables;

bool AddVariable(std::string Name, std::string Type, std::string Value)
{
	try
	{
		Variable NewVar;
		NewVar.Value = Value;
		NewVar.Type = Type;
		NewVar.VName = Name;
		std::lock_guard<std::mutex> lock(VariablesMutex);
		Variables.push_back(NewVar);
		//std::cerr << "Successfully added variable!" << std::endl;
		return true;
	}
	catch (std::exception& e)
	{
		std::cerr << "Failed to add variable" << std::endl;
		return false;
	}

}

bool FindVariables(std::string Filepath)
{
	std::ifstream LexFile(Filepath);

	if (!LexFile.is_open())
	{
		std::cerr << "Error: Couldn't open file " << Filepath << std::endl;
		return false;
	}
	std::string line;
	while (std::getline(LexFile, line))
	{
		std::stringstream ss(line);
		std::string command;

		if (!(ss >> command)) continue;

		if (command == "var")
		{
			std::string type, name, equals, value;

			if (ss >> type >> name >> equals)
			{
				if (equals == "=")
				{
					
					std::getline(ss, value);

					
					if (!value.empty() && value[0] == ' ') {
						value.erase(0, 1);
					}

					AddVariable(name, type, value);
				}
				else
				{
					std::cerr << "Syntax error: Expected '=' after Var name" << std::endl;
				}
			}
		}
		else if (command == "say")
		{
			std::string varName;
			if (ss >> varName)
			{
				bool Found = false;
				for (Variable variable : Variables)
				{
					if (variable.VName == varName)
					{
						std::cout << variable.Value << std::endl;
						Found = true;
						break;
					}
					else
					{
						continue;
					}
				}
				if (!Found)
				{
					std::cout << "Couldn't find variable with name '" << varName << "'" << std::endl;
				}
			}
		}
	}
}