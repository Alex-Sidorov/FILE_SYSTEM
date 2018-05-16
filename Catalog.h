#pragma once
#include "File.h"
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <ios>

#define FLAGS_FOR_CATALOG 0
#define END_FILE -1
#define MAX_SIZE_SYSTEM  1'048'576

class Catalog
{
public:

	bool add_new_file(std::string name_file);//touch name
	bool delete_file(std::string name_file);//rm name
	bool add_catalog(std::string name_catalog);//md name
	bool delete_catalog(std::string name_catalog);// rm-r name || rm-r this
	bool next_catalog(std::string name_catalog);//cd name
	bool open(std::string &name_file);//open name
	bool back();//cd..
	void dir();//dir
	void help();//help

	bool save();
	bool load();

	std::string get_name_cur_catalog()const;

	void change_name(std::string name_catalog);

	Catalog& operator=(const Catalog &obj);
	Catalog& operator=(Catalog &&obj);

	Catalog(std::string name_catalog);
	Catalog(Catalog &&obj);
	Catalog(const Catalog &obj);
	virtual ~Catalog();


private:

	std::string _name_catalog;

	std::list<Catalog> _catalogs;
	std::list<File> _files;
	Catalog* _cur_point;
	Catalog* _back_point;

	int _size_catalog;
	static int _size_system;
	std::vector<int> _way;

	std::fstream _file;


	std::list<File>::iterator find_file(std::string name);
	int find_index_file(std::list<File>::iterator);

	Catalog(std::string name_catalog,std::vector<int> &way, int value_for_way);

	std::list<Catalog>::iterator find_catalog(std::string name);
	int find_index_catalog(std::list<Catalog>::iterator);

	void write_data(Catalog *node);
	void create_catalog(std::vector<int> &way, std::string &name);
	void create_file(std::vector<int> &way, std::string &name, std::vector<std::string> &data);
	void change_size();
};