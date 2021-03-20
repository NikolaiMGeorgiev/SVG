#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "DataBese.h"
#include "FileExplorer.h"

void saveasOrErase(const std::vector<std::string>&, DataBase&, FileExplorer&);
bool isCloseOrSaveOrPrint(const std::string&, DataBase&, FileExplorer&);
void createRectangleOrLine(const std::vector<std::string>&, DataBase&, FileExplorer&);
void createCircle(const std::vector<std::string>&, DataBase&, FileExplorer&);
void withinRectangle(const std::vector<std::string>&, DataBase&, FileExplorer&);
void withinCircle(const std::vector<std::string>&, DataBase&, FileExplorer&);
void translate(const std::vector<std::string>&, DataBase&, FileExplorer&);

int main(){
	std::string command;
	std::string filePath;
	std::vector<std::string> segments;
	std::fstream file;
	DataBase data;
	FileExplorer explorer;

	while (true) {
		std::getline(std::cin, command);
		segments = explorer.getCommandSegments(command);

		if (!segments.empty()) {
			if (explorer.getIsOpen()) {
				if (segments.size() == 2) {
					saveasOrErase(segments, data, explorer);
				}
				else if (segments.size() == 1) {
					if (!isCloseOrSaveOrPrint(segments[0], data, explorer)) {
						if (explorer.getIsOpen()) {
							explorer.close(data);
						}
						std::cout << "Exiting the program...\n";
						system("pause");
						return 0;
					}
				}
				else if (segments.size() == 7 && segments[0] == "create") {
					createRectangleOrLine(segments, data, explorer);
				}
				else if (segments.size() == 6) {
					if (segments[0] == "create") {
						createCircle(segments, data, explorer);
					}
					else if (segments[0] == "within" && segments[1] == "rectangle") {
						withinRectangle(segments, data, explorer);
					}
					else {
						std::cout << "Invalid command! Try again.\n";
					}
				}
				else if (segments.size() == 5 && segments[0] == "within"
					&& segments[1] == "circle") {
					withinCircle(segments, data, explorer);
				}
				else if (segments[0] == "translate") {
					translate(segments, data, explorer);
				}
				else {
					std::cout << "Invalid command! Try again.\n";
				}
			}
			else {
				if (segments[0] == "open") {
					if (segments.size() == 2) {
						filePath = segments[1];
						if (filePath.find(".svg") != std::string::npos) {
							explorer.open(filePath, data);
						}
						else {
							std::cout << "Please open a svg file.\n";
						}
					}
					else {
						std::cout << "Invalid command! Try again.\n";
					}
				}
				else if (segments[0] == "exit") {
					std::cout << "Exiting the program...\n";
					system("pause");
					return 0;
				}
				else {
					std::cout << "No file is open.\n";
				}
			}
			
		}
	}
}

void saveasOrErase(const std::vector<std::string>& segments, DataBase& data, FileExplorer& explorer) {
	if (segments[0] == "saveas") {
		explorer.saveAs(segments[1], data);
	}
	else if (segments[0] == "erase") {
		data.erase(explorer.convertStringToInt(segments[1]));
	}
	else {
		std::cout << "Invalid command! Try again.\n";
	}
}

bool isCloseOrSaveOrPrint(const std::string& command, DataBase& data, FileExplorer& explorer) {
	if (command == "close") {
		explorer.close(data);
	}
	else if (command == "save") {
		explorer.save(data);
	}
	else if (command == "exit") {
		return false;
	}
	else if (command == "print") {
		data.print();
	}
	else {
		std::cout << "Invalid command! Try again.\n";
	}
	
	return true;
}

void createRectangleOrLine(const std::vector<std::string>& segments, DataBase& data,
	FileExplorer& explorer) {
	data.create(segments[1], explorer.convertStringToInt(segments[2]),
		explorer.convertStringToInt(segments[3]),
		explorer.convertStringToInt(segments[4]),
		explorer.convertStringToInt(segments[5]), segments[6]);
}

void createCircle(const std::vector<std::string>& segments, DataBase& data,
	FileExplorer& explorer) {
	data.create(segments[1], explorer.convertStringToInt(segments[2]),
		explorer.convertStringToInt(segments[3]),
		explorer.convertStringToInt(segments[4]), segments[5]);
}

void withinRectangle(const std::vector<std::string>& segments, DataBase& data,
	FileExplorer& explorer) {
	data.within(explorer.convertStringToInt(segments[2]),
		explorer.convertStringToInt(segments[3]),
		explorer.convertStringToInt(segments[4]),
		explorer.convertStringToInt(segments[5]));
}

void withinCircle(const std::vector<std::string>& segments, DataBase& data,
	FileExplorer& explorer) {
	data.within(explorer.convertStringToInt(segments[2]),
		explorer.convertStringToInt(segments[3]),
		explorer.convertStringToInt(segments[4]));
}

void translate(const std::vector<std::string>& segments, DataBase& data, FileExplorer& explorer) {
	int x, y;
	if (segments[1].find("horizontal") != std::string::npos) {
		x = explorer.convertStringToInt(segments[1]);
		y = explorer.convertStringToInt(segments[2]);
	}
	else if (segments[1].find("vertical") != std::string::npos) {
		x = explorer.convertStringToInt(segments[2]);
		y = explorer.convertStringToInt(segments[1]);
	}
	if (segments.size() == 3) {
		data.translate(x, y);
	}
	else if (segments.size() == 4) {
		data.translate(x, y, explorer.convertStringToInt(segments[3]));
	}
	else {
		std::cout << "Invalid command! Try again.\n";
	}
}