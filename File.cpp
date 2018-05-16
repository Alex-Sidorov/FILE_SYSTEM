#include "File.h"

bool File::_open = false;

std::string File::get_name()const
{
	return _name;
}

int File::get_size()const
{
	int size = 0;
	for (int i = 0; i < _data.size();i++)
	{
		size += _data[i].size();
	}
	return size;
}

bool File::show(const int real_size)
{
	std::fstream temp_file;
	std::string file_name = _name + ".txt";
	temp_file.open(file_name, std::ios::out);
	if (temp_file.is_open())
	{
		for (int i = 0;i < _data.size();i++)
		{
			temp_file << _data[i] << std::endl;
		}
		temp_file.close();
		system((std::string("notepad.exe ")+ file_name).c_str());

		temp_file.open(file_name, std::ios::in);
		if(temp_file.is_open())
		{
			std::string temp_str;
			std::vector<std::string> old_data = std::move(_data);
			int size_old_data = get_size();
			for (int i = 0; std::getline(temp_file, temp_str); i++)
			{
				_data.push_back(temp_str);
			}
			if (real_size + size_old_data - get_size() < 0)
			{
				_data = std::move(old_data);
				temp_file.close();
				std::remove(file_name.c_str());
				return false;
			}
			temp_file.close();
			std::remove(file_name.c_str());
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

void File::write(std::ostream &file)
{
	file << _way.size() << ' ';

	for (int i = 0; i < _way.size(); i++)
	{
		file << _way[i] << ' ';
	}

	file << FLAGS_FOR_FILE << ' ' << _name << ' ' << _data.size() <<  std::endl;
	for (int i = 0; i < _data.size(); i++)
	{
		file << _data[i] << std::endl;
	}
}

File::File(std::string name_file, std::vector<int> &way, std::vector<std::string> &data)
{
	_name = name_file;
	_way = way;
	_data = data;
}

File::File(std::string name_file, std::vector<int> &way, int value_for_way)
{
	_name = name_file;
	_way = way;
	_way.push_back(value_for_way);
}

File::File(const File &obj)
{
	_data = obj._data;
	 _name = obj._name;
	_way = obj._way;
}

File::File(File &&obj)
{
	_data = obj._data;
	obj._data.clear();

	_name = obj._name;
	obj._name.clear();

	_way = obj._way;
	obj._way.clear();

}

File& File::operator=(const File &obj)
{
	_data = obj._data;
	_name = obj._name;
	_way = obj._way;
	return *this;
}

File& File::operator=(File &&obj)
{
	_data = obj._data;
	obj._data.clear();

	_name = obj._name;
	obj._name.clear();

	_way = obj._way;
	obj._way.clear();

	return *this;
}

File::~File()
{
}
