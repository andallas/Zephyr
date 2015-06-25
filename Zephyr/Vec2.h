#ifndef VEC2_H
#define VEC2_H
#include <iostream>

class Vec2
{
public:
	Vec2();
	Vec2(double x, double y);
	virtual ~Vec2();

	// Swizzling
	Vec2 xx();
	Vec2 yy();
	Vec2 yx();

	double Length();
	double Dot(Vec2 vec);
	Vec2 Normalize();
	std::string ToString();

	Vec2 operator+(Vec2 vec);
	Vec2 operator+(double scalar);
	Vec2& operator+=(Vec2 vec);
	Vec2& operator+=(double scalar);

	Vec2 operator-(Vec2 vec);
	Vec2 operator-(double scalar);
	Vec2& operator-=(Vec2 vec);
	Vec2& operator-=(double scalar);

	Vec2 operator*(Vec2 vec);
	Vec2 operator*(double scalar);
	Vec2& operator*=(Vec2 vec);
	Vec2& operator*=(double scalar);

	Vec2 operator/(Vec2 vec);
	Vec2 operator/(double scalar);
	Vec2& operator/=(Vec2 vec);
	Vec2& operator/=(double scalar);

	double x();
	double y();

	void Set(double x, double y);
	void x(double x);
	void y(double y);

private:
	double _x;
	double _y;
};

#endif