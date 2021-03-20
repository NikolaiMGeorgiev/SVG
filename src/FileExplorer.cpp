#include "FileExplorer.h"

FileExplorer::FileExplorer() {
	filePath = "";
	isOpen = false;
}

void FileExplorer::open(const std::string& filePath, DataBase& data) {
	file.open(filePath, std::ios::in);
	
	if (!file.is_open()) {
		std::ofstream openfile;
		openfile.open(filePath, std::ios::out);
		openfile.close();
		file.open(filePath, std::ios::in);
	}

	if (file.good()) {
		isOpen = true;
		std::cout << "Successfully opened " << filePath << std::endl;
		this->filePath = filePath;

	}
	else {
		std::cout << "Error opening file " << filePath << std::endl;
	}

	saveFileData(data);
	file.close();
}

void FileExplorer::save(DataBase& data) {
	file.open(filePath, std::ios::in);
	saveChangesToFile(data);

	if (file.good()) {
		std::cout << "Successfully saved " << filePath << std::endl;
	}
	else {
		std::cout << "Error saving file " << filePath << std::endl;
	}

	file.close();
}

void FileExplorer::saveAs(const std::string& newFilePath, DataBase& data) {
	if (newFilePath.find(".svg") != std::string::npos) {
		std::fstream newFile(newFilePath, std::ios::out);
		file.open(filePath);

		saveDataToNewFile(data, newFile);

		if (newFile.good()) {
			std::cout << "Successfully saved file to " << newFilePath << std::endl;
		}
		else {
			std::cout << "Error saving file to " << newFilePath << std::endl;
		}

		file.close();
		newFile.close();
	}
	else {
		std::cout << "Must be saved as a .svg file.\n";
	}
	
}

void FileExplorer::close(DataBase& data) {
	data.~DataBase();
	isOpen = false;
	std::cout << "Successfully closed " << filePath << std::endl;

	if (file.is_open()) {
		file.close();
	}
}

const std::vector<std::string> FileExplorer::getCommandSegments(const std::string& command) {
	std::string operation;
	std::vector<std::string> segments;
	int j = 0;

	while (command.at(j) == ' ') {
		j++;
	}

	for (int i = j; i < command.size() - 1; i++) {
		if (command.at(i) == ' ') {

			if (command.at(i + 1) == ' ') {
				continue;
			}
			segments.push_back(operation);
			operation.clear();
			continue;
		}
		operation.push_back(command.at(i));
	}

	if (command.at(command.size() - 1) != ' ') {
		operation.push_back(command.at(command.size() - 1));
	}

	if (!operation.empty()) {
		segments.push_back(operation);
	}

	if (segments.empty()) {
		std::cout << "Invalid commnd\n";
	}

	if ((segments.at(0) == "open" || segments.at(0) == "saveas") && segments.size() > 2) {
		if (segments.at(segments.size() - 1).find('.') != std::string::npos) {
			int size = segments.size();
			for (int i = 2; i < size; i++) {
				segments.at(1).append(" " + segments.at(i));
			}
			for (int i = 2; i < size; i++) {
				segments.pop_back();
			}
		}
	}

	return segments;
}

void FileExplorer::saveFileData(DataBase& data) {
	std::string line;
	//std::streampos svgStartPosition;
	std::vector<std::string> segments;

	while (std::getline(file, line)) {
		if (line.find("<svg") != std::string::npos
			&& line.find(">") != std::string::npos) {
			break;
		}
	}

	while (std::getline(file, line)) {
		if (line.find("</svg>") != std::string::npos) {
			break;
		}

		segments = getCommandSegments(line);

		if (line.find("<rect") != std::string::npos) {
			insertRectangleInData(data, segments);
		}
		else if (line.find("<circle") != std::string::npos) {
			insertCircleInData(data, segments);
		}
		else if (line.find("<line") != std::string::npos) {
			insertLineInData(data, segments);
		}
	}
}

void FileExplorer::insertRectangleInData(DataBase& data, const std::vector<std::string>& segmnets) {
	std::string segment;
	Rectangle* rect = new Rectangle();

	for (int i = 0; i < segmnets.size(); i++) {
		segment = segmnets.at(i);

		if (segment.find("x=") != std::string::npos) {
			rect->setX(getIntValueFromString(segment));
		}
		else if (segment.find("y=") != std::string::npos) {
			rect->setY(getIntValueFromString(segment));
		}
		else if (segment.find("width=") != std::string::npos) {
			rect->setWidth(getIntValueFromString(segment));
		}
		else if (segment.find("height=") != std::string::npos) {
			rect->setHeight(getIntValueFromString(segment));
		}
		else if (segment.find("fill=") != std::string::npos) {
			rect->setFill(getStringValueFromString(segment));
		}
	}
	data.add((Figure*)rect);
}

void FileExplorer::insertCircleInData(DataBase& data, const std::vector<std::string>& segments) {
	std::string segment;
	Circle* circle = new Circle;

	for (int i = 0; i < segments.size(); i++) {
		segment = segments.at(i);

		if (segment.find("cx=") != std::string::npos) {
			circle->setX(getIntValueFromString(segment));
		}
		else if (segment.find("cy=") != std::string::npos) {
			circle->setY(getIntValueFromString(segment));
		}
		else if (segment.find("r=") != std::string::npos) {
			circle->setRadius(getIntValueFromString(segment));
		}
		else if (segment.find("fill=") != std::string::npos) {
			circle->setFill(getStringValueFromString(segment));
		}
	}
	data.add(circle);
}

void FileExplorer::insertLineInData(DataBase& data, const std::vector<std::string>& segmnets) {
	std::string segment;
	Line* line = new Line;

	for (int i = 0; i < segmnets.size(); i++) {
		segment = segmnets.at(i);

		if (segment.find("x1=") != std::string::npos) {
			line->setX(getIntValueFromString(segment));
		}
		else if (segment.find("y1=") != std::string::npos) {
			line->setY(getIntValueFromString(segment));
		}
		else if (segment.find("x2=") != std::string::npos) {
			line->setX2(getIntValueFromString(segment));
		}
		else if (segment.find("y2=") != std::string::npos) {
			line->setY2(getIntValueFromString(segment));
		}
		else if (segment.find("fill=") != std::string::npos) {
			line->setFill(getStringValueFromString(segment));
		}
	}
	data.add(line);
}

int FileExplorer::getIntValueFromString(const std::string& segment) {
	std::string value;
	for (int i = 0; i < segment.size(); i++) {
		if (segment.at(i) == '"') {
			i++;
			while (segment.at(i) != '"' && i < segment.size()) {
				value.push_back(segment.at(i));
				i++;
			}
			if (i == segment.size()) {
				std::cout << "Invalid value!\n";
			}
			break;
		}
	}
	return convertStringToInt(value);
}

std::string FileExplorer::getStringValueFromString(const std::string& segment) {
	std::string value;
	for (int i = 0; i < segment.size(); i++) {
		if (segment.at(i) == '"') {
			i++;
			while (segment.at(i) != '"' && i < segment.size()) {
				value.push_back(segment.at(i));
				i++;
			}
			if (i == segment.size()) {
				std::cout << "Invalid value!\n";
			}
			break;
		}
	}
	return value;
}

int FileExplorer::convertStringToInt(const std::string& text) {
	int result = 0;
	for (int i = 0; i < text.size(); i++) {
		if (text.at(i) >= 48 && text.at(i) <= 57) {
			result += (text.at(i) - 48)*pow(10, (text.size() - 1 - i));
		}

	}
	return result;
}

void FileExplorer::saveDataToFile(DataBase& data) {
	std::string line;
	std::streampos position;
	std::vector<std::string> endOfFile;
	std::ifstream readFile(filePath);

	while (std::getline(readFile, line)) {
		if (line.find("</svg") != std::string::npos) {
			break;
		}
		position = readFile.tellg();
	}

	file.seekp(position);

	while (std::getline(readFile, line)) {
		endOfFile.push_back(line);
	}

	readFile.close();

	writeDataToFile(data, file);

	for (int i = 0; i < endOfFile.size(); i++) {
		file << endOfFile[i] << "\n";
	}
}

void FileExplorer::writeDataToFile(DataBase& data, std::fstream& file) {
	for (int i = 0; i < data.figures.size(); i++) {
		if (data.figures.at(i)->getType() == Figure::rectangle) {
			writeRectangle((Rectangle*)data.figures.at(i), file);
		}
		else if (data.figures.at(i)->getType() == Figure::circle) {
			writeCircle((Circle*)data.figures.at(i), file);
		}
		else if (data.figures.at(i)->getType() == Figure::line) {
			writeLine((Line*)data.figures.at(i), file);
		}
	}
}

void FileExplorer::saveChangesToFile(DataBase& data) {
	std::string line;
	std::vector<std::string> lines;

	std::fstream readFile(filePath, std::ios::in);
	std::fstream temp(filePath);

	lines = getDataOutsideSVG();
	readFile.close();
	file.close();
	file.open(filePath, std::ofstream::out | std::ios::trunc);

	int i = 0;
	while (i < lines.size()) {
		file << lines[i];
		file << "\n";
		if (lines[i].find("<svg") != std::string::npos) {
			i++;
			break;
		}
		i++;
	}

	writeDataToFile(data, file);

	for (i; i < lines.size(); i++) {
		file << lines[i];
		file << "\n";
	}
}

std::vector<std::string> FileExplorer::getDataOutsideSVG() {
	std::string line;
	std::vector<std::string> lines;
	std::fstream readFile(filePath, std::ios::in);

	bool foundSVG = false;

	while (std::getline(readFile, line)) {
		lines.push_back(line);
		if (line.find("<svg") != std::string::npos) {
			foundSVG = true;
			break;
		}
	}

	if (!foundSVG) {
		lines.push_back("<svg>");
	}

	while (std::getline(readFile, line)) {
		if (line.find("</svg>") != std::string::npos) {
			break;
		}
	}

	lines.push_back("</svg>");

	while (std::getline(readFile, line)) {
		lines.push_back(line);
	}

	readFile.close();

	return lines;
}

void FileExplorer::saveDataToNewFile(DataBase& data, std::fstream& newFile) {
	std::string line;
	std::vector<std::string> lines = getDataOutsideSVG();

	int i = 0;
	while (i < lines.size()) {
		newFile << lines[i] << "\n";
		if (lines[i].find("<svg") != std::string::npos) {
			i++;
			break;
		}
		i++;
	}

	writeDataToFile(data, newFile);

	for (i; i < lines.size(); i++) {
		newFile << lines[i];
		newFile << "\n";
	}
}

void FileExplorer::writeRectangle(Rectangle* rect, std::fstream& file) {
	file << "<rect x=\"" << rect->getX() << "\" y=\"" << rect->getY();
	file << "\" width=\"" << rect->getWidth() << "\" height=\"" << rect->getHeight();
	file << "\" fill=\"" << rect->getFill() << "\" />\n";
}

void FileExplorer::writeCircle(Circle* circle, std::fstream& file) {
	file << "<circle cx=\"" << circle->getX() << "\" cy=\"" << circle->getY();
	file << "\" r=\"" << circle->getRadius() << "\" fill=\"" << circle->getFill() << "\" />\n";
}

void FileExplorer::writeLine(Line* line, std::fstream& file) {
	file << "<line x1=\"" << line->getX() << "\" y1=\"" << line->getY();
	file << "\" x2=\"" << line->getX2() << "\" y2=\"" << line->getY2();
	file << "\" fill=\"" << line->getFill() << "\" />\n";
}

const std::string FileExplorer::getFilePath()const {
	return filePath;
}

const bool FileExplorer::getIsOpen()const {
	return isOpen;
}

void FileExplorer::setFilePath(const std::string& filePath) {
	this->filePath = filePath;
}