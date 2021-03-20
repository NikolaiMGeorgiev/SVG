#include "DataBese.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

DataBase::DataBase() {

}

DataBase::DataBase(const DataBase& database) {
	for (int i = 0; i < database.figures.size(); i++) {
		figures.push_back(database.figures.at(i));
	}
}

DataBase& DataBase::operator=(const DataBase& database) {
	for (int i = 0; i < figures.size(); i++) {
		Figure* currentFigure = figures.back();
		figures.pop_back();
		delete currentFigure;
	}

	for (int i = 0; i < database.figures.size(); i++) {
		figures.push_back(database.figures.at(i));
	}

	return *this;
}

void DataBase::print()const {
	for (int i = 0; i < figures.size(); i++) {
		std::cout << i + 1<<". ";
		figures.at(i)->print();
	}
}

void DataBase::within(const int& x, const int& y, const int& width,
	const int& height)const {
	int counter = 0;

	for (int i = 0; i < figures.size(); i++) {
		if (figures.at(i)->isWithin(x, y, width, height)) {
			figures.at(i)->print();
			counter++;
		}
	}

	if (counter == 0) {
		std::cout << "No figures within rectangle " << x << " " << y << " ";
		std::cout<< width << " " << height << "\n";
	}
}

void DataBase::within(const int& x, const int& y, const int& radius)const {
	int counter = 0;
	for (int i = 0; i < figures.size(); i++) {
		if (figures.at(i)->isWithin(x, y, radius)) {
			figures.at(i)->print();
			counter++;
		}
	}

	if (counter == 0) {
		std::cout << "No figures within circle " << x << " " << y << " " << radius << "\n ";
	}
}

void DataBase::create(const std::string& type, const int& x, const int& y, const int& parameter1,
	const int& parameter2, const std::string& fill) {
	if (type == "rectangle") {
		Rectangle* rectangle = new Rectangle(x, y, parameter1, parameter2, fill);
		figures.push_back(rectangle);
		std::cout << "Successfully created rectangle " << figures.size() << std::endl;
	}
	else if (type == "line") {
		Line* line = new Line(x, y, parameter1, parameter2, fill);
		figures.push_back(line);
		std::cout << "Successfully created line " << figures.size() << std::endl;
	}
	else {
		std::cout << "Invalid type!\n";
	}
}

void DataBase::create(const std::string& type, const int& x, const int& y, 
	const int& radius, const std::string& fill) {
	if (type == "circle") {
		Circle* circle = new Circle(x, y, radius, fill);
		figures.push_back(circle);
		std::cout << "Successfully created circle " << figures.size() << std::endl;
	}
	else {
		std::cout << "Invalid type!\n";
	}
}

void DataBase::erase(const int& index) {
	if (index > 0 && index <= figures.size()) {
		std::cout << "Erased a ";
		figures.at(index - 1)->printType();
		std::cout << "(" << index << ")" << std::endl;

		Figure* figure = figures.at(index - 1);
		figures.erase(figures.begin() + index - 1);
		delete figure;
	}
	else {
		std::cout << "No figure with a number " << index << std::endl;
	}
}

void DataBase::translate(const int& x, const int& y, const int& index) {
	if (index > 0 && index - 1 < figures.size()) {
		figures.at(index - 1)->setX(figures.at(index - 1)->getX() + x);
		figures.at(index - 1)->setY(figures.at(index - 1)->getY() + y);
		std::cout << "Translted figure with number " << index << std::endl;
	}
	else if(index == 0){
		for (int i = 0; i < figures.size(); i++) {
			figures.at(i)->setX(figures.at(i)->getX() + x);
			figures.at(i)->setY(figures.at(i)->getY() + y);
		}
		std::cout << "Translated all figures\n";
	}
	else {
		std::cout << "No figure with number " << index << std::endl;
	}
}

void DataBase::add(Figure* figure) {
	figures.push_back(figure);
}

DataBase::~DataBase() {
	for (int i = 0; i < figures.size(); i++) {
		Figure* currentFigure = figures.back();
		figures.pop_back();
		delete currentFigure;
	}
}