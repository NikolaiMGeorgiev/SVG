#include <string>
#include "Line.h"

Line::Line() {
	endPoint = new Point();
	figureType = line;
}

Line::Line(const int& x1, const int& y1, const int& x2, const int& y2, 
	const std::string& fill) :
	Figure(x1, y1, fill) {
	endPoint = new Point(x2, y2);
	figureType = line;
}

Line::Line(const Line& line) {
	endPoint = new Point(line.getX2(), line.getY2());
	setX(line.getX());
	setY(line.getY());
	setFill(line.getFill());
	figureType = Figure::line;
}

Line& Line::operator=(const Line& line) {
	endPoint->setX(line.getX2());
	endPoint->setY(line.getY2());
	setX(line.getX());
	setY(line.getY());
	setFill(line.getFill());

	return *this;
 }

bool Line::isWithin(const int& x, const int& y, const int& width, const int& height)const {
	if (getX() >= x && getX() <= (x + width) && getY() >= y && getY() <= (y + height)
		&& endPoint->getX() >= x && endPoint->getX() <= (x + width)
		&& endPoint->getY() >= y && endPoint->getY() <= (y + height)) {
		return true;
	}
	return false;
}

bool Line::isWithin(const int& x, const int& y, const int& radius)const {
	Point startPoint(getX(), getY());
	Point circleCenter(x + radius, y + radius);

	if (startPoint.getDistanceTo(circleCenter) <= radius
		&& endPoint->getDistanceTo(circleCenter) <= radius) {
		return true;
	}

	return false;
}

void Line::print()const {
	Figure::print();
	std::cout << endPoint->getX() << " " << endPoint->getY() << " " << getFill() << std::endl;
}

void Line::setX2(const int& x2) {
	endPoint->setX(x2);
}

void Line::setY2(const int& y2) {
	endPoint->setY(y2);
}

const int Line::getX2()const {
	return endPoint->getX();
}

const int Line::getY2()const {
	return endPoint->getY();
}

Line::~Line() {
	delete endPoint;
}