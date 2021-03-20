#include <string>
#include "Circle.h"
#include "Rectangle.h"

Circle::Circle():radius(0) {
	figureType = circle;
	center = new Point();
}

Circle::Circle(const int& x, const int& y, const int& radius, const std::string& fill) :
	Figure(x, y, fill), radius(radius) {
	figureType = Figure::circle;
	center = new Point(getX() + getRadius(), getY() + getRadius());
}

Circle::Circle(const Circle& circle): Figure(circle.getX(), circle.getY(), circle.getFill()),
radius(circle.getRadius()){
	figureType = Figure::circle;
	center = new Point(circle.getX() + circle.getRadius(), circle.getY() + circle.getRadius());
}

Circle& Circle::operator=(const Circle& circle) {
	delete center;

	figureType = Figure::circle;
	setX(circle.getX());
	setY(circle.getY());
	setFill(circle.getFill());
	setRadius(circle.getRadius());
	center = new Point(circle.getX() + circle.getRadius(), circle.getY() + circle.getRadius());
	
	return *this;
}

bool Circle::isWithin(const int& x, const int& y, const int& width, const int& height)const {
	if (this->getX() >= x && this->getY() >= y 
		&& (this->getX() + 2 * getRadius()) <= (x + width) 
		&& (this->getY() + 2 * getRadius()) <= (y + height)) {
		return true;
	}

	return false;
}

bool Circle::isWithin(const int& x, const int& y, const int& radius)const {
	Point areaCenter(x + radius, y + radius); 

	if (this->getX() >= x && this->getY() >= y && this->getRadius() <= radius
		&& areaCenter.getDistanceTo(*center) + this->radius <= radius) {
		return true;
	}

	return false;
}

void Circle::print()const {
	Figure::print();
	std::cout << radius << " " << getFill() << std::endl;
}

void Circle::setX(const int& x) {
	Figure::setX(x);
	center->setX(x + getRadius());
}

void Circle::setY(const int& y) {
	Figure::setY(y);
	center->setY(y + getRadius());
}

void Circle::setRadius(const int& radius) {
	this->radius = radius;
}

const int Circle::getRadius()const {
	return radius;
}

Circle::~Circle() {
	delete center;
}