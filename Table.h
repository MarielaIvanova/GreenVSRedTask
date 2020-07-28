#pragma once
#include"Box.h"
#include<vector>

//The class Table realizes a table that is given as a table created of vector of vectors of objects of type Box and sizes for the table
class Table {
	std::vector<std::vector<Box>> _table;
	int sizeX;
	int sizeY;

public:
	Table() {}
	Table(std::vector<std::vector<Box>> t, int sX = 0, int sY = 0) : _table(t), sizeX(sX), sizeY(sY){}
	Table& operator=(Table const &t);
	~Table() {}

	void set_Table(std::vector<std::vector<Box>>& t);  //changes the table with a new one, the new table should be again vector of vector of objects of the clas Box
	std::vector<std::vector<Box>>& get_Table() { return _table; }  //returns just the table which contains boxes(boxes contain colors)

	void setX(int x) { sizeX = x; } //changes the number of the rows of the table
	int getX() { return sizeX; }  //returns the number of the rows of the table

	void setY(int y) { sizeY = y; } //changes the number of the columns of the table
	int getY() { return sizeY; }  //returns the number of the columns of the table

};


void Table::set_Table(std::vector<std::vector<Box>>& t) {
	_table.clear();
	std::vector<Box> v;
	for (unsigned int i = 0; i < t.size(); i++) {
		v = t[i];
		_table.push_back(v);
	}
}

//assigns the values from right side operand (object of type Table) to the left side operand (again object of type Table)
Table& Table::operator=(Table const &t) {
	if (this != &t) {
		this->_table.clear();
		std::vector<Box> v;
		for (unsigned int i = 0; i < t._table.size(); i++) {
			v = t._table[i];
			_table.push_back(v);
		}
		this->sizeX = t.sizeX;
		this->sizeY = t.sizeY;
	}
	return *this;
}