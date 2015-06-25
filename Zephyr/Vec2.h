#ifndef VEC2_H
#define VEC2_H
#include <iostream>
#include "Vec3.h"
#include "Vec4.h"

class Vec2
{
public:
	Vec2();
	Vec2(double x, double y);
	Vec2(Vec3 vec);
	Vec2(Vec4 vec);
	virtual ~Vec2();

	// Static methods
	static Vec2 Up();
	static Vec2 Down();
	static Vec2 Left();
	static Vec2 Right();

	double Length();
	double Dot(Vec2 vec);
	Vec2 Normalize();
	std::string ToString();

	// Operator overloads
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

	// Swizzling
	Vec2 xx();
	Vec2 xy();
	Vec2 yy();
	Vec2 yx();

	// Getters & setters
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