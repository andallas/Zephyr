#include "Vec3.h"
#include <sstream>

Vec3::Vec3()
{
	this->_x = 0;
	this->_y = 0;
	this->_z = 0;
}

Vec3::Vec3(double x, double y, double z)
{
	this->_x = x;
	this->_y = y;
	this->_z = z;
}

Vec3::~Vec3() { }

// Swizzling
Vec2 Vec3::xx()
{
	Vec2 vec;
	vec.Set(this->_x, this->_x);
	return vec;
}

Vec2 Vec3::xy()
{
	Vec2 vec;
	vec.Set(this->_x, this->_y);
	return vec;
}

Vec2 Vec3::xz()
{
	Vec2 vec;
	vec.Set(this->_x, this->_z);
	return vec;
}

Vec2 Vec3::yx()
{
	Vec2 vec;
	vec.Set(this->_y, this->_x);
	return vec;
}

Vec2 Vec3::yy()
{
	Vec2 vec;
	vec.Set(this->_y, this->_y);
	return vec;
}

Vec2 Vec3::yz()
{
	Vec2 vec;
	vec.Set(this->_y, this->_z);
	return vec;
}

Vec2 Vec3::zx()
{
	Vec2 vec;
	vec.Set(this->_z, this->_x);
	return vec;
}

Vec2 Vec3::zy()
{
	Vec2 vec;
	vec.Set(this->_z, this->_y);
	return vec;
}

Vec2 Vec3::zz()
{
	Vec2 vec;
	vec.Set(this->_z, this->_z);
	return vec;
}

Vec3 Vec3::xxx()
{
	Vec3 vec;
	vec.Set(this->_x, this->_x, this->_x);
	return vec;
}

Vec3 Vec3::xxy()
{
	Vec3 vec;
	vec.Set(this->_x, this->_x, this->_y);
	return vec;
}

Vec3 Vec3::xxz()
{
	Vec3 vec;
	vec.Set(this->_x, this->_x, this->_z);
	return vec;
}

Vec3 Vec3::xyx()
{
	Vec3 vec;
	vec.Set(this->_x, this->_y, this->_x);
	return vec;
}

Vec3 Vec3::xyy()
{
	Vec3 vec;
	vec.Set(this->_x, this->_y, this->_y);
	return vec;
}

Vec3 Vec3::xyz()
{
	Vec3 vec;
	vec.Set(this->_x, this->_y, this->_z);
	return vec;
}

Vec3 Vec3::xzx()
{
	Vec3 vec;
	vec.Set(this->_x, this->_z, this->_x);
	return vec;
}

Vec3 Vec3::xzy()
{
	Vec3 vec;
	vec.Set(this->_x, this->_z, this->_y);
	return vec;
}

Vec3 Vec3::xzz()
{
	Vec3 vec;
	vec.Set(this->_x, this->_z, this->_z);
	return vec;
}

Vec3 Vec3::yxx()
{
	Vec3 vec;
	vec.Set(this->_y, this->_x, this->_x);
	return vec;
}

Vec3 Vec3::yxy()
{
	Vec3 vec;
	vec.Set(this->_y, this->_x, this->_y);
	return vec;
}

Vec3 Vec3::yxz()
{
	Vec3 vec;
	vec.Set(this->_y, this->_x, this->_z);
	return vec;
}

Vec3 Vec3::yyx()
{
	Vec3 vec;
	vec.Set(this->_y, this->_y, this->_x);
	return vec;
}

Vec3 Vec3::yyy()
{
	Vec3 vec;
	vec.Set(this->_y, this->_y, this->_y);
	return vec;
}

Vec3 Vec3::yyz()
{
	Vec3 vec;
	vec.Set(this->_y, this->_y, this->_z);
	return vec;
}

Vec3 Vec3::yzx()
{
	Vec3 vec;
	vec.Set(this->_y, this->_z, this->_x);
	return vec;
}

Vec3 Vec3::yzy()
{
	Vec3 vec;
	vec.Set(this->_y, this->_z, this->_y);
	return vec;
}

Vec3 Vec3::yzz()
{
	Vec3 vec;
	vec.Set(this->_y, this->_z, this->_z);
	return vec;
}

Vec3 Vec3::zxx()
{
	Vec3 vec;
	vec.Set(this->_z, this->_x, this->_x);
	return vec;
}

Vec3 Vec3::zxy()
{
	Vec3 vec;
	vec.Set(this->_z, this->_x, this->_y);
	return vec;
}

Vec3 Vec3::zxz()
{
	Vec3 vec;
	vec.Set(this->_z, this->_x, this->_z);
	return vec;
}

Vec3 Vec3::zyx()
{
	Vec3 vec;
	vec.Set(this->_z, this->_y, this->_x);
	return vec;
}

Vec3 Vec3::zyy()
{
	Vec3 vec;
	vec.Set(this->_z, this->_y, this->_y);
	return vec;
}

Vec3 Vec3::zyz()
{
	Vec3 vec;
	vec.Set(this->_z, this->_y, this->_z);
	return vec;
}

Vec3 Vec3::zzx()
{
	Vec3 vec;
	vec.Set(this->_z, this->_z, this->_x);
	return vec;
}

Vec3 Vec3::zzy()
{
	Vec3 vec;
	vec.Set(this->_z, this->_z, this->_y);
	return vec;
}

Vec3 Vec3::zzz()
{
	Vec3 vec;
	vec.Set(this->_z, this->_z, this->_z);
	return vec;
}


double Vec3::Length()
{
	return sqrt(this->_x * this->_x + this->_y * this->_y);
}

double Vec3::Dot(Vec3 vec)
{
	return this->_x * vec.x() + this->_y * vec.y();
}

Vec3 Vec3::Normalize()
{
	*this /= this->Length();
	return *this;
}

std::string Vec3::ToString()
{
	std::string value;
	std::ostringstream stream;

	value = "(";
	stream << value << this->x();
	value = ", ";
	stream << value << this->y();
	value = ")";
	stream << value;

	return stream.str();
}

// Operator overloads
Vec3 Vec3::operator+(Vec3 vec)
{
	Vec3 vector;
	vector.Set(this->x() + vec.x(), this->y() + vec.y());
	return vector;
}

Vec3 Vec3::operator+(double scalar)
{
	Vec3 vector;
	vector.Set(this->x() + scalar, this->y() + scalar);
	return vector;
}

Vec3& Vec3::operator+=(Vec3 vec)
{
	this->Set(this->x() + vec.x(), this->y() + vec.y());
	return *this;
}

Vec3& Vec3::operator+=(double scalar)
{
	this->Set(this->x() + scalar, this->y() + scalar);
	return *this;
}


Vec3 Vec3::operator-(Vec3 vec)
{
	Vec3 vector;
	vector.Set(this->x() - vec.x(), this->y() - vec.y());
	return vector;
}

Vec3 Vec3::operator-(double scalar)
{
	Vec3 vector;
	vector.Set(this->x() - scalar, this->y() - scalar);
	return vector;
}

Vec3& Vec3::operator-=(Vec3 vec)
{
	this->Set(this->x() - vec.x(), this->y() - vec.y());
	return *this;
}

Vec3& Vec3::operator-=(double scalar)
{
	this->Set(this->x() - scalar, this->y() - scalar);
	return *this;
}


Vec3 Vec3::operator*(Vec3 vec)
{
	Vec3 vector;
	vector.Set(this->x() * vec.x(), this->y() * vec.y());
	return vector;
}

Vec3 Vec3::operator*(double scalar)
{
	Vec3 vector;
	vector.Set(this->x() * scalar, this->y() * scalar);
	return vector;
}

Vec3& Vec3::operator*=(Vec3 vec)
{
	this->Set(this->x() * vec.x(), this->y() * vec.y());
	return *this;
}

Vec3& Vec3::operator*=(double scalar)
{
	this->Set(this->x() * scalar, this->y() * scalar);
	return *this;
}


Vec3 Vec3::operator/(Vec3 vec)
{
	Vec3 vector;
	vector.Set(this->x() / vec.x(), this->y() / vec.y());
	return vector;
}

Vec3 Vec3::operator/(double scalar)
{
	Vec3 vector;
	vector.Set(this->x() / scalar, this->y() / scalar);
	return vector;
}

Vec3& Vec3::operator/=(Vec3 vec)
{
	this->Set(this->x() / vec.x(), this->y() / vec.y());
	return *this;
}

Vec3& Vec3::operator/=(double scalar)
{
	this->Set(this->x() / scalar, this->y() / scalar);
	return *this;
}


void Vec3::Set(double x, double y, double z)
{
	this->_x = x;
	this->_y = y;
	this->_z = z;
}

double Vec3::x()
{
	return this->_x;
}

double Vec3::y()
{
	return this->_y;
}

double Vec3::z()
{
	return this->_z;
}

void Vec3::x(double x)
{
	this->_x = x;
}

void Vec3::y(double y)
{
	this->_y = y;
}

void Vec3::z(double z)
{
	this->_z = z;
}