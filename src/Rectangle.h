#pragma once
#include "Figure.h"
#include "Point.h"

class Rectangle: public Figure {
private:
	Point* topLeftP;
	Point* topRightP;
	Point* botLeftP;
	Point* botRightP;

	int width;
	int height;

	bool isWithinTopLeft(const int&, const int&, const int&, const int&)const;
	bool isWithinTopRight(const int&, const int&, const int&, const int&)const;
	bool isWithinBotLeft(const int&, const int&, const int&, const int&)const;
	bool isWithinBotRight(const int&, const int&, const int&, const int&)const;

	void initPoints(const int&, const int&, const int&, const int&);
public:
	Rectangle();
	Rectangle(const int&, const int&, const int&, const int&, std::string);
	Rectangle(const Rectangle&);
	Rectangle& operator=(const Rectangle&);

	bool isWithin(const int&, const int&, const int&, const int&)const override;
	bool isWithin(const int&, const int&, const int&)const override;

	void print()const override;

	void setWidth(const int&);
	void setHeight(const int&);
	void setX(const int&) override;
	void setY(const int&) override;

	const int getWidth()const;
	const int getHeight()const;
	const Point* getTopLeftP()const;
	const Point* getBotLeftP()const;
	const Point* getTopRightP()const;
	const Point* getBotRightP()const;

	~Rectangle();
};
