#pragma once
#include "Figure.h"

class Circle: public Figure {
private:
	int radius;
	Point* center;
public:
	Circle();
	Circle(const int&, const int&, const int&, const std::string&);
	Circle(const Circle&);
	Circle& operator=(const Circle&);

	bool isWithin(const int&, const int&, const int&, const int&)const override;
	bool isWithin(const int&, const int&, const int&)const override;

	void print()const override;

	void setRadius(const int&);

	const int getRadius()const;

	void setX(const int&) override;
	void setY(const int&) override;

	~Circle();
};
