#include <string>
#include "Rectangle.h"

Rectangle::Rectangle():width(0), height(0){
	figureType = rectangle;
	initPoints(0, 0, 0, 0);
}

Rectangle::Rectangle(const int& x, const int& y, const int& width, const int& height, std::string fill):
	Figure(x, y, fill), width(width), height(height) {
	figureType = rectangle;
	initPoints(x, y, width, height);
}

Rectangle::Rectangle(const Rectangle& rect): Figure(rect.getX(), rect.getY(), rect.getFill()), 
width(rect.getWidth()), height(rect.getHeight()) {
	figureType = rectangle;
	initPoints(rect.getX(), rect.getY(), rect.width, rect.height);
}

Rectangle& Rectangle::operator=(const Rectangle& rect) {
	delete topLeftP;
	delete botLeftP;
	delete topRightP;
	delete botRightP;

	setX(rect.getX());
	setY(rect.getY());
	setFill(rect.getFill());
	width = rect.width;
	height = rect.height;

	initPoints(rect.getX(), rect.getY(), rect.width, rect.height);

	return *this;
}

void Rectangle::initPoints(const int& x, const int& y, const int& width, const int& height) {
	topLeftP = new Point(this->getX(), this->getY());
	botLeftP = new Point(this->getX(), this->getY() + this->height);
	topRightP = new Point(this->getX() + this->width, this->getY());
	botRightP = new Point(this->getX() + this->width, this->getY() + this->height);
}

bool Rectangle::isWithin(const int& x, const int& y, const int& width, const int& height)const {
	if (isWithinBotLeft(x, y, width, height) && isWithinBotRight(x, y, width, height) 
		&& isWithinTopLeft(x, y, width, height) && isWithinTopRight(x, y, width, height)) {
		return true;
	}
	return false;
}

bool Rectangle::isWithin(const int& x, const int& y, const int& radius)const {
	Point circleCenter(x + radius, y + radius);
	if (topLeftP->getDistanceTo(circleCenter) <= radius 
		&& topRightP->getDistanceTo(circleCenter) <= radius
		&& botLeftP->getDistanceTo(circleCenter) <= radius 
		&& botRightP->getDistanceTo(circleCenter) <= radius) {
		return true;
	}
	return false;
}

void Rectangle::print()const {
	Figure::print();
	std::cout << width << " " << height << " " << getFill() << std::endl;
}

bool Rectangle::isWithinTopLeft(const int& x, const int& y, const int& width,
	const int& height)const {
	if (topLeftP->getX() >= x && topLeftP->getY() >= y) {
		return true;
	}
	return false;
}

bool Rectangle::isWithinTopRight(const int& x, const int& y, const int& width,
	const int& height)const {
	if (topRightP->getX() <= (x + width) && topRightP->getY() >= y) {
		return true;
	}
	return false;
}

bool Rectangle::isWithinBotLeft(const int& x, const int& y, const int& width,
	const int& height)const {
	if (botLeftP->getX() >= x && botLeftP->getY() <= (y + height)) {
		return true;
	}
	return false;
}

bool Rectangle::isWithinBotRight(const int& x, const int& y, const int& width,
	const int& height)const {
	if (botRightP->getX() <= (x + width) && botRightP->getY() <= (y + height)) {
		return true;
	}
	return false;
}

void Rectangle::setX(const int& x) {
	this->Figure::setX(x);
	topLeftP->setX(x);
	botLeftP->setX(x);
	topRightP->setX(x + width);
	botRightP->setX(x + width);
}

void Rectangle::setY(const int& y){
	this->Figure::setY(y);
	topLeftP->setY(y);
	botLeftP->setY(y + height);
	topRightP->setY(y);
	botRightP->setY(y + height);
	}

void Rectangle::setWidth(const int& width) {
	this->width = width;
	topRightP->setX(getX() + width);
	botRightP->setX(getX() + width);
}

void Rectangle::setHeight(const int& height) {
	this->height = height;
	botLeftP->setY(getY() + height);
	botRightP->setY(getY() + height);
}

const int Rectangle::getWidth()const {
	return width;
}

const int Rectangle::getHeight()const {
	return height;
}

const Point* Rectangle::getTopLeftP()const {
	return topLeftP;
}

const Point* Rectangle::getBotLeftP()const {
	return botLeftP;
}

const Point* Rectangle::getTopRightP()const {
	return topRightP;
}

const Point* Rectangle::getBotRightP()const {
	return botRightP;
}

Rectangle::~Rectangle() {
	delete topLeftP;
	delete botLeftP;
	delete topRightP;
	delete botRightP;
}