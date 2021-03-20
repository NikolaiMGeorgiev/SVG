#pragma once
#include <iostream>
#include "Point.h"

class Figure {
private:
	int x;
	int y;
	std::string fill;
public:
	enum type { line, circle, rectangle };

	Figure();
	Figure(const int&,  const int&, const std::string&);

	virtual bool isWithin(const int&, const int&, const int&, const int&)const;
	virtual bool isWithin(const int&, const int&, const int&)const;

	virtual void print()const = 0;
	void printType()const;

	virtual void setX(const int&);
	virtual void setY(const int&);
	void setFill(const std::string&);

	const int getX()const;
	const int getY()const;
	const std::string getFill()const;
	const type getType()const;
protected:
	type figureType;
};
