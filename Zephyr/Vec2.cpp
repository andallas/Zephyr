#include "Vec2.h"
#include <sstream>

Vec2::Vec2() : _x(0), _y(0) { }

Vec2::Vec2(double x, double y) : _x(x), _y(y) { }

Vec2::Vec2(Vec3 vec) : _x(vec.x()), _y(vec.y()) { }

Vec2::Vec2(Vec4 vec) : _x(vec.x()), _y(vec.y()) { }

Vec2::~Vec2() { }


// Static methods
Vec2 Vec2::Up()
{
	return Vec2(0, 1);
}

Vec2 Vec2::Down()
{
	return Vec2(0, -1);
}

Vec2 Vec2::Left()
{
	return Vec2(-1, 0);
}

Vec2 Vec2::Right()
{
	return Vec2(1, 0);
}


double Vec2::Magnitude()
{
	return sqrt(this->_x * this->_x + this->_y * this->_y);
}

double Vec2::Dot(Vec2 vec)
{
	return this->_x * vec.x() + this->_y * vec.y();
}

Vec2 Vec2::Normalize()
{
	double fMag = (this->_x * this->_x + this->_y * this->_y);
	if (fMag == 0)
		return *this;

	float fMult = 1.0 / sqrtf(fMag);
	this->_x *= fMult;
	this->_y *= fMult;

	return *this;
}

double Vec2::Distance(Vec2 vec)
{
	return (*this - vec).Magnitude();
}

std::string Vec2::ToString()
{
	std::string value;
	std::ostringstream stream;

	value = "(";
	stream << value << this->_x;
	value = ", ";
	stream << value << this->_y;
	value = ")";
	stream << value;

	return stream.str();
}


// Operator overloads
bool Vec2::operator==(Vec2 vec)
{
	return (this->_x == vec.x() && this->_y == vec.y());
}

Vec2 Vec2::operator+(Vec2 vec)
{
	Vec2 vector;
	vector.Set(this->_x + vec.x(), this->_y + vec.y());
	return vector;
}

Vec2 Vec2::operator+(double scalar)
{
	Vec2 vector;
	vector.Set(this->_x + scalar, this->_y + scalar);
	return vector;
}

Vec2& Vec2::operator+=(Vec2 vec)
{
	this->Set(this->_x + vec.x(), this->_y + vec.y());
	return *this;
}

Vec2& Vec2::operator+=(double scalar)
{
	this->Set(this->_x + scalar, this->_y + scalar);
	return *this;
}

Vec2 Vec2::operator-()
{
	Vec2 vector;
	vector.Set(-this->_x, -this->_y);
	return vector;
}

Vec2 Vec2::operator-(Vec2 vec)
{
	Vec2 vector;
	vector.Set(this->_x - vec.x(), this->_y - vec.y());
	return vector;
}

Vec2 Vec2::operator-(double scalar)
{
	Vec2 vector;
	vector.Set(this->_x - scalar, this->_y - scalar);
	return vector;
}

Vec2& Vec2::operator-=(Vec2 vec)
{
	this->Set(this->_x - vec.x(), this->_y - vec.y());
	return *this;
}

Vec2& Vec2::operator-=(double scalar)
{
	this->Set(this->_x - scalar, this->_y - scalar);
	return *this;
}

Vec2 Vec2::operator*(Vec2 vec)
{
	Vec2 vector;
	vector.Set(this->_x * vec.x(), this->_y * vec.y());
	return vector;
}

Vec2 Vec2::operator*(double scalar)
{
	Vec2 vector;
	vector.Set(this->_x * scalar, this->_y * scalar);
	return vector;
}

Vec2& Vec2::operator*=(Vec2 vec)
{
	this->Set(this->_x * vec.x(), this->_y * vec.y());
	return *this;
}

Vec2& Vec2::operator*=(double scalar)
{
	this->Set(this->_x * scalar, this->_y * scalar);
	return *this;
}

Vec2 Vec2::operator/(Vec2 vec)
{
	Vec2 vector;
	vector.Set(this->_x / vec.x(), this->_y / vec.y());
	return vector;
}

Vec2 Vec2::operator/(double scalar)
{
	Vec2 vector;
	vector.Set(this->_x / scalar, this->_y / scalar);
	return vector;
}

Vec2& Vec2::operator/=(Vec2 vec)
{
	this->Set(this->_x / vec.x(), this->_y / vec.y());
	return *this;
}

Vec2& Vec2::operator/=(double scalar)
{
	this->Set(this->_x / scalar, this->_y / scalar);
	return *this;
}

double Vec2::operator[](int index)
{
	switch (index)
	{
	case 0:
		return this->_x;
	default:
		return this->_y;
	}
}

// Swizzling
Vec2 Vec2::xx()
{
	Vec2 vec;
	vec.Set(this->_x, this->_x);
	return vec;
}

Vec2 Vec2::xy()
{
	Vec2 vec;
	vec.Set(this->_x, this->_y);
	return vec;
}

Vec2 Vec2::yy()
{
	Vec2 vec;
	vec.Set(this->_y, this->_y);
	return vec;
}

Vec2 Vec2::yx()
{
	Vec2 vec;
	vec.Set(this->_y, this->_x);
	return vec;
}


// Getters & setters
void Vec2::Set(double x, double y)
{
	this->_x = x;
	this->_y = y;
}

double Vec2::x()
{
	return this->_x;
}

double Vec2::y()
{
	return this->_y;
}

void Vec2::x(double x)
{
	this->_x = x;
}

void Vec2::y(double y)
{
	this->_y = y;
}