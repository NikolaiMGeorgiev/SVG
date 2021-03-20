#pragma once
#include "Figure.h"

class Line : public Figure {
private:
	Point* endPoint;
public:
	Line();
	Line(const int&, const int&, const int&, const int&, const std::string&);
	Line(const Line&);
	Line& operator=(const Line&);

	bool isWithin(const int&, const int&, const int&, const int&)const override;
	bool isWithin(const int&, const int&, const int&)const override;

	void print()const override;

	void setX2(const int&);
	void setY2(const int&);

	const int getX2()const;
	const int getY2()const;

	~Line();
};
