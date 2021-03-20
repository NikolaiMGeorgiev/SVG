#pragma once
class Point {
private: 
	int x;
	int y;
public:
	Point();
	Point(const int&, const int&);

	const int getDistanceTo(const int&, const int&);
	const int getDistanceTo(const Point&);

	void setX(const int&);
	void setY(const int&);

	const int getX()const;
	const int getY()const;
};