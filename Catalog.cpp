#include "Catalog.h"

std::vector<std::string> invalid_name = { "system", "this" };

int Catalog::_size_system = MAX_SIZE_SYSTEM;

bool Catalog::add_new_file(std::string name_file)
{
	if (find_file(name_file) != _cur_point->_files.end())
	{
		return false;
	}
	_cur_point->_files.push_back(File(name_file, _cur_point->_way, _cur_point->_files.size()));
	change_size();
	return true;
}

bool Catalog::delete_file(std::string name_file)
{
	std::list<File>::iterator index = find_file(name_file);
	if (index == _cur_point->_files.end())
	{
		return false;
	}
	else
	{
		_cur_point->_files.erase(index);
		change_size();
		return true;
	}
}

bool Catalog::add_catalog(std::string name_catalog)
{
	if (find_catalog(name_catalog) != _cur_point->_catalogs.end() 
		|| std::find(invalid_name.begin(),invalid_name.end(),name_catalog)!=invalid_name.end())
	{
		return false;
	}
	_cur_point->_catalogs.push_back(std::move(Catalog(name_catalog,_cur_point->_way, _cur_point->_catalogs.size())));
	_cur_point->_catalogs.back()._back_point = _cur_point;
	return true;
}

bool Catalog::delete_catalog(std::string name_catalog)
{
	if (name_catalog == "this")
	{
		if (_cur_point->_back_point == nullptr)
		{
			_cur_point->_files.clear();
			_cur_point->_catalogs.clear();
			_cur_point->_size_catalog = 0;
			_cur_point->_size_system = MAX_SIZE_SYSTEM;
			return true;
		}

		name_catalog = _cur_point->_name_catalog;
		_cur_point = _cur_point->_back_point;
	}
	
	std::list<Catalog>::iterator index = find_catalog(name_catalog);
	if (index == _cur_point->_catalogs.end())
	{
		return false;
	}
	else
	{
		_cur_point->_catalogs.erase(index);
		change_size();
		return true;
	}
}

bool Catalog::next_catalog(std::string name_catalog)
{
	std::list<Catalog>::iterator index = find_catalog(name_catalog);
	if (index == _cur_point->_catalogs.end())
	{
		return false;
	}
	else
	{
		_cur_point=&(*index);
		return true;
	}
}

bool Catalog::back()
{
	if (_cur_point->_back_point == nullptr)
	{
		return false;
	}
	else
	{
		_cur_point = _cur_point->_back_point;
		return true;
	}
}

void Catalog::dir()
{
	std::cout << "Max size system:" << _cur_point->_size_system<<std::endl;
	std::cout << "Name catalog:" << _cur_point->_name_catalog << std::endl;
	std::cout << "Size catalog:" << _cur_point->_size_catalog << std::endl << std::endl;

	std::cout << "FILES:" << std::endl;

	for (auto i = _cur_point->_files.begin();i != _cur_point->_files.end(); i++)
	{
		std::cout << (*i).get_name() << " " << (*i).get_size() << " byte" << std::endl;
	}

	std::cout << std::endl << "CATALOGS:" << std::endl;
	
	for (auto i = _cur_point->_catalogs.begin(); i != _cur_point->_catalogs.end(); i++)
	{
		std::cout << (*i)._name_catalog << " " << (*i)._size_catalog << " byte" << std::endl;
	}

}

void Catalog::help()
{
	std::cout << "touch <name's file> :create new file" << std::endl;
	std::cout << "rm <name's file> :delete file" << std::endl;
	std::cout << "md <name's catalog> :add catalog" << std::endl;
	std::cout << "rm-r this :delete this catalog" << std::endl;
	std::cout << "rm-r <name's catalog> :delete catalog" << std::endl;
	std::cout << "cd <name's catalog> :go to next catalog" << std::endl;
	std::cout << "cd.. :go to back catalog" << std::endl;
	std::cout << "open <name's file> :open file" << std::endl;
	std::cout << "dir :info's catalog" << std::endl;
	std::cout << "help :help for user" << std::endl;
	std::cout << "exit :for exit";
}

bool Catalog::open(std::string &name_file)
{
	auto file = find_file(name_file);
	if (file == _cur_point->_files.end())
	{
		return false;
	}
	
	int old_size_file = file->get_size();
	bool result = file->show(_size_system);
	if (result)
	{
		change_size();
		return true;
	}
	return false;
}

std::string Catalog::get_name_cur_catalog()const
{
	return _cur_point->_name_catalog;
}

void Catalog::change_size()
{
	Catalog *it = _cur_point;
	_size_system = MAX_SIZE_SYSTEM;
	int size = 0;

	while (it!=nullptr)
	{
		for (auto i = it->_catalogs.begin(); i != it->_catalogs.end(); i++)
		{
			size += i->_size_catalog;
		}

		for (auto i = it->_files.begin(); i != it->_files.end(); i++)
		{
			size += i->get_size();
		}
		it->_size_catalog = size;
		_size_system -= size;
		size = 0;
		it = it->_back_point;
	}
}

int Catalog::find_index_file(std::list<File>::iterator it)
{
	auto value = _cur_point->_files.begin();
	for (int i = 0; i < _cur_point->_files.size();i++, value++)
	{
		if (value == it)
		{
			return i;
		}
	}
	return -1;
}

int Catalog::find_index_catalog(std::list<Catalog>::iterator it)
{
	auto value = _cur_point->_catalogs.begin();
	for (int i = 0; i < _cur_point->_catalogs.size();i++, value++)
	{
		if (value == it)
		{
			return i;
		}
	}
	return -1;
}

std::list<Catalog>::iterator Catalog::find_catalog(std::string name)
{
	for (auto i = _cur_point->_catalogs.begin(); i != _cur_point->_catalogs.end(); i++)
	{
		if ((*i)._name_catalog == name)
		{
			return i;
		}

	}
	return _cur_point->_catalogs.end();
}

std::list<File>::iterator Catalog::find_file(std::string name)
{
	for (auto i = _cur_point->_files.begin(); i != _cur_point->_files.end(); i++)
	{
		if ((*i).get_name() == name)
		{
			return i;
		}
	}
	return _cur_point->_files.end();
}


void Catalog::write_data(Catalog *node)
{
	for (auto it = node->_catalogs.begin(); it != node->_catalogs.end(); it++)
	{
		write_data(&(*it));
	}

	_file << node->_way.size() << ' ';

	for (int i = 0; i < node->_way.size(); i++)
	{
		_file << node->_way[i] << ' ';
	}

	_file << FLAGS_FOR_CATALOG << ' ' << node->_name_catalog << ' ';

	for (auto it = node->_files.begin(); it != node->_files.end(); it++)
	{
		it->write(_file);
	}
}

bool Catalog::save()
{
	_file.open("data.txt", std::ios::out);
	if (!_file.is_open())
	{
		return false;
	}
	write_data(this);
	_file << END_FILE;
	_file.close();
	return true;
}

bool Catalog::load()
{
	int size_way = 0;
	int temp_way = 0;
	int flag = 0;
	std::string name;
	std::vector<std::string> data;

	std::vector<int> way;

	_file.open("data.txt", std::ios::in);
	if (!_file.is_open())
	{
		return false;
	}
	
	while (!_file.eof())
	{
		_file >> size_way;
		if (size_way == END_FILE)
		{
			break;
		}

		for (int i = 0; i < size_way; i++)
		{
			_file >> temp_way;
			way.push_back(temp_way);
		}
		_file >> flag;
		_file >> name;
	
		if (flag == 0)
		{
			create_catalog(way, name);
		}
		else
		{
			int size_data = 0;
			_file >> size_data;
			if (size_data == END_FILE)
			{
				break;
			}
			data.reserve(size_data);
			_file.get();
			std::string temp_str;
			for (int i = 0; i < size_data; i++)
			{
				std::getline(_file, temp_str);
				data.push_back(temp_str);
			}
			create_file(way, name, data);
		}
		way.clear();
		data.clear();
	}

	_file.close();
}

void Catalog::create_catalog(std::vector<int> &way, std::string &name)
{
	_cur_point = this;
	std::vector<int> temp_way;
	temp_way.push_back(0);

	for (int i = 1; i < way.size(); i++)
	{
		if (_cur_point->_catalogs.size() <= way[i])
		{
			while (_cur_point->_catalogs.size() <= way[i])
			{
				_cur_point->_catalogs.push_back(Catalog("",temp_way, _cur_point->_catalogs.size()));
				_cur_point->_catalogs.back()._back_point = _cur_point;
			}
			_cur_point = &(_cur_point->_catalogs.back());
		}
		else
		{
			auto it = _cur_point->_catalogs.begin();
			std::advance(it, way[i]);
			_cur_point = &(*it);
		}
		temp_way.push_back(way[i]);
	}
	_cur_point->change_name(name);
}

void Catalog::create_file(std::vector<int> &way, std::string &name, std::vector<std::string> &data)
{
	_cur_point = this;
	for (int i = 1; i < way.size()-1; i++)
	{
		auto it = _cur_point->_catalogs.begin();
		std::advance(it, way[i]);
		_cur_point = &(*it);
	}
	_cur_point->_files.push_back(File(name, way, data));
	change_size();

	_cur_point = this;
}

void Catalog::change_name(std::string name_catalog)
{
	_name_catalog = name_catalog;
}

Catalog& Catalog::operator=(const Catalog &obj)
{
	_name_catalog = obj._name_catalog;
	_files = obj._files;
	_catalogs = obj._catalogs;
	_cur_point = obj._cur_point;
	_back_point = obj._back_point;
	_size_catalog = obj._size_catalog;
	return *this;
}

Catalog& Catalog::operator=(Catalog &&obj)
{
	_name_catalog = obj._name_catalog;
	obj._name_catalog.clear();

	_files = obj._files;
	obj._files.clear();

	_catalogs = obj._catalogs;
	obj._catalogs.clear();

	_cur_point = obj._cur_point;
	obj._cur_point = nullptr;

	_back_point = obj._back_point;
	obj._back_point = nullptr;

	_size_catalog = obj._size_catalog;
	obj._size_catalog = 0;

	return *this;
}

Catalog::Catalog(std::string name_catalog) :_cur_point(this),_back_point(nullptr), _name_catalog(name_catalog)
{
	_way.push_back(0);
	_size_catalog = 0;
}

Catalog::Catalog(std::string name_catalog,std::vector<int> &way, int value_for_way): _name_catalog(name_catalog)
{
	_way = way;
	_way.push_back(value_for_way);
	_size_catalog = 0;
}

Catalog::Catalog(Catalog &&obj)
{
	_name_catalog = obj._name_catalog;
	obj._name_catalog.clear();

	_files = obj._files;
	obj._files.clear();

	_catalogs = obj._catalogs;
	obj._catalogs.clear();

	_cur_point = obj._cur_point;
	obj._cur_point = nullptr;

	_back_point = obj._back_point;
	obj._back_point = nullptr;

	_size_catalog = obj._size_catalog;
	obj._size_catalog = 0;

	_way = obj._way;
	obj._way.clear();
}

Catalog::Catalog(const Catalog &obj)
{
	_name_catalog = obj._name_catalog;
	_files = obj._files;
	_catalogs = obj._catalogs;
	_cur_point = obj._cur_point;
	_back_point = obj._back_point;
	_size_catalog = obj._size_catalog;
	_way = obj._way;
}

Catalog::~Catalog()
{
}
