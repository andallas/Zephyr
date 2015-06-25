#ifndef VEC3_H
#define VEC3_H
#include <iostream>
#include "Vec2.h"

class Vec3
{
public:
	Vec3();
	Vec3(double x, double y, double z);
	virtual ~Vec3();

	// Static methods
	static Vec3 Up();
	static Vec3 Down();
	static Vec3 Left();
	static Vec3 Right();
	static Vec3 Forward();
	static Vec3 Backward();

	double Length();
	double Dot(Vec3 vec);
	Vec3 Cross(Vec3 vec);
	Vec3 Normalize();
	std::string ToString();

	// Operator Overloads
	Vec3 operator+(Vec3 vec);
	Vec3 operator+(double scalar);
	Vec3& operator+=(Vec3 vec);
	Vec3& operator+=(double scalar);
	Vec3 operator-(Vec3 vec);
	Vec3 operator-(double scalar);
	Vec3& operator-=(Vec3 vec);
	Vec3& operator-=(double scalar);
	Vec3 operator*(Vec3 vec);
	Vec3 operator*(double scalar);
	Vec3& operator*=(Vec3 vec);
	Vec3& operator*=(double scalar);
	Vec3 operator/(Vec3 vec);
	Vec3 operator/(double scalar);
	Vec3& operator/=(Vec3 vec);
	Vec3& operator/=(double scalar);

	// Swizzling
	Vec2 xx();
	Vec2 xy();
	Vec2 xz();
	Vec2 yx();
	Vec2 yy();
	Vec2 yz();
	Vec2 zx();
	Vec2 zy();
	Vec2 zz();
	Vec3 xxx();
	Vec3 xxy();
	Vec3 xxz();
	Vec3 xyx();
	Vec3 xyy();
	Vec3 xyz();
	Vec3 xzx();
	Vec3 xzy();
	Vec3 xzz();
	Vec3 yxx();
	Vec3 yxy();
	Vec3 yxz();
	Vec3 yyx();
	Vec3 yyy();
	Vec3 yyz();
	Vec3 yzx();
	Vec3 yzy();
	Vec3 yzz();
	Vec3 zxx();
	Vec3 zxy();
	Vec3 zxz();
	Vec3 zyx();
	Vec3 zyy();
	Vec3 zyz();
	Vec3 zzx();
	Vec3 zzy();
	Vec3 zzz();

	// Getters & setters
	double x();
	double y();
	double z();

	void Set(double x, double y, double z);
	void x(double x);
	void y(double y);
	void z(double z);

private:
	double _x;
	double _y;
	double _z;
};

#endif