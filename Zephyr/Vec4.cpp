#include "Vec4.h"
#include <sstream>

Vec4::Vec4()
{
	this->_x = 0;
	this->_y = 0;
	this->_z = 0;
	this->_w = 0;
}

Vec4::Vec4(double x, double y, double z, double w)
{
	this->_x = x;
	this->_y = y;
	this->_z = z;
	this->_w = w;
}

Vec4::~Vec4() { }


// Static methods
Vec4 Vec4::Up()
{
	return Vec4(0, 1, 0, 0);
}

Vec4 Vec4::Down()
{
	return Vec4(0, -1, 0, 0);
}

Vec4 Vec4::Left()
{
	return Vec4(-1, 0, 0, 0);
}

Vec4 Vec4::Right()
{
	return Vec4(1, 0, 0, 0);
}

Vec4 Vec4::Forward()
{
	return Vec4(0, 0, 1, 0);
}

Vec4 Vec4::Backward()
{
	return Vec4(0, 0, -1, 0);
}


double Vec4::Length()
{
	return sqrt(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z + this->_w * this->_w);
}

double Vec4::Dot(Vec4 vec)
{
	return this->_x * vec.x() + this->_y * vec.y() + this->_z * vec.z() + this->_w * vec.w();
}

Vec3 Vec4::Cross(Vec4 vec)
{
	Vec3 newVec;
	newVec.Set(this->_y * vec.z() - this->_z * vec.y(),
		this->_z * vec.x() - this->_x * vec.z(),
		this->_x * vec.y() - this->_y * vec.x());
	return newVec;
}

Vec4 Vec4::Normalize()
{
	*this /= this->Length();
	return *this;
}

std::string Vec4::ToString()
{
	std::string value;
	std::ostringstream stream;

	value = "(";
	stream << value << this->_x;
	value = ", ";
	stream << value << this->_y;
	value = ", ";
	stream << value << this->_z;
	value = ", ";
	stream << value << this->_w;
	value = ")";
	stream << value;

	return stream.str();
}


// Operator overloads
Vec4 Vec4::operator+(Vec4 vec)
{
	Vec4 vector;
	vector.Set(this->_x + vec.x(), this->_y + vec.y(), this->_z + vec.z(), this->_w + vec.w());
	return vector;
}

Vec4 Vec4::operator+(double scalar)
{
	Vec4 vector;
	vector.Set(this->_x + scalar, this->_y + scalar, this->_z + scalar, this->_w + scalar);
	return vector;
}

Vec4& Vec4::operator+=(Vec4 vec)
{
	this->Set(this->_x + vec.x(), this->_y + vec.y(), this->_z + vec.z(), this->_w + vec.w());
	return *this;
}

Vec4& Vec4::operator+=(double scalar)
{
	this->Set(this->_x + scalar, this->_y + scalar, this->_z + scalar, this->_w + scalar);
	return *this;
}

Vec4 Vec4::operator-(Vec4 vec)
{
	Vec4 vector;
	vector.Set(this->_x - vec.x(), this->_y - vec.y(), this->_z - vec.z(), this->_w - vec.w());
	return vector;
}

Vec4 Vec4::operator-(double scalar)
{
	Vec4 vector;
	vector.Set(this->_x - scalar, this->_y - scalar, this->_z - scalar, this->_w - scalar);
	return vector;
}

Vec4& Vec4::operator-=(Vec4 vec)
{
	this->Set(this->_x - vec.x(), this->_y - vec.y(), this->_z - vec.z(), this->_w - vec.w());
	return *this;
}

Vec4& Vec4::operator-=(double scalar)
{
	this->Set(this->_x - scalar, this->_y - scalar, this->_z - scalar, this->_w - scalar);
	return *this;
}

Vec4 Vec4::operator*(Vec4 vec)
{
	Vec4 vector;
	vector.Set(this->_x * vec.x(), this->_y * vec.y(), this->_z * vec.z(), this->_w * vec.w());
	return vector;
}

Vec4 Vec4::operator*(double scalar)
{
	Vec4 vector;
	vector.Set(this->_x * scalar, this->_y * scalar, this->_z * scalar, this->_w * scalar);
	return vector;
}

Vec4& Vec4::operator*=(Vec4 vec)
{
	this->Set(this->_x * vec.x(), this->_y * vec.y(), this->_z * vec.z(), this->_w * vec.w());
	return *this;
}

Vec4& Vec4::operator*=(double scalar)
{
	this->Set(this->_x * scalar, this->_y * scalar, this->_z * scalar, this->_w * scalar);
	return *this;
}

Vec4 Vec4::operator/(Vec4 vec)
{
	Vec4 vector;
	vector.Set(this->_x / vec.x(), this->_y / vec.y(), this->_z / vec.z(), this->_w / vec.w());
	return vector;
}

Vec4 Vec4::operator/(double scalar)
{
	Vec4 vector;
	vector.Set(this->_x / scalar, this->_y / scalar, this->_z / scalar, this->_w / scalar);
	return vector;
}

Vec4& Vec4::operator/=(Vec4 vec)
{
	this->Set(this->_x / vec.x(), this->_y / vec.y(), this->_z / vec.z(), this->_w / vec.w());
	return *this;
}

Vec4& Vec4::operator/=(double scalar)
{
	this->Set(this->_x / scalar, this->_y / scalar, this->_z / scalar, this->_w / scalar);
	return *this;
}


// Swizzling
Vec2 Vec4::xx()
{
	Vec2 vec;
	vec.Set(this->_x, this->_x);
	return vec;
}

Vec2 Vec4::xy()
{
	Vec2 vec;
	vec.Set(this->_x, this->_y);
	return vec;
}

Vec2 Vec4::xz()
{
	Vec2 vec;
	vec.Set(this->_x, this->_z);
	return vec;
}

Vec2 Vec4::xw()
{
	Vec2 vec;
	vec.Set(this->_x, this->_w);
	return vec;
}

Vec2 Vec4::yx()
{
	Vec2 vec;
	vec.Set(this->_y, this->_x);
	return vec;
}

Vec2 Vec4::yy()
{
	Vec2 vec;
	vec.Set(this->_y, this->_y);
	return vec;
}

Vec2 Vec4::yz()
{
	Vec2 vec;
	vec.Set(this->_y, this->_z);
	return vec;
}

Vec2 Vec4::yw()
{
	Vec2 vec;
	vec.Set(this->_y, this->_w);
	return vec;
}

Vec2 Vec4::zx()
{
	Vec2 vec;
	vec.Set(this->_z, this->_x);
	return vec;
}

Vec2 Vec4::zy()
{
	Vec2 vec;
	vec.Set(this->_z, this->_y);
	return vec;
}

Vec2 Vec4::zz()
{
	Vec2 vec;
	vec.Set(this->_z, this->_z);
	return vec;
}

Vec2 Vec4::zw()
{
	Vec2 vec;
	vec.Set(this->_z, this->_w);
	return vec;
}

Vec2 Vec4::wx()
{
	Vec2 vec;
	vec.Set(this->_w, this->_x);
	return vec;
}

Vec2 Vec4::wy()
{
	Vec2 vec;
	vec.Set(this->_w, this->_y);
	return vec;
}

Vec2 Vec4::wz()
{
	Vec2 vec;
	vec.Set(this->_w, this->_z);
	return vec;
}

Vec2 Vec4::ww()
{
	Vec2 vec;
	vec.Set(this->_w, this->_w);
	return vec;
}

Vec3 Vec4::xxx()
{
	Vec3 vec;
	vec.Set(this->_x, this->_x, this->_x);
	return vec;
}

Vec3 Vec4::xxy()
{
	Vec3 vec;
	vec.Set(this->_x, this->_x, this->_y);
	return vec;
}

Vec3 Vec4::xxz()
{
	Vec3 vec;
	vec.Set(this->_x, this->_x, this->_z);
	return vec;
}

Vec3 Vec4::xyx()
{
	Vec3 vec;
	vec.Set(this->_x, this->_y, this->_x);
	return vec;
}

Vec3 Vec4::xyy()
{
	Vec3 vec;
	vec.Set(this->_x, this->_y, this->_y);
	return vec;
}

Vec3 Vec4::xyz()
{
	Vec3 vec;
	vec.Set(this->_x, this->_y, this->_z);
	return vec;
}

Vec3 Vec4::xzx()
{
	Vec3 vec;
	vec.Set(this->_x, this->_z, this->_x);
	return vec;
}

Vec3 Vec4::xzy()
{
	Vec3 vec;
	vec.Set(this->_x, this->_z, this->_y);
	return vec;
}

Vec3 Vec4::xzz()
{
	Vec3 vec;
	vec.Set(this->_x, this->_z, this->_z);
	return vec;
}

Vec3 Vec4::yxx()
{
	Vec3 vec;
	vec.Set(this->_y, this->_x, this->_x);
	return vec;
}

Vec3 Vec4::yxy()
{
	Vec3 vec;
	vec.Set(this->_y, this->_x, this->_y);
	return vec;
}

Vec3 Vec4::yxz()
{
	Vec3 vec;
	vec.Set(this->_y, this->_x, this->_z);
	return vec;
}

Vec3 Vec4::yyx()
{
	Vec3 vec;
	vec.Set(this->_y, this->_y, this->_x);
	return vec;
}

Vec3 Vec4::yyy()
{
	Vec3 vec;
	vec.Set(this->_y, this->_y, this->_y);
	return vec;
}

Vec3 Vec4::yyz()
{
	Vec3 vec;
	vec.Set(this->_y, this->_y, this->_z);
	return vec;
}

Vec3 Vec4::yzx()
{
	Vec3 vec;
	vec.Set(this->_y, this->_z, this->_x);
	return vec;
}

Vec3 Vec4::yzy()
{
	Vec3 vec;
	vec.Set(this->_y, this->_z, this->_y);
	return vec;
}

Vec3 Vec4::yzz()
{
	Vec3 vec;
	vec.Set(this->_y, this->_z, this->_z);
	return vec;
}

Vec3 Vec4::zxx()
{
	Vec3 vec;
	vec.Set(this->_z, this->_x, this->_x);
	return vec;
}

Vec3 Vec4::zxy()
{
	Vec3 vec;
	vec.Set(this->_z, this->_x, this->_y);
	return vec;
}

Vec3 Vec4::zxz()
{
	Vec3 vec;
	vec.Set(this->_z, this->_x, this->_z);
	return vec;
}

Vec3 Vec4::zyx()
{
	Vec3 vec;
	vec.Set(this->_z, this->_y, this->_x);
	return vec;
}

Vec3 Vec4::zyy()
{
	Vec3 vec;
	vec.Set(this->_z, this->_y, this->_y);
	return vec;
}

Vec3 Vec4::zyz()
{
	Vec3 vec;
	vec.Set(this->_z, this->_y, this->_z);
	return vec;
}

Vec3 Vec4::zzx()
{
	Vec3 vec;
	vec.Set(this->_z, this->_z, this->_x);
	return vec;
}

Vec3 Vec4::zzy()
{
	Vec3 vec;
	vec.Set(this->_z, this->_z, this->_y);
	return vec;
}

Vec3 Vec4::zzz()
{
	Vec3 vec;
	vec.Set(this->_z, this->_z, this->_z);
	return vec;
}



Vec4 Vec4::xxxx()
{

}

Vec4 Vec4::xxxy()
{

}

Vec4 Vec4::xxxz()
{

}

Vec4 Vec4::xxyx()
{

}

Vec4 Vec4::xxyy()
{

}

Vec4 Vec4::xxyz()
{

}

Vec4 Vec4::xxzx()
{

}

Vec4 Vec4::xxzy()
{

}

Vec4 Vec4::xxzz()
{

}

Vec4 Vec4::xyxx()
{

}

Vec4 Vec4::xyxy()
{

}

Vec4 Vec4::xyxz()
{

}

Vec4 Vec4::xyyx()
{

}

Vec4 Vec4::xyyy()
{

}

Vec4 Vec4::xyyz()
{

}

Vec4 Vec4::xyzx()
{

}

Vec4 Vec4::xyzy()
{

}

Vec4 Vec4::xyzz()
{

}

Vec4 Vec4::xzxx()
{

}

Vec4 Vec4::xzxy()
{

}

Vec4 Vec4::xzxz()
{

}

Vec4 Vec4::xzyx()
{

}

Vec4 Vec4::xzyy()
{

}

Vec4 Vec4::xzyz()
{

}

Vec4 Vec4::xzzx()
{

}

Vec4 Vec4::xzzy()
{

}

Vec4 Vec4::xzzz()
{

}

Vec4 Vec4::yxxx()
{

}

Vec4 Vec4::yxxy()
{

}

Vec4 Vec4::yxxz()
{

}

Vec4 Vec4::yxyx()
{

}

Vec4 Vec4::yxyy()
{

}

Vec4 Vec4::yxyz()
{

}

Vec4 Vec4::yxzx()
{

}

Vec4 Vec4::yxzy()
{

}

Vec4 Vec4::yxzz()
{

}

Vec4 Vec4::yyxx()
{

}

Vec4 Vec4::yyxy()
{

}

Vec4 Vec4::yyxz()
{

}

Vec4 Vec4::yyyx()
{

}

Vec4 Vec4::yyyy()
{

}

Vec4 Vec4::yyyz()
{

}

Vec4 Vec4::yyzx()
{

}

Vec4 Vec4::yyzy()
{

}

Vec4 Vec4::yyzz()
{

}

Vec4 Vec4::yzxx()
{

}

Vec4 Vec4::yzxy()
{

}

Vec4 Vec4::yzxz()
{

}

Vec4 Vec4::yzyx()
{

}

Vec4 Vec4::yzyy()
{

}

Vec4 Vec4::yzyz()
{

}

Vec4 Vec4::yzzx()
{

}

Vec4 Vec4::yzzy()
{

}

Vec4 Vec4::yzzz()
{

}

Vec4 Vec4::zxxx()
{

}

Vec4 Vec4::zxxy()
{

}

Vec4 Vec4::zxxz()
{

}

Vec4 Vec4::zxyx()
{

}

Vec4 Vec4::zxyy()
{

}

Vec4 Vec4::zxyz()
{

}

Vec4 Vec4::zxzx()
{

}

Vec4 Vec4::zxzy()
{

}

Vec4 Vec4::zxzz()
{

}

Vec4 Vec4::zyxx()
{

}

Vec4 Vec4::zyxy()
{

}

Vec4 Vec4::zyxz()
{

}

Vec4 Vec4::zyyx()
{

}

Vec4 Vec4::zyyy()
{

}

Vec4 Vec4::zyyz()
{

}

Vec4 Vec4::zyzx()
{

}

Vec4 Vec4::zyzy()
{

}

Vec4 Vec4::zyzz()
{

}

Vec4 Vec4::zzxx()
{

}

Vec4 Vec4::zzxy()
{

}

Vec4 Vec4::zzxz()
{

}

Vec4 Vec4::zzyx()
{

}

Vec4 Vec4::zzyy()
{

}

Vec4 Vec4::zzyz()
{

}

Vec4 Vec4::zzzx()
{

}

Vec4 Vec4::zzzy()
{

}

Vec4 Vec4::zzzz()
{

}





// Getters & setters
void Vec4::Set(double x, double y, double z, double w)
{
	this->_x = x;
	this->_y = y;
	this->_z = z;
	this->_w = w;
}

double Vec4::x()
{
	return this->_x;
}

double Vec4::y()
{
	return this->_y;
}

double Vec4::z()
{
	return this->_z;
}

double Vec4::w()
{
	return this->_w;
}

void Vec4::x(double x)
{
	this->_x = x;
}

void Vec4::y(double y)
{
	this->_y = y;
}

void Vec4::z(double z)
{
	this->_z = z;
}

void Vec4::w(double w)
{
	this->_w = w;
}