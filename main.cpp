#include "Catalog.h"
#include "library.h"

int main()
{
	Catalog system("system");
	
	if (!system.load())
	{
		std::cout << "Error load file.";
		return -1;

	}

	std::string input;
	std::tuple<std::string, std::string> command;
	std::vector<std::string> way;
	way.push_back("system\\");
	
	while (true)
	{
		std::cout << std::endl;
		for (int i = 0; i < way.size(); i++)
		{
			std::cout << way[i];
		}
		std::cout << std::endl << "command:";
		std::getline(std::cin, input);

		command = pars_input(input);
		if (std::get<0>(command) == "error")
		{
			std::cout<< std::endl << "doesn't value";
			continue;
		}
		else if (std::get<0>(command).empty())
		{
			std::cout << std::endl << "doesn't command";
			continue;
		}

		switch (commands.at(std::get<0>(command)))
		{
		case 1:
		{
			if (!system.add_new_file(std::get<1>(command)))
			{
				std::cout << std::endl << std::get<1>(command) + ": can't add new file";
			}
			break;
		}
		case 2:
		{
			if (!system.delete_file(std::get<1>(command)))
			{
				std::cout << std::endl << std::get<1>(command) + " was not found";
			}
			break;
		}
		case 3: 
		{
			if (!system.add_catalog(std::get<1>(command)))
			{
				std::cout << std::endl << std::get<1>(command) + ": this name already use";
			}
			break;
		}
		case 4: 
		{
			if (!system.delete_catalog(std::get<1>(command)))
			{
				std::cout << std::endl << std::get<1>(command) + " was not found";
			}
			else
			{
				way.pop_back();
			}
			break;
		}
		case 5:
		{
			if (!system.next_catalog(std::get<1>(command)))
			{
				std::cout << std::endl << std::get<1>(command) + " was not found";
				
			}
			else
			{
				way.push_back(system.get_name_cur_catalog() + "\\");
			}

			break;
		}
		case 6:
		{
			if (!system.back())
			{
				std::cout << std::endl << "Already root";
			}
			else
			{
				way.pop_back();
			}
			break;
		}
		case 7:
		{
			system.help();
			break;
		}
		case 8:
		{
			system.dir();
			break;
		}
		case 9:
		{
			if (!system.open(std::get<1>(command)))
			{
				std::cout << std::endl << "file can't change.";
			}
			break;
		}
		case 10:
		{
			if (!system.save())
			{
				std::cout << "Error save file.";
				return -2;

			}
			return 0;
		}
		default:
		{
			std::cout << std::endl << "unknow command";
			break;
		}
		}
	}

	return 0;
}