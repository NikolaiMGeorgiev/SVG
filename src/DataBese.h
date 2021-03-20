#pragma once
#include <iostream>
#include <vector>
#include "Figure.h"

class DataBase {
private:
	friend class FileExplorer;
	std::vector<Figure*> figures;
public:
	DataBase();
	DataBase(const DataBase&);
	DataBase& operator=(const DataBase&);

	void print()const;
	void within(const int&, const int&, const int&, const int&)const;
	void within(const int&, const int&, const int&)const;

	void create(const std::string&, const int&, const int&, const int&, const int&, 
		const std::string&);
	void create(const std::string&, const int&, const int&, const int&, const std::string&);
	void erase(const int&);
	void translate(const int&, const int&, const int& = 0);
	void add(Figure*);

	~DataBase();
};
