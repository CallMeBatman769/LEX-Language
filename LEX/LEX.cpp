#include <iostream>
#include <Windows.h>
#include <string>
#include <filesystem>
#include "Parse.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "No lex file specified!" << std::endl;
		return 0;
	}
	else if (argc > 2)
	{
		std::cout << "To many arguments, correct use case: LEX.exe file.lex" << std::endl;
		return 0;
	}
	std::string Filename = argv[1];
	if (!fs::exists(argv[1]) || !Filename.ends_with(".lex"))
	{
		std::cout << "File does not exist or is not a .lex file" << std::endl;
		return 0;
	}
	FindVariables(argv[1]);

	//for (Variable variable : Variables)
	//{
	//	std::cout << "VName: " << variable.VName << " Value: "<< variable.Value << " Type: " << variable.Type << std::endl;
	//}
	return 0;
}