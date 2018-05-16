#include "library.h"

const std::map<std::string, int> commands = { { "touch",1 },{ "rm",2 },{ "md",3 },
{ "rm-r",4 },{ "cd",5 },{ "cd..",6 } ,
{ "help",7 },{ "dir",8 } ,{ "open",9 } ,{ "exit",10 } };

std::tuple<std::string, std::string> pars_input(std::string &input)
{
	if (input.find("\t") != input.npos)
	{
		return std::make_tuple("error", "");
	}

	std::string command;
	std::string value;

	int space = input.find(" ");
	command = input.substr(0, space);

	if (command == "dir" || command == "help" || command == "cd.." || command == "exit")
	{
		return std::make_tuple(command, "");
	}

	if (command.empty() || commands.find(command) == commands.end())
	{

		return std::make_tuple("", "");
	}

	int start_value = input.find_first_not_of(" ", space);
	if (start_value == input.npos)
	{
		return std::make_tuple("error", "");
	}

	value = input.substr(start_value);
	int end_value = value.find(" ");
	if (end_value == value.npos)
	{
		return std::make_tuple(command, value);
	}
	else
	{
		return std::make_tuple(command, value.substr(0, end_value));
	}
}