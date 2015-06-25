#ifndef VEC4_H
#define VEC4_H
#include <iostream>
#include "Vec2.h"
#include "Vec3.h"

class Vec4
{
public:
	Vec4();
	Vec4(double x, double y, double z, double w);
	virtual ~Vec4();

	// Static methods
	static Vec4 Up();
	static Vec4 Down();
	static Vec4 Left();
	static Vec4 Right();
	static Vec4 Forward();
	static Vec4 Backward();

	double Length();
	double Dot(Vec4 vec);
	Vec3 Cross(Vec4 vec);
	Vec4 Normalize();
	std::string ToString();

	// Operator Overloads
	Vec4 operator+(Vec4 vec);
	Vec4 operator+(double scalar);
	Vec4& operator+=(Vec4 vec);
	Vec4& operator+=(double scalar);
	Vec4 operator-(Vec4 vec);
	Vec4 operator-(double scalar);
	Vec4& operator-=(Vec4 vec);
	Vec4& operator-=(double scalar);
	Vec4 operator*(Vec4 vec);
	Vec4 operator*(double scalar);
	Vec4& operator*=(Vec4 vec);
	Vec4& operator*=(double scalar);
	Vec4 operator/(Vec4 vec);
	Vec4 operator/(double scalar);
	Vec4& operator/=(Vec4 vec);
	Vec4& operator/=(double scalar);

	// Swizzling
	Vec2 xx();
	Vec2 xy();
	Vec2 xz();
	Vec2 xw();
	Vec2 yx();
	Vec2 yy();
	Vec2 yz();
	Vec2 yw();
	Vec2 zx();
	Vec2 zy();
	Vec2 zz();
	Vec2 zw();
	Vec2 wx();
	Vec2 wy();
	Vec2 wz();
	Vec2 ww();
	Vec3 xxx();
	Vec3 xxy();
	Vec3 xxz();
	Vec3 xxw();
	Vec3 xyx();
	Vec3 xyy();
	Vec3 xyz();
	Vec3 xyw();
	Vec3 xzx();
	Vec3 xzy();
	Vec3 xzz();
	Vec3 xzw();
	Vec3 xwx();
	Vec3 xwy();
	Vec3 xwz();
	Vec3 xww();
	Vec3 yxx();
	Vec3 yxy();
	Vec3 yxz();
	Vec3 yxw();
	Vec3 yyx();
	Vec3 yyy();
	Vec3 yyz();
	Vec3 yyw();
	Vec3 yzx();
	Vec3 yzy();
	Vec3 yzz();
	Vec3 yzw();
	Vec3 ywx();
	Vec3 ywy();
	Vec3 ywz();
	Vec3 yww();
	Vec3 zxx();
	Vec3 zxy();
	Vec3 zxz();
	Vec3 zxw();
	Vec3 zyx();
	Vec3 zyy();
	Vec3 zyz();
	Vec3 zyw();
	Vec3 zzx();
	Vec3 zzy();
	Vec3 zzz();
	Vec3 zzw();
	Vec3 zwx();
	Vec3 zwy();
	Vec3 zwz();
	Vec3 zww();
	Vec3 wxx();
	Vec3 wxy();
	Vec3 wxz();
	Vec3 wxw();
	Vec3 wyx();
	Vec3 wyy();
	Vec3 wyz();
	Vec3 wyw();
	Vec3 wzx();
	Vec3 wzy();
	Vec3 wzz();
	Vec3 wzw();
	Vec3 wwx();
	Vec3 wwy();
	Vec3 wwz();
	Vec3 www();




	Vec4 xxxx();
	Vec4 xxxy();
	Vec4 xxxz();
	Vec4 xxxw();
	Vec4 xxyx();
	Vec4 xxyy();
	Vec4 xxyz();
	Vec4 xxyw();
	Vec4 xxzx();
	Vec4 xxzy();
	Vec4 xxzz();
	Vec4 xxzw();
	Vec4 xxwx();
	Vec4 xxwy();
	Vec4 xxwz();
	Vec4 xxww();

	Vec4 xyxx();
	Vec4 xyxy();
	Vec4 xyxz();
	Vec4 xyxw();
	Vec4 xyyx();
	Vec4 xyyy();
	Vec4 xyyz();
	Vec4 xyyw();
	Vec4 xyzx();
	Vec4 xyzy();
	Vec4 xyzz();
	Vec4 xyzw();
	Vec4 xywx();
	Vec4 xywy();
	Vec4 xywz();
	Vec4 xyww();

	Vec4 xzxx();
	Vec4 xzxy();
	Vec4 xzxz();
	Vec4 xzxw();
	Vec4 xzyx();
	Vec4 xzyy();
	Vec4 xzyz();
	Vec4 xzyw();
	Vec4 xzzx();
	Vec4 xzzy();
	Vec4 xzzz();
	Vec4 xzzw();
	Vec4 xzwx();
	Vec4 xzwy();
	Vec4 xzwz();
	Vec4 xzww();

	Vec4 xwxx();
	Vec4 xwxy();
	Vec4 xwxz();
	Vec4 xwxw();
	Vec4 xwyx();
	Vec4 xwyy();
	Vec4 xwyz();
	Vec4 xwyw();
	Vec4 xwzx();
	Vec4 xwzy();
	Vec4 xwzz();
	Vec4 xwzw();
	Vec4 xwwx();
	Vec4 xwwy();
	Vec4 xwwz();
	Vec4 xwww();


	Vec4 yxxx();
	Vec4 yxxy();
	Vec4 yxxz();
	Vec4 yxxw();
	Vec4 yxyx();
	Vec4 yxyy();
	Vec4 yxyz();
	Vec4 yxyw();
	Vec4 yxzx();
	Vec4 yxzy();
	Vec4 yxzz();
	Vec4 yxzw();
	Vec4 yxwx();
	Vec4 yxwy();
	Vec4 yxwz();
	Vec4 yxww();

	Vec4 yyxx();
	Vec4 yyxy();
	Vec4 yyxz();
	Vec4 yyxw();
	Vec4 yyyx();
	Vec4 yyyy();
	Vec4 yyyz();
	Vec4 yyyw();
	Vec4 yyzx();
	Vec4 yyzy();
	Vec4 yyzz();
	Vec4 yyzw();
	Vec4 yywx();
	Vec4 yywy();
	Vec4 yywz();
	Vec4 yyww();

	Vec4 yzxx();
	Vec4 yzxy();
	Vec4 yzxz();
	Vec4 yzxw();
	Vec4 yzyx();
	Vec4 yzyy();
	Vec4 yzyz();
	Vec4 yzyw();
	Vec4 yzzx();
	Vec4 yzzy();
	Vec4 yzzz();
	Vec4 yzzw();
	Vec4 yzwx();
	Vec4 yzwy();
	Vec4 yzwz();
	Vec4 yzww();


	Vec4 ywxx();
	Vec4 ywxy();
	Vec4 ywxz();
	Vec4 ywxw();
	Vec4 ywyx();
	Vec4 ywyy();
	Vec4 ywyz();
	Vec4 ywyw();
	Vec4 ywzx();
	Vec4 ywzy();
	Vec4 ywzz();
	Vec4 ywzw();
	Vec4 ywwx();
	Vec4 ywwy();
	Vec4 ywwz();
	Vec4 ywww();


	Vec4 zxxx();
	Vec4 zxxy();
	Vec4 zxxz();
	Vec4 zxxw();
	Vec4 zxyx();
	Vec4 zxyy();
	Vec4 zxyz();
	Vec4 zxyw();
	Vec4 zxzx();
	Vec4 zxzy();
	Vec4 zxzz();
	Vec4 zxzw();
	Vec4 zxwx();
	Vec4 zxwy();
	Vec4 zxwz();
	Vec4 zxww();

	Vec4 zyxx();
	Vec4 zyxy();
	Vec4 zyxz();
	Vec4 zyxw();
	Vec4 zyyx();
	Vec4 zyyy();
	Vec4 zyyz();
	Vec4 zyyw();
	Vec4 zyzx();
	Vec4 zyzy();
	Vec4 zyzz();
	Vec4 zyzw();
	Vec4 zywx();
	Vec4 zywy();
	Vec4 zywz();
	Vec4 zyww();

	Vec4 zzxx();
	Vec4 zzxy();
	Vec4 zzxz();
	Vec4 zzxw();
	Vec4 zzyx();
	Vec4 zzyy();
	Vec4 zzyz();
	Vec4 zzyw();
	Vec4 zzzx();
	Vec4 zzzy();
	Vec4 zzzz();
	Vec4 zzzw();
	Vec4 zzwx();
	Vec4 zzwy();
	Vec4 zzwz();
	Vec4 zzww();

	Vec4 zwxx();
	Vec4 zwxy();
	Vec4 zwxz();
	Vec4 zwxw();
	Vec4 zwyx();
	Vec4 zwyy();
	Vec4 zwyz();
	Vec4 zwyw();
	Vec4 zwzx();
	Vec4 zwzy();
	Vec4 zwzz();
	Vec4 zwzw();
	Vec4 zwwx();
	Vec4 zwwy();
	Vec4 zwwz();
	Vec4 zwww();

	Vec4 wxxx();
	Vec4 wxxy();
	Vec4 wxxz();
	Vec4 wxxw();
	Vec4 wxyx();
	Vec4 wxyy();
	Vec4 wxyz();
	Vec4 wxyw();
	Vec4 wxzx();
	Vec4 wxzy();
	Vec4 wxzz();
	Vec4 wxzw();
	Vec4 wxwx();
	Vec4 wxwy();
	Vec4 wxwz();
	Vec4 wxww();
	Vec4 wyxx();
	Vec4 wyxy();
	Vec4 wyxz();
	Vec4 wyxw();
	Vec4 wyyx();
	Vec4 wyyy();
	Vec4 wyyz();
	Vec4 wyyw();
	Vec4 wyzx();
	Vec4 wyzy();
	Vec4 wyzz();
	Vec4 wyzw();
	Vec4 wywx();
	Vec4 wywy();
	Vec4 wywz();
	Vec4 wyww();
	Vec4 wzxx();
	Vec4 wzxy();
	Vec4 wzxz();
	Vec4 wzxw();
	Vec4 wzyx();
	Vec4 wzyy();
	Vec4 wzyz();
	Vec4 wzyw();
	Vec4 wzzx();
	Vec4 wzzy();
	Vec4 wzzz();
	Vec4 wzzw();
	Vec4 wzwx();
	Vec4 wzwy();
	Vec4 wzwz();
	Vec4 wzww();
	Vec4 wwxx();
	Vec4 wwxy();
	Vec4 wwxz();
	Vec4 wwxw();
	Vec4 wwyx();
	Vec4 wwyy();
	Vec4 wwyz();
	Vec4 wwyw();
	Vec4 wwzx();
	Vec4 wwzz();
	Vec4 wwzx();
	Vec4 wwzy();
	Vec4 wwzz();
	Vec4 wwzw();
	Vec4 wwwx();
	Vec4 wwwy();
	Vec4 wwwz();
	Vec4 wwww();



	// Getters & setters
	double x();
	double y();
	double z();
	double w();

	void Set(double x, double y, double z, double w);
	void x(double x);
	void y(double y);
	void z(double z);
	void w(double w);

private:
	double _x;
	double _y;
	double _z;
	double _w;
};

#endif