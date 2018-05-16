#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ios>

#define FLAGS_FOR_FILE 1

class File
{
public:
	bool show(const int max_size);

	std::string get_name()const;
	int get_size()const;

	void write(std::ostream &file);

	File& operator=(const File &obj);
	File& operator=(File &&obj);

	File(std::string name_file,std::vector<int> &_way, int value_for_way);
	File(std::string name_file, std::vector<int> &_way, std::vector<std::string>  &data);
	File(const File &obj);
	File(File &&obj);
	virtual ~File();
private:
	std::vector<std::string> _data;
	std::string _name;
	std::vector<int> _way;
	static bool _open;
};