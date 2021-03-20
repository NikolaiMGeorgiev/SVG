#include <iostream>
#include "Point.h"

Point::Point():x(0), y(0) {

}

Point::Point(const int& x, const int& y):x(x), y(y) {

}

const int Point::getDistanceTo(const int& x, const int& y) {
	return sqrt((this->x - x)*(this->x - x) + (this->y - y)*(this->y - y));
}

const int Point::getDistanceTo(const Point& point) {
	return sqrt((this->x - point.getX())*(this->x - point.getX()) 
		+ (this->y - point.getY())*(this->y - point.getY()));
}

void Point::setX(const int& x) {
	this->x = x;
}

void Point::setY(const int& y) {
	this->y = y;
}

const int Point::getX()const {
	return x;
}

const int Point::getY()const {
	return y;
}