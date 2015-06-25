#include "Vec4.h"
#include <sstream>

Vec4::Vec4() : _x(0), _y(0), _z(0), _w(0) { }

Vec4::Vec4(double x, double y, double z, double w) : _x(w), _y(y), _z(z), _w(w) { }

Vec4::Vec4(Vec3 vec, double w) : _x(vec.x()), _y(vec.y()), _z(vec.z()), _w(w) { }

Vec4::Vec4(Vec2 vec, double z, double w) : _x(vec.x()), _y(vec.y()), _z(z), _w(w) { }

Vec4::Vec4(Vec2 vec1, Vec2 vec2) : _x(vec1.x()), _y(vec1.y()), _z(vec2.x()), _w(vec2.y()) { }

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


double Vec4::Magnitude()
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
	*this /= this->Magnitude();
	return *this;
}

double Vec4::Distance(Vec4 vec)
{
	return (*this - vec).Magnitude();
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
bool Vec4::operator==(Vec4 vec)
{
	return (this->_x == vec.x() && this->_y == vec.y() && this->_z == vec.z() && this->_w == vec.w());
}

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

Vec4 Vec4::operator-()
{
	Vec4 vector;
	vector.Set(-this->_x, -this->_y, -this->_z, -this->_w);
	return vector;
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

double Vec4::operator[](int index)
{
	switch (index)
	{
	case 0:
		return this->_x;
	case 1:
		return this->_y;
	case 2:
		return this->_z;
	default:
		return this->_w;
	}
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

Vec3 Vec4::xxw()
{
	Vec3 vec;
	vec.Set(this->_x, this->_x, this->_w);
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

Vec3 Vec4::xyw()
{
	Vec3 vec;
	vec.Set(this->_x, this->_y, this->_w);
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

Vec3 Vec4::xzw()
{
	Vec3 vec;
	vec.Set(this->_x, this->_z, this->_w);
	return vec;
}

Vec3 Vec4::xwx()
{
	Vec3 vec;
	vec.Set(this->_x, this->_w, this->_x);
	return vec;
}

Vec3 Vec4::xwy()
{
	Vec3 vec;
	vec.Set(this->_x, this->_w, this->_y);
	return vec;
}

Vec3 Vec4::xwz()
{
	Vec3 vec;
	vec.Set(this->_x, this->_w, this->_z);
	return vec;
}

Vec3 Vec4::xww()
{
	Vec3 vec;
	vec.Set(this->_x, this->_w, this->_w);
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

Vec3 Vec4::yxw()
{
	Vec3 vec;
	vec.Set(this->_y, this->_x, this->_w);
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

Vec3 Vec4::yyw()
{
	Vec3 vec;
	vec.Set(this->_y, this->_y, this->_w);
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

Vec3 Vec4::yzw()
{
	Vec3 vec;
	vec.Set(this->_y, this->_z, this->_w);
	return vec;
}

Vec3 Vec4::ywx()
{
	Vec3 vec;
	vec.Set(this->_y, this->_w, this->_x);
	return vec;
}

Vec3 Vec4::ywy()
{
	Vec3 vec;
	vec.Set(this->_y, this->_w, this->_y);
	return vec;
}

Vec3 Vec4::ywz()
{
	Vec3 vec;
	vec.Set(this->_y, this->_w, this->_z);
	return vec;
}

Vec3 Vec4::yww()
{
	Vec3 vec;
	vec.Set(this->_y, this->_w, this->_w);
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

Vec3 Vec4::zxw()
{
	Vec3 vec;
	vec.Set(this->_z, this->_x, this->_w);
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

Vec3 Vec4::zyw()
{
	Vec3 vec;
	vec.Set(this->_z, this->_y, this->_w);
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

Vec3 Vec4::zzw()
{
	Vec3 vec;
	vec.Set(this->_z, this->_z, this->_w);
	return vec;
}

Vec3 Vec4::zwx()
{
	Vec3 vec;
	vec.Set(this->_z, this->_w, this->_x);
	return vec;
}

Vec3 Vec4::zwy()
{
	Vec3 vec;
	vec.Set(this->_z, this->_w, this->_y);
	return vec;
}

Vec3 Vec4::zwz()
{
	Vec3 vec;
	vec.Set(this->_z, this->_w, this->_z);
	return vec;
}

Vec3 Vec4::zww()
{
	Vec3 vec;
	vec.Set(this->_z, this->_w, this->_w);
	return vec;
}

Vec3 Vec4::wxx()
{
	Vec3 vec;
	vec.Set(this->_w, this->_x, this->_x);
	return vec;
}

Vec3 Vec4::wxy()
{
	Vec3 vec;
	vec.Set(this->_w, this->_x, this->_y);
	return vec;
}

Vec3 Vec4::wxz()
{
	Vec3 vec;
	vec.Set(this->_w, this->_x, this->_z);
	return vec;
}

Vec3 Vec4::wxw()
{
	Vec3 vec;
	vec.Set(this->_w, this->_x, this->_w);
	return vec;
}

Vec3 Vec4::wyx()
{
	Vec3 vec;
	vec.Set(this->_w, this->_y, this->_x);
	return vec;
}

Vec3 Vec4::wyy()
{
	Vec3 vec;
	vec.Set(this->_w, this->_y, this->_y);
	return vec;
}

Vec3 Vec4::wyz()
{
	Vec3 vec;
	vec.Set(this->_w, this->_y, this->_z);
	return vec;
}

Vec3 Vec4::wyw()
{
	Vec3 vec;
	vec.Set(this->_w, this->_y, this->_w);
	return vec;
}

Vec3 Vec4::wzx()
{
	Vec3 vec;
	vec.Set(this->_w, this->_z, this->_x);
	return vec;
}

Vec3 Vec4::wzy()
{
	Vec3 vec;
	vec.Set(this->_w, this->_z, this->_y);
	return vec;
}

Vec3 Vec4::wzz()
{
	Vec3 vec;
	vec.Set(this->_w, this->_z, this->_z);
	return vec;
}

Vec3 Vec4::wzw()
{
	Vec3 vec;
	vec.Set(this->_w, this->_z, this->_w);
	return vec;
}

Vec3 Vec4::wwx()
{
	Vec3 vec;
	vec.Set(this->_w, this->_w, this->_x);
	return vec;
}

Vec3 Vec4::wwy()
{
	Vec3 vec;
	vec.Set(this->_w, this->_w, this->_y);
	return vec;
}

Vec3 Vec4::wwz()
{
	Vec3 vec;
	vec.Set(this->_w, this->_w, this->_z);
	return vec;
}

Vec3 Vec4::www()
{
	Vec3 vec;
	vec.Set(this->_w, this->_w, this->_w);
	return vec;
}


Vec4 Vec4::xxxx()
{
	Vec4 vec;
	vec.Set(this->_x, this->_x, this->_x, this->_x);
	return vec;
}

Vec4 Vec4::xxxy()
{
	Vec4 vec;
	vec.Set(this->_x, this->_x, this->_x, this->_y);
	return vec;
}

Vec4 Vec4::xxxz()
{
	Vec4 vec;
	vec.Set(this->_x, this->_x, this->_x, this->_z);
	return vec;
}

Vec4 Vec4::xxxw()
{
	Vec4 vec;
	vec.Set(this->_x, this->_x, this->_x, this->_w);
	return vec;
}

Vec4 Vec4::xxyx()
{
	Vec4 vec;
	vec.Set(this->_x, this->_x, this->_y, this->_x);
	return vec;
}

Vec4 Vec4::xxyy()
{
	Vec4 vec;
	vec.Set(this->_x, this->_x, this->_y, this->_y);
	return vec;
}

Vec4 Vec4::xxyz()
{
	Vec4 vec;
	vec.Set(this->_x, this->_x, this->_y, this->_z);
	return vec;
}

Vec4 Vec4::xxyw()
{
	Vec4 vec;
	vec.Set(this->_x, this->_x, this->_y, this->_w);
	return vec;
}

Vec4 Vec4::xxzx()
{
	Vec4 vec;
	vec.Set(this->_x, this->_x, this->_z, this->_x);
	return vec;
}

Vec4 Vec4::xxzy()
{
	Vec4 vec;
	vec.Set(this->_x, this->_x, this->_z, this->_y);
	return vec;
}

Vec4 Vec4::xxzz()
{
	Vec4 vec;
	vec.Set(this->_x, this->_x, this->_z, this->_z);
	return vec;
}

Vec4 Vec4::xxzw()
{
	Vec4 vec;
	vec.Set(this->_x, this->_x, this->_z, this->_w);
	return vec;
}

Vec4 Vec4::xxwx()
{
	Vec4 vec;
	vec.Set(this->_x, this->_x, this->_w, this->_x);
	return vec;
}

Vec4 Vec4::xxwy()
{
	Vec4 vec;
	vec.Set(this->_x, this->_x, this->_w, this->_y);
	return vec;
}

Vec4 Vec4::xxwz()
{
	Vec4 vec;
	vec.Set(this->_x, this->_x, this->_w, this->_z);
	return vec;
}

Vec4 Vec4::xxww()
{
	Vec4 vec;
	vec.Set(this->_x, this->_x, this->_w, this->_w);
	return vec;
}

Vec4 Vec4::xyxx()
{
	Vec4 vec;
	vec.Set(this->_x, this->_y, this->_x, this->_x);
	return vec;
}

Vec4 Vec4::xyxy()
{
	Vec4 vec;
	vec.Set(this->_x, this->_y, this->_x, this->_y);
	return vec;
}

Vec4 Vec4::xyxz()
{
	Vec4 vec;
	vec.Set(this->_x, this->_y, this->_x, this->_z);
	return vec;
}

Vec4 Vec4::xyxw()
{
	Vec4 vec;
	vec.Set(this->_x, this->_y, this->_x, this->_w);
	return vec;
}

Vec4 Vec4::xyyx()
{
	Vec4 vec;
	vec.Set(this->_x, this->_y, this->_y, this->_x);
	return vec;
}

Vec4 Vec4::xyyy()
{
	Vec4 vec;
	vec.Set(this->_x, this->_y, this->_y, this->_y);
	return vec;
}

Vec4 Vec4::xyyz()
{
	Vec4 vec;
	vec.Set(this->_x, this->_y, this->_y, this->_z);
	return vec;
}

Vec4 Vec4::xyyw()
{
	Vec4 vec;
	vec.Set(this->_x, this->_y, this->_y, this->_w);
	return vec;
}

Vec4 Vec4::xyzx()
{
	Vec4 vec;
	vec.Set(this->_x, this->_y, this->_z, this->_x);
	return vec;
}

Vec4 Vec4::xyzy()
{
	Vec4 vec;
	vec.Set(this->_x, this->_y, this->_z, this->_y);
	return vec;
}

Vec4 Vec4::xyzz()
{
	Vec4 vec;
	vec.Set(this->_x, this->_y, this->_z, this->_z);
	return vec;
}

Vec4 Vec4::xyzw()
{
	Vec4 vec;
	vec.Set(this->_x, this->_y, this->_z, this->_w);
	return vec;
}

Vec4 Vec4::xywx()
{
	Vec4 vec;
	vec.Set(this->_x, this->_y, this->_w, this->_x);
	return vec;
}

Vec4 Vec4::xywy()
{
	Vec4 vec;
	vec.Set(this->_x, this->_y, this->_w, this->_y);
	return vec;
}

Vec4 Vec4::xywz()
{
	Vec4 vec;
	vec.Set(this->_x, this->_y, this->_w, this->_z);
	return vec;
}

Vec4 Vec4::xyww()
{
	Vec4 vec;
	vec.Set(this->_x, this->_y, this->_w, this->_w);
	return vec;
}

Vec4 Vec4::xzxx()
{
	Vec4 vec;
	vec.Set(this->_x, this->_z, this->_x, this->_x);
	return vec;
}

Vec4 Vec4::xzxy()
{
	Vec4 vec;
	vec.Set(this->_x, this->_z, this->_x, this->_y);
	return vec;
}

Vec4 Vec4::xzxz()
{
	Vec4 vec;
	vec.Set(this->_x, this->_z, this->_x, this->_z);
	return vec;
}

Vec4 Vec4::xzxw()
{
	Vec4 vec;
	vec.Set(this->_x, this->_z, this->_x, this->_w);
	return vec;
}

Vec4 Vec4::xzyx()
{
	Vec4 vec;
	vec.Set(this->_x, this->_z, this->_y, this->_x);
	return vec;
}

Vec4 Vec4::xzyy()
{
	Vec4 vec;
	vec.Set(this->_x, this->_z, this->_y, this->_y);
	return vec;
}

Vec4 Vec4::xzyz()
{
	Vec4 vec;
	vec.Set(this->_x, this->_z, this->_y, this->_z);
	return vec;
}

Vec4 Vec4::xzyw()
{
	Vec4 vec;
	vec.Set(this->_x, this->_z, this->_y, this->_w);
	return vec;
}

Vec4 Vec4::xzzx()
{
	Vec4 vec;
	vec.Set(this->_x, this->_z, this->_z, this->_x);
	return vec;
}

Vec4 Vec4::xzzy()
{
	Vec4 vec;
	vec.Set(this->_x, this->_z, this->_z, this->_y);
	return vec;
}

Vec4 Vec4::xzzz()
{
	Vec4 vec;
	vec.Set(this->_x, this->_z, this->_z, this->_z);
	return vec;
}

Vec4 Vec4::xzzw()
{
	Vec4 vec;
	vec.Set(this->_x, this->_z, this->_z, this->_w);
	return vec;
}

Vec4 Vec4::xzwx()
{
	Vec4 vec;
	vec.Set(this->_x, this->_z, this->_w, this->_x);
	return vec;
}

Vec4 Vec4::xzwy()
{
	Vec4 vec;
	vec.Set(this->_x, this->_z, this->_w, this->_y);
	return vec;
}

Vec4 Vec4::xzwz()
{
	Vec4 vec;
	vec.Set(this->_x, this->_z, this->_w, this->_z);
	return vec;
}

Vec4 Vec4::xzww()
{
	Vec4 vec;
	vec.Set(this->_x, this->_z, this->_w, this->_w);
	return vec;
}

Vec4 Vec4::xwxx()
{
	Vec4 vec;
	vec.Set(this->_x, this->_w, this->_x, this->_x);
	return vec;
}

Vec4 Vec4::xwxy()
{
	Vec4 vec;
	vec.Set(this->_x, this->_w, this->_x, this->_y);
	return vec;
}

Vec4 Vec4::xwxz()
{
	Vec4 vec;
	vec.Set(this->_x, this->_w, this->_x, this->_z);
	return vec;
}

Vec4 Vec4::xwxw()
{
	Vec4 vec;
	vec.Set(this->_x, this->_w, this->_x, this->_w);
	return vec;
}

Vec4 Vec4::xwyx()
{
	Vec4 vec;
	vec.Set(this->_x, this->_w, this->_y, this->_x);
	return vec;
}

Vec4 Vec4::xwyy()
{
	Vec4 vec;
	vec.Set(this->_x, this->_w, this->_y, this->_y);
	return vec;
}

Vec4 Vec4::xwyz()
{
	Vec4 vec;
	vec.Set(this->_x, this->_w, this->_y, this->_z);
	return vec;
}

Vec4 Vec4::xwyw()
{
	Vec4 vec;
	vec.Set(this->_x, this->_w, this->_y, this->_w);
	return vec;
}

Vec4 Vec4::xwzx()
{
	Vec4 vec;
	vec.Set(this->_x, this->_w, this->_z, this->_x);
	return vec;
}

Vec4 Vec4::xwzy()
{
	Vec4 vec;
	vec.Set(this->_x, this->_w, this->_z, this->_y);
	return vec;
}

Vec4 Vec4::xwzz()
{
	Vec4 vec;
	vec.Set(this->_x, this->_w, this->_z, this->_z);
	return vec;
}

Vec4 Vec4::xwzw()
{
	Vec4 vec;
	vec.Set(this->_x, this->_w, this->_z, this->_w);
	return vec;
}

Vec4 Vec4::xwwx()
{
	Vec4 vec;
	vec.Set(this->_x, this->_w, this->_w, this->_x);
	return vec;
}

Vec4 Vec4::xwwy()
{
	Vec4 vec;
	vec.Set(this->_x, this->_w, this->_w, this->_y);
	return vec;
}

Vec4 Vec4::xwwz()
{
	Vec4 vec;
	vec.Set(this->_x, this->_w, this->_w, this->_z);
	return vec;
}

Vec4 Vec4::xwww()
{
	Vec4 vec;
	vec.Set(this->_x, this->_w, this->_w, this->_w);
	return vec;
}

Vec4 Vec4::yxxx()
{
	Vec4 vec;
	vec.Set(this->_y, this->_x, this->_x, this->_x);
	return vec;
}

Vec4 Vec4::yxxy()
{
	Vec4 vec;
	vec.Set(this->_y, this->_x, this->_x, this->_y);
	return vec;
}

Vec4 Vec4::yxxz()
{
	Vec4 vec;
	vec.Set(this->_y, this->_x, this->_x, this->_z);
	return vec;
}

Vec4 Vec4::yxxw()
{
	Vec4 vec;
	vec.Set(this->_y, this->_x, this->_x, this->_w);
	return vec;
}

Vec4 Vec4::yxyx()
{
	Vec4 vec;
	vec.Set(this->_y, this->_x, this->_y, this->_x);
	return vec;
}

Vec4 Vec4::yxyy()
{
	Vec4 vec;
	vec.Set(this->_y, this->_x, this->_y, this->_y);
	return vec;
}

Vec4 Vec4::yxyz()
{
	Vec4 vec;
	vec.Set(this->_y, this->_x, this->_y, this->_z);
	return vec;
}

Vec4 Vec4::yxyw()
{
	Vec4 vec;
	vec.Set(this->_y, this->_x, this->_y, this->_w);
	return vec;
}

Vec4 Vec4::yxzx()
{
	Vec4 vec;
	vec.Set(this->_y, this->_x, this->_z, this->_x);
	return vec;
}

Vec4 Vec4::yxzy()
{
	Vec4 vec;
	vec.Set(this->_y, this->_x, this->_z, this->_y);
	return vec;
}

Vec4 Vec4::yxzz()
{
	Vec4 vec;
	vec.Set(this->_y, this->_x, this->_z, this->_z);
	return vec;
}

Vec4 Vec4::yxzw()
{
	Vec4 vec;
	vec.Set(this->_y, this->_x, this->_z, this->_w);
	return vec;
}

Vec4 Vec4::yxwx()
{
	Vec4 vec;
	vec.Set(this->_y, this->_x, this->_w, this->_x);
	return vec;
}

Vec4 Vec4::yxwy()
{
	Vec4 vec;
	vec.Set(this->_y, this->_x, this->_w, this->_y);
	return vec;
}

Vec4 Vec4::yxwz()
{
	Vec4 vec;
	vec.Set(this->_y, this->_x, this->_w, this->_z);
	return vec;
}

Vec4 Vec4::yxww()
{
	Vec4 vec;
	vec.Set(this->_y, this->_x, this->_w, this->_w);
	return vec;
}

Vec4 Vec4::yyxx()
{
	Vec4 vec;
	vec.Set(this->_y, this->_y, this->_x, this->_x);
	return vec;
}

Vec4 Vec4::yyxy()
{
	Vec4 vec;
	vec.Set(this->_y, this->_y, this->_x, this->_y);
	return vec;
}

Vec4 Vec4::yyxz()
{
	Vec4 vec;
	vec.Set(this->_y, this->_y, this->_x, this->_z);
	return vec;
}

Vec4 Vec4::yyxw()
{
	Vec4 vec;
	vec.Set(this->_y, this->_y, this->_x, this->_w);
	return vec;
}

Vec4 Vec4::yyyx()
{
	Vec4 vec;
	vec.Set(this->_y, this->_y, this->_y, this->_x);
	return vec;
}

Vec4 Vec4::yyyy()
{
	Vec4 vec;
	vec.Set(this->_y, this->_y, this->_y, this->_y);
	return vec;
}

Vec4 Vec4::yyyz()
{
	Vec4 vec;
	vec.Set(this->_y, this->_y, this->_y, this->_z);
	return vec;
}

Vec4 Vec4::yyyw()
{
	Vec4 vec;
	vec.Set(this->_y, this->_y, this->_y, this->_w);
	return vec;
}

Vec4 Vec4::yyzx()
{
	Vec4 vec;
	vec.Set(this->_y, this->_y, this->_z, this->_x);
	return vec;
}

Vec4 Vec4::yyzy()
{
	Vec4 vec;
	vec.Set(this->_y, this->_y, this->_z, this->_y);
	return vec;
}

Vec4 Vec4::yyzz()
{
	Vec4 vec;
	vec.Set(this->_y, this->_y, this->_z, this->_z);
	return vec;
}

Vec4 Vec4::yyzw()
{
	Vec4 vec;
	vec.Set(this->_y, this->_y, this->_z, this->_w);
	return vec;
}

Vec4 Vec4::yywx()
{
	Vec4 vec;
	vec.Set(this->_y, this->_y, this->_w, this->_x);
	return vec;
}

Vec4 Vec4::yywy()
{
	Vec4 vec;
	vec.Set(this->_y, this->_y, this->_w, this->_y);
	return vec;
}

Vec4 Vec4::yywz()
{
	Vec4 vec;
	vec.Set(this->_y, this->_y, this->_w, this->_z);
	return vec;
}

Vec4 Vec4::yyww()
{
	Vec4 vec;
	vec.Set(this->_y, this->_y, this->_w, this->_w);
	return vec;
}

Vec4 Vec4::yzxx()
{
	Vec4 vec;
	vec.Set(this->_y, this->_z, this->_x, this->_x);
	return vec;
}

Vec4 Vec4::yzxy()
{
	Vec4 vec;
	vec.Set(this->_y, this->_z, this->_x, this->_y);
	return vec;
}

Vec4 Vec4::yzxz()
{
	Vec4 vec;
	vec.Set(this->_y, this->_z, this->_x, this->_z);
	return vec;
}

Vec4 Vec4::yzxw()
{
	Vec4 vec;
	vec.Set(this->_y, this->_z, this->_x, this->_w);
	return vec;
}

Vec4 Vec4::yzyx()
{
	Vec4 vec;
	vec.Set(this->_y, this->_z, this->_y, this->_x);
	return vec;
}

Vec4 Vec4::yzyy()
{
	Vec4 vec;
	vec.Set(this->_y, this->_z, this->_y, this->_y);
	return vec;
}

Vec4 Vec4::yzyz()
{
	Vec4 vec;
	vec.Set(this->_y, this->_z, this->_y, this->_z);
	return vec;
}

Vec4 Vec4::yzyw()
{
	Vec4 vec;
	vec.Set(this->_y, this->_z, this->_y, this->_w);
	return vec;
}

Vec4 Vec4::yzzx()
{
	Vec4 vec;
	vec.Set(this->_y, this->_z, this->_z, this->_x);
	return vec;
}

Vec4 Vec4::yzzy()
{
	Vec4 vec;
	vec.Set(this->_y, this->_z, this->_z, this->_y);
	return vec;
}

Vec4 Vec4::yzzz()
{
	Vec4 vec;
	vec.Set(this->_y, this->_z, this->_z, this->_z);
	return vec;
}

Vec4 Vec4::yzzw()
{
	Vec4 vec;
	vec.Set(this->_y, this->_z, this->_z, this->_w);
	return vec;
}

Vec4 Vec4::yzwx()
{
	Vec4 vec;
	vec.Set(this->_y, this->_z, this->_w, this->_x);
	return vec;
}

Vec4 Vec4::yzwy()
{
	Vec4 vec;
	vec.Set(this->_y, this->_z, this->_w, this->_y);
	return vec;
}

Vec4 Vec4::yzwz()
{
	Vec4 vec;
	vec.Set(this->_y, this->_z, this->_w, this->_z);
	return vec;
}

Vec4 Vec4::yzww()
{
	Vec4 vec;
	vec.Set(this->_y, this->_z, this->_w, this->_w);
	return vec;
}

Vec4 Vec4::ywxx()
{
	Vec4 vec;
	vec.Set(this->_y, this->_w, this->_x, this->_x);
	return vec;
}

Vec4 Vec4::ywxy()
{
	Vec4 vec;
	vec.Set(this->_y, this->_w, this->_x, this->_y);
	return vec;
}

Vec4 Vec4::ywxz()
{
	Vec4 vec;
	vec.Set(this->_y, this->_w, this->_x, this->_z);
	return vec;
}

Vec4 Vec4::ywxw()
{
	Vec4 vec;
	vec.Set(this->_y, this->_w, this->_x, this->_w);
	return vec;
}

Vec4 Vec4::ywyx()
{
	Vec4 vec;
	vec.Set(this->_y, this->_w, this->_y, this->_x);
	return vec;
}

Vec4 Vec4::ywyy()
{
	Vec4 vec;
	vec.Set(this->_y, this->_w, this->_y, this->_y);
	return vec;
}

Vec4 Vec4::ywyz()
{
	Vec4 vec;
	vec.Set(this->_y, this->_w, this->_y, this->_z);
	return vec;
}

Vec4 Vec4::ywyw()
{
	Vec4 vec;
	vec.Set(this->_y, this->_w, this->_y, this->_w);
	return vec;
}

Vec4 Vec4::ywzx()
{
	Vec4 vec;
	vec.Set(this->_y, this->_w, this->_z, this->_x);
	return vec;
}

Vec4 Vec4::ywzy()
{
	Vec4 vec;
	vec.Set(this->_y, this->_w, this->_z, this->_y);
	return vec;
}

Vec4 Vec4::ywzz()
{
	Vec4 vec;
	vec.Set(this->_y, this->_w, this->_z, this->_z);
	return vec;
}

Vec4 Vec4::ywzw()
{
	Vec4 vec;
	vec.Set(this->_y, this->_w, this->_z, this->_w);
	return vec;
}

Vec4 Vec4::ywwx()
{
	Vec4 vec;
	vec.Set(this->_y, this->_w, this->_w, this->_x);
	return vec;
}

Vec4 Vec4::ywwy()
{
	Vec4 vec;
	vec.Set(this->_y, this->_w, this->_w, this->_y);
	return vec;
}

Vec4 Vec4::ywwz()
{
	Vec4 vec;
	vec.Set(this->_y, this->_w, this->_w, this->_z);
	return vec;
}

Vec4 Vec4::ywww()
{
	Vec4 vec;
	vec.Set(this->_y, this->_w, this->_w, this->_w);
	return vec;
}

Vec4 Vec4::zxxx()
{
	Vec4 vec;
	vec.Set(this->_z, this->_x, this->_x, this->_x);
	return vec;
}

Vec4 Vec4::zxxy()
{
	Vec4 vec;
	vec.Set(this->_z, this->_x, this->_x, this->_y);
	return vec;
}

Vec4 Vec4::zxxz()
{
	Vec4 vec;
	vec.Set(this->_z, this->_x, this->_x, this->_z);
	return vec;
}

Vec4 Vec4::zxxw()
{
	Vec4 vec;
	vec.Set(this->_z, this->_x, this->_x, this->_w);
	return vec;
}

Vec4 Vec4::zxyx()
{
	Vec4 vec;
	vec.Set(this->_z, this->_x, this->_y, this->_x);
	return vec;
}

Vec4 Vec4::zxyy()
{
	Vec4 vec;
	vec.Set(this->_z, this->_x, this->_y, this->_y);
	return vec;
}

Vec4 Vec4::zxyz()
{
	Vec4 vec;
	vec.Set(this->_z, this->_x, this->_y, this->_z);
	return vec;
}

Vec4 Vec4::zxyw()
{
	Vec4 vec;
	vec.Set(this->_z, this->_x, this->_y, this->_w);
	return vec;
}

Vec4 Vec4::zxzx()
{
	Vec4 vec;
	vec.Set(this->_z, this->_x, this->_z, this->_x);
	return vec;
}

Vec4 Vec4::zxzy()
{
	Vec4 vec;
	vec.Set(this->_z, this->_x, this->_z, this->_y);
	return vec;
}

Vec4 Vec4::zxzz()
{
	Vec4 vec;
	vec.Set(this->_z, this->_x, this->_z, this->_z);
	return vec;
}

Vec4 Vec4::zxzw()
{
	Vec4 vec;
	vec.Set(this->_z, this->_x, this->_z, this->_w);
	return vec;
}

Vec4 Vec4::zxwx()
{
	Vec4 vec;
	vec.Set(this->_z, this->_x, this->_w, this->_x);
	return vec;
}

Vec4 Vec4::zxwy()
{
	Vec4 vec;
	vec.Set(this->_z, this->_x, this->_w, this->_y);
	return vec;
}

Vec4 Vec4::zxwz()
{
	Vec4 vec;
	vec.Set(this->_z, this->_x, this->_w, this->_z);
	return vec;
}

Vec4 Vec4::zxww()
{
	Vec4 vec;
	vec.Set(this->_z, this->_x, this->_w, this->_w);
	return vec;
}

Vec4 Vec4::zyxx()
{
	Vec4 vec;
	vec.Set(this->_z, this->_y, this->_x, this->_x);
	return vec;
}

Vec4 Vec4::zyxy()
{
	Vec4 vec;
	vec.Set(this->_z, this->_y, this->_x, this->_y);
	return vec;
}

Vec4 Vec4::zyxz()
{
	Vec4 vec;
	vec.Set(this->_z, this->_y, this->_x, this->_z);
	return vec;
}

Vec4 Vec4::zyxw()
{
	Vec4 vec;
	vec.Set(this->_z, this->_y, this->_x, this->_w);
	return vec;
}

Vec4 Vec4::zyyx()
{
	Vec4 vec;
	vec.Set(this->_z, this->_y, this->_y, this->_x);
	return vec;
}

Vec4 Vec4::zyyy()
{
	Vec4 vec;
	vec.Set(this->_z, this->_y, this->_y, this->_y);
	return vec;
}

Vec4 Vec4::zyyz()
{
	Vec4 vec;
	vec.Set(this->_z, this->_y, this->_y, this->_z);
	return vec;
}

Vec4 Vec4::zyyw()
{
	Vec4 vec;
	vec.Set(this->_z, this->_y, this->_y, this->_w);
	return vec;
}

Vec4 Vec4::zyzx()
{
	Vec4 vec;
	vec.Set(this->_z, this->_y, this->_z, this->_x);
	return vec;
}

Vec4 Vec4::zyzy()
{
	Vec4 vec;
	vec.Set(this->_z, this->_y, this->_z, this->_y);
	return vec;
}

Vec4 Vec4::zyzz()
{
	Vec4 vec;
	vec.Set(this->_z, this->_y, this->_z, this->_z);
	return vec;
}

Vec4 Vec4::zyzw()
{
	Vec4 vec;
	vec.Set(this->_z, this->_y, this->_z, this->_w);
	return vec;
}

Vec4 Vec4::zywx()
{
	Vec4 vec;
	vec.Set(this->_z, this->_y, this->_w, this->_x);
	return vec;
}

Vec4 Vec4::zywy()
{
	Vec4 vec;
	vec.Set(this->_z, this->_y, this->_w, this->_y);
	return vec;
}

Vec4 Vec4::zywz()
{
	Vec4 vec;
	vec.Set(this->_z, this->_y, this->_w, this->_z);
	return vec;
}

Vec4 Vec4::zyww()
{
	Vec4 vec;
	vec.Set(this->_z, this->_y, this->_w, this->_w);
	return vec;
}

Vec4 Vec4::zzxx()
{
	Vec4 vec;
	vec.Set(this->_z, this->_z, this->_x, this->_x);
	return vec;
}

Vec4 Vec4::zzxy()
{
	Vec4 vec;
	vec.Set(this->_z, this->_z, this->_x, this->_y);
	return vec;
}

Vec4 Vec4::zzxz()
{
	Vec4 vec;
	vec.Set(this->_z, this->_z, this->_x, this->_z);
	return vec;
}

Vec4 Vec4::zzxw()
{
	Vec4 vec;
	vec.Set(this->_z, this->_z, this->_x, this->_w);
	return vec;
}

Vec4 Vec4::zzyx()
{
	Vec4 vec;
	vec.Set(this->_z, this->_z, this->_y, this->_x);
	return vec;
}

Vec4 Vec4::zzyy()
{
	Vec4 vec;
	vec.Set(this->_z, this->_z, this->_y, this->_y);
	return vec;
}

Vec4 Vec4::zzyz()
{
	Vec4 vec;
	vec.Set(this->_z, this->_z, this->_y, this->_z);
	return vec;
}

Vec4 Vec4::zzyw()
{
	Vec4 vec;
	vec.Set(this->_z, this->_z, this->_y, this->_w);
	return vec;
}

Vec4 Vec4::zzzx()
{
	Vec4 vec;
	vec.Set(this->_z, this->_z, this->_z, this->_x);
	return vec;
}

Vec4 Vec4::zzzy()
{
	Vec4 vec;
	vec.Set(this->_z, this->_z, this->_z, this->_y);
	return vec;
}

Vec4 Vec4::zzzz()
{
	Vec4 vec;
	vec.Set(this->_z, this->_z, this->_z, this->_z);
	return vec;
}

Vec4 Vec4::zzzw()
{
	Vec4 vec;
	vec.Set(this->_z, this->_z, this->_z, this->_w);
	return vec;
}

Vec4 Vec4::zzwx()
{
	Vec4 vec;
	vec.Set(this->_z, this->_z, this->_w, this->_x);
	return vec;
}

Vec4 Vec4::zzwy()
{
	Vec4 vec;
	vec.Set(this->_z, this->_z, this->_w, this->_y);
	return vec;
}

Vec4 Vec4::zzwz()
{
	Vec4 vec;
	vec.Set(this->_z, this->_z, this->_w, this->_z);
	return vec;
}

Vec4 Vec4::zzww()
{
	Vec4 vec;
	vec.Set(this->_z, this->_z, this->_w, this->_w);
	return vec;
}

Vec4 Vec4::zwxx()
{
	Vec4 vec;
	vec.Set(this->_z, this->_w, this->_x, this->_x);
	return vec;
}

Vec4 Vec4::zwxy()
{
	Vec4 vec;
	vec.Set(this->_z, this->_w, this->_x, this->_y);
	return vec;
}

Vec4 Vec4::zwxz()
{
	Vec4 vec;
	vec.Set(this->_z, this->_w, this->_x, this->_z);
	return vec;
}

Vec4 Vec4::zwxw()
{
	Vec4 vec;
	vec.Set(this->_z, this->_w, this->_x, this->_w);
	return vec;
}

Vec4 Vec4::zwyx()
{
	Vec4 vec;
	vec.Set(this->_z, this->_w, this->_y, this->_x);
	return vec;
}

Vec4 Vec4::zwyy()
{
	Vec4 vec;
	vec.Set(this->_z, this->_w, this->_y, this->_y);
	return vec;
}

Vec4 Vec4::zwyz()
{
	Vec4 vec;
	vec.Set(this->_z, this->_w, this->_y, this->_z);
	return vec;
}

Vec4 Vec4::zwyw()
{
	Vec4 vec;
	vec.Set(this->_z, this->_w, this->_y, this->_w);
	return vec;
}

Vec4 Vec4::zwzx()
{
	Vec4 vec;
	vec.Set(this->_z, this->_w, this->_z, this->_x);
	return vec;
}

Vec4 Vec4::zwzy()
{
	Vec4 vec;
	vec.Set(this->_z, this->_w, this->_z, this->_y);
	return vec;
}

Vec4 Vec4::zwzz()
{
	Vec4 vec;
	vec.Set(this->_z, this->_w, this->_z, this->_z);
	return vec;
}

Vec4 Vec4::zwzw()
{
	Vec4 vec;
	vec.Set(this->_z, this->_w, this->_z, this->_w);
	return vec;
}

Vec4 Vec4::zwwx()
{
	Vec4 vec;
	vec.Set(this->_z, this->_w, this->_w, this->_x);
	return vec;
}

Vec4 Vec4::zwwy()
{
	Vec4 vec;
	vec.Set(this->_z, this->_w, this->_w, this->_y);
	return vec;
}

Vec4 Vec4::zwwz()
{
	Vec4 vec;
	vec.Set(this->_z, this->_w, this->_w, this->_z);
	return vec;
}

Vec4 Vec4::zwww()
{
	Vec4 vec;
	vec.Set(this->_z, this->_w, this->_w, this->_w);
	return vec;
}

Vec4 Vec4::wxxx()
{
	Vec4 vec;
	vec.Set(this->_w, this->_x, this->_x, this->_x);
	return vec;
}

Vec4 Vec4::wxxy()
{
	Vec4 vec;
	vec.Set(this->_w, this->_x, this->_x, this->_y);
	return vec;
}

Vec4 Vec4::wxxz()
{
	Vec4 vec;
	vec.Set(this->_w, this->_x, this->_x, this->_z);
	return vec;
}

Vec4 Vec4::wxxw()
{
	Vec4 vec;
	vec.Set(this->_w, this->_x, this->_x, this->_w);
	return vec;
}

Vec4 Vec4::wxyx()
{
	Vec4 vec;
	vec.Set(this->_w, this->_x, this->_y, this->_x);
	return vec;
}

Vec4 Vec4::wxyy()
{
	Vec4 vec;
	vec.Set(this->_w, this->_x, this->_y, this->_y);
	return vec;
}

Vec4 Vec4::wxyz()
{
	Vec4 vec;
	vec.Set(this->_w, this->_x, this->_y, this->_z);
	return vec;
}

Vec4 Vec4::wxyw()
{
	Vec4 vec;
	vec.Set(this->_w, this->_x, this->_y, this->_w);
	return vec;
}

Vec4 Vec4::wxzx()
{
	Vec4 vec;
	vec.Set(this->_w, this->_x, this->_z, this->_x);
	return vec;
}

Vec4 Vec4::wxzy()
{
	Vec4 vec;
	vec.Set(this->_w, this->_x, this->_z, this->_y);
	return vec;
}

Vec4 Vec4::wxzz()
{
	Vec4 vec;
	vec.Set(this->_w, this->_x, this->_z, this->_z);
	return vec;
}

Vec4 Vec4::wxzw()
{
	Vec4 vec;
	vec.Set(this->_w, this->_x, this->_z, this->_w);
	return vec;
}

Vec4 Vec4::wxwx()
{
	Vec4 vec;
	vec.Set(this->_w, this->_x, this->_w, this->_x);
	return vec;
}

Vec4 Vec4::wxwy()
{
	Vec4 vec;
	vec.Set(this->_w, this->_x, this->_w, this->_y);
	return vec;
}

Vec4 Vec4::wxwz()
{
	Vec4 vec;
	vec.Set(this->_w, this->_x, this->_w, this->_z);
	return vec;
}

Vec4 Vec4::wxww()
{
	Vec4 vec;
	vec.Set(this->_w, this->_x, this->_w, this->_w);
	return vec;
}

Vec4 Vec4::wyxx()
{
	Vec4 vec;
	vec.Set(this->_w, this->_y, this->_x, this->_x);
	return vec;
}

Vec4 Vec4::wyxy()
{
	Vec4 vec;
	vec.Set(this->_w, this->_y, this->_x, this->_y);
	return vec;
}

Vec4 Vec4::wyxz()
{
	Vec4 vec;
	vec.Set(this->_w, this->_y, this->_x, this->_z);
	return vec;
}

Vec4 Vec4::wyxw()
{
	Vec4 vec;
	vec.Set(this->_w, this->_y, this->_x, this->_w);
	return vec;
}

Vec4 Vec4::wyyx()
{
	Vec4 vec;
	vec.Set(this->_w, this->_y, this->_y, this->_x);
	return vec;
}

Vec4 Vec4::wyyy()
{
	Vec4 vec;
	vec.Set(this->_w, this->_y, this->_y, this->_y);
	return vec;
}

Vec4 Vec4::wyyz()
{
	Vec4 vec;
	vec.Set(this->_w, this->_y, this->_y, this->_z);
	return vec;
}

Vec4 Vec4::wyyw()
{
	Vec4 vec;
	vec.Set(this->_w, this->_y, this->_y, this->_w);
	return vec;
}

Vec4 Vec4::wyzx()
{
	Vec4 vec;
	vec.Set(this->_w, this->_y, this->_z, this->_x);
	return vec;
}

Vec4 Vec4::wyzy()
{
	Vec4 vec;
	vec.Set(this->_w, this->_y, this->_z, this->_y);
	return vec;
}

Vec4 Vec4::wyzz()
{
	Vec4 vec;
	vec.Set(this->_w, this->_y, this->_z, this->_z);
	return vec;
}

Vec4 Vec4::wyzw()
{
	Vec4 vec;
	vec.Set(this->_w, this->_y, this->_z, this->_w);
	return vec;
}

Vec4 Vec4::wywx()
{
	Vec4 vec;
	vec.Set(this->_w, this->_y, this->_w, this->_x);
	return vec;
}

Vec4 Vec4::wywy()
{
	Vec4 vec;
	vec.Set(this->_w, this->_y, this->_w, this->_y);
	return vec;
}

Vec4 Vec4::wywz()
{
	Vec4 vec;
	vec.Set(this->_w, this->_y, this->_w, this->_z);
	return vec;
}

Vec4 Vec4::wyww()
{
	Vec4 vec;
	vec.Set(this->_w, this->_y, this->_w, this->_w);
	return vec;
}

Vec4 Vec4::wzxx()
{
	Vec4 vec;
	vec.Set(this->_w, this->_z, this->_x, this->_x);
	return vec;
}

Vec4 Vec4::wzxy()
{
	Vec4 vec;
	vec.Set(this->_w, this->_z, this->_x, this->_y);
	return vec;
}

Vec4 Vec4::wzxz()
{
	Vec4 vec;
	vec.Set(this->_w, this->_z, this->_x, this->_z);
	return vec;
}

Vec4 Vec4::wzxw()
{
	Vec4 vec;
	vec.Set(this->_w, this->_z, this->_x, this->_w);
	return vec;
}

Vec4 Vec4::wzyx()
{
	Vec4 vec;
	vec.Set(this->_w, this->_z, this->_y, this->_x);
	return vec;
}

Vec4 Vec4::wzyy()
{
	Vec4 vec;
	vec.Set(this->_w, this->_z, this->_y, this->_y);
	return vec;
}

Vec4 Vec4::wzyz()
{
	Vec4 vec;
	vec.Set(this->_w, this->_z, this->_y, this->_z);
	return vec;
}

Vec4 Vec4::wzyw()
{
	Vec4 vec;
	vec.Set(this->_w, this->_z, this->_y, this->_w);
	return vec;
}

Vec4 Vec4::wzzx()
{
	Vec4 vec;
	vec.Set(this->_w, this->_z, this->_z, this->_x);
	return vec;
}

Vec4 Vec4::wzzy()
{
	Vec4 vec;
	vec.Set(this->_w, this->_z, this->_z, this->_y);
	return vec;
}

Vec4 Vec4::wzzz()
{
	Vec4 vec;
	vec.Set(this->_w, this->_z, this->_z, this->_z);
	return vec;
}

Vec4 Vec4::wzzw()
{
	Vec4 vec;
	vec.Set(this->_w, this->_z, this->_z, this->_w);
	return vec;
}

Vec4 Vec4::wzwx()
{
	Vec4 vec;
	vec.Set(this->_w, this->_z, this->_w, this->_x);
	return vec;
}

Vec4 Vec4::wzwy()
{
	Vec4 vec;
	vec.Set(this->_w, this->_z, this->_w, this->_y);
	return vec;
}

Vec4 Vec4::wzwz()
{
	Vec4 vec;
	vec.Set(this->_w, this->_z, this->_w, this->_z);
	return vec;
}

Vec4 Vec4::wzww()
{
	Vec4 vec;
	vec.Set(this->_w, this->_z, this->_w, this->_w);
	return vec;
}

Vec4 Vec4::wwxx()
{
	Vec4 vec;
	vec.Set(this->_w, this->_w, this->_x, this->_x);
	return vec;
}

Vec4 Vec4::wwxy()
{
	Vec4 vec;
	vec.Set(this->_w, this->_w, this->_x, this->_y);
	return vec;
}

Vec4 Vec4::wwxz()
{
	Vec4 vec;
	vec.Set(this->_w, this->_w, this->_x, this->_z);
	return vec;
}

Vec4 Vec4::wwxw()
{
	Vec4 vec;
	vec.Set(this->_w, this->_w, this->_x, this->_w);
	return vec;
}

Vec4 Vec4::wwyx()
{
	Vec4 vec;
	vec.Set(this->_w, this->_w, this->_y, this->_x);
	return vec;
}

Vec4 Vec4::wwyy()
{
	Vec4 vec;
	vec.Set(this->_w, this->_w, this->_y, this->_y);
	return vec;
}

Vec4 Vec4::wwyz()
{
	Vec4 vec;
	vec.Set(this->_w, this->_w, this->_y, this->_z);
	return vec;
}

Vec4 Vec4::wwyw()
{
	Vec4 vec;
	vec.Set(this->_w, this->_w, this->_y, this->_w);
	return vec;
}

Vec4 Vec4::wwzx()
{
	Vec4 vec;
	vec.Set(this->_w, this->_w, this->_z, this->_x);
	return vec;
}

Vec4 Vec4::wwzy()
{
	Vec4 vec;
	vec.Set(this->_w, this->_w, this->_z, this->_y);
	return vec;
}

Vec4 Vec4::wwzz()
{
	Vec4 vec;
	vec.Set(this->_w, this->_w, this->_z, this->_z);
	return vec;
}

Vec4 Vec4::wwzw()
{
	Vec4 vec;
	vec.Set(this->_w, this->_w, this->_z, this->_w);
	return vec;
}

Vec4 Vec4::wwwx()
{
	Vec4 vec;
	vec.Set(this->_w, this->_w, this->_w, this->_x);
	return vec;
}

Vec4 Vec4::wwwy()
{
	Vec4 vec;
	vec.Set(this->_w, this->_w, this->_w, this->_y);
	return vec;
}

Vec4 Vec4::wwwz()
{
	Vec4 vec;
	vec.Set(this->_w, this->_w, this->_w, this->_z);
	return vec;
}

Vec4 Vec4::wwww()
{
	Vec4 vec;
	vec.Set(this->_w, this->_w, this->_w, this->_w);
	return vec;
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