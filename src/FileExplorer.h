#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "DataBese.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

class FileExplorer {
private:
	std::string filePath;
	std::fstream file;
	bool isOpen;

	void insertRectangleInData(DataBase&, const std::vector<std::string>&);
	void insertCircleInData(DataBase&, const std::vector<std::string>&);
	void insertLineInData(DataBase&, const std::vector<std::string>&);
	//saves data from file to database
	void saveFileData(DataBase&);
	//saves data from database to file
	void saveDataToFile(DataBase&);
	//saves the changed data to file
	void saveChangesToFile(DataBase&);
	void saveDataToNewFile(DataBase&, std::fstream&);
	void writeDataToFile(DataBase&, std::fstream&);
	void writeRectangle(Rectangle*, std::fstream&);
	void writeCircle(Circle*, std::fstream&);
	void writeLine(Line*, std::fstream&);

	std::vector<std::string> getDataOutsideSVG();
public:
	FileExplorer();

	const std::vector<std::string> getCommandSegments(const std::string&);
	int getIntValueFromString(const std::string&);
	int convertStringToInt(const std::string&);
	std::string getStringValueFromString(const std::string&);

	void open(const std::string&, DataBase&);
	void save(DataBase&);
	void saveAs(const std::string&, DataBase&);
	void close(DataBase&);

	const std::string getFilePath()const;
	const bool getIsOpen()const;

	void setFilePath(const std::string&);
};