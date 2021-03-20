#include "Figure.h"
#include <iostream>

Figure::Figure():x(0), y(0) {
	fill = " ";
}

Figure::Figure(const int& x, const int& y, const std::string& fill): x(x), y(y){
	this->fill = fill;
}

bool Figure::isWithin(const int&, const int&, const int&, const int&)const {
	return false;
}

bool Figure::isWithin(const int&, const int&, const int&)const {
	return false;
}

void Figure::print()const {
	printType();
	std::cout << " " << x << " " << y << " ";
}

void Figure::printType()const {
	if (figureType == rectangle) {
		std::cout << "rectangle";
	}
	else if (figureType == circle) {
		std::cout << "circle";
	}
	else if (figureType == line) {
		std::cout << "line";
	}
}

void Figure::setX(const int& x) {
	this->x = x;
}

void Figure::setY(const int& y) {
	this->y = y;
}

void Figure::setFill(const std::string& color) {
	this->fill = color;
}

const int Figure::getX()const {
	return x;
}

const int Figure::getY()const {
	return y;
}

const std::string Figure::getFill()const {
	return fill;
}

const Figure::type Figure::getType()const {
	return figureType;
}