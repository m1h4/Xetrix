#include "Globals.h"
#include "Vector.h"
#include "Interpolations.h"
#include "Matrix.h"

float Vector2::GetLength(void) const
{
	return sqrtf(x*x+y*y);
}

float Vector2::Normalize(void)
{
	float length = GetLength();

	if(length == 0.0f)
		return 0.0f;
	
	x /= length;
	y /= length;

	return length;
}

void Vector2::LinearInterp(const Vector2& dest,float s)
{
	x = LinearInterpolation(x,dest.x,s);
	y = LinearInterpolation(y,dest.y,s);
}

void Vector2::CubicInterp(const Vector2& dest,float s)
{
	x = CubicInterpolation(x,dest.x,s);
	y = CubicInterpolation(y,dest.y,s);
}

void Vector2::CosInterp(const Vector2& dest,float s)
{
	x = CosineInterpolation(x,dest.x,s);
	y = CosineInterpolation(y,dest.y,s);
}

Vector2 Vector2::operator * (const Matrix2& other) const
{
	Vector2 vec(x,y);

	other.Transform(&vec);
	
	return vec;
}

Vector2 Vector2::operator ^ (const Matrix2& other) const
{
	Vector2 vec(x,y);

	other.TransformTransposed(&vec);
	
	return vec;
}

//Vector2 Vector2::operator * (const Matrix4& other) const
//{
//	Vector2 vec(x,y);
//
//	other.Transform(&vec);
//	
//	return vec;
//}

Vector2& Vector2::operator *= (const Matrix2& other)
{
	other.Transform(this); return *this;
}

Vector2& Vector2::operator ^= (const Matrix2& other)
{
	other.TransformTransposed(this); return *this;
}

//Vector2& Vector2::operator *= (const Matrix4& other)
//{
//	other.Transform(this); return *this;
//}

float Vector3::GetLength(void) const
{
	return sqrtf(x*x+y*y+z*z);
}

float Vector3::GetLengthSqr(void) const
{
	return x*x+y*y+z*z;
}

float Vector3::Normalize(void)
{
	float length = this->GetLength();

	if(length == 0.0f)
		return 0.0f;
	
	x /= length;
	y /= length;
	z /= length;

	return length;
}

void Vector3::LinearInterp(const Vector3& dest,float s)
{
	x = LinearInterpolation(x,dest.x,s);
	y = LinearInterpolation(y,dest.y,s);
	z = LinearInterpolation(z,dest.z,s);
}

void Vector3::CubicInterp(const Vector3& dest,float s)
{
	x = CubicInterpolation(x,dest.x,s);
	y = CubicInterpolation(y,dest.y,s);
	z = CubicInterpolation(z,dest.z,s);
}

void Vector3::CosInterp(const Vector3& dest,float s)
{
	x = CosineInterpolation(x,dest.x,s);
	y = CosineInterpolation(y,dest.y,s);
	z = CosineInterpolation(z,dest.z,s);
}

Vector3 Vector3::operator * (const Matrix4& other) const
{
	Vector3 vec(x,y,z);

	other.Transform(&vec);
	
	return vec;
}

Vector3& Vector3::operator *= (const Matrix4& other)
{
	other.Transform(this);
	
	return *this;
}

void Vector4::SetEmpty(void)
{
	x = y = z = w = 0.0f;
}

bool Vector4::Empty(void) const
{
	return x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f;
}

float Vector4::Length(void) const
{
	return sqrtf(x*x+y*y+z*z+w*w);
}

float Vector4::LengthSqr(void) const
{
	return x*x+y*y+z*z+w*w;
}

float Vector4::Normalize(void)
{
	float l = this->Length();

	if(l == 0.0f)
		return 0.0f;
	
	x /= l;
	y /= l;
	z /= l;
	w /= l;

	return l;
}

bool Vector4::Normalized(void) const
{
	return Length() == 1.0f;
}

void Vector4::LinearInterp(const Vector4& dest,float s)
{
	x = LinearInterpolation(x,dest.x,s);
	y = LinearInterpolation(y,dest.y,s);
	z = LinearInterpolation(z,dest.z,s);
	w = LinearInterpolation(w,dest.w,s);
}

void Vector4::CubicInterp(const Vector4& dest,float s)
{
	x = CubicInterpolation(x,dest.x,s);
	y = CubicInterpolation(y,dest.y,s);
	z = CubicInterpolation(z,dest.z,s);
	w = CubicInterpolation(w,dest.w,s);
}

void Vector4::CosInterp(const Vector4& dest,float s)
{
	x = CosineInterpolation(x,dest.x,s);
	y = CosineInterpolation(y,dest.y,s);
	z = CosineInterpolation(z,dest.z,s);
	w = CosineInterpolation(w,dest.w,s);
}

Vector4 Vector4::operator + (const Vector4& other) const
{
	return Vector4(x+other.x,y+other.y,z+other.z,w+other.w);
}

Vector4 Vector4::operator - (const Vector4& other) const
{
	return Vector4(x-other.x,y-other.y,z-other.z,w-other.w);
}

float Vector4::operator * (const Vector4& other) const
{
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

Vector4 Vector4::operator / (const Vector4& other) const
{
	return Vector4(x/other.x,y/other.y,z/other.z,w/other.w);
}

Vector4 Vector4::operator * (const Matrix4& other) const
{
	Vector4 vec(x,y,z,w);

	other.Transform(&vec);

	return vec;
}

Vector4 Vector4::operator + (float scalar) const
{
	return Vector4(x+scalar,y+scalar,z+scalar,w+scalar);
}

Vector4 Vector4::operator - (float scalar) const
{
	return Vector4(x-scalar,y-scalar,z-scalar,w-scalar);
}

Vector4 Vector4::operator * (float scalar) const
{
	return Vector4(x*scalar,y*scalar,z*scalar,w*scalar);
}

Vector4 Vector4::operator / (float scalar) const
{
	return Vector4(x/scalar,y/scalar,z/scalar,w/scalar);
}

Vector4& Vector4::operator += (const Vector4& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	
	return *this;
}

Vector4& Vector4::operator -= (const Vector4& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	
	return *this;
}

Vector4& Vector4::operator /= (const Vector4& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;
	
	return *this;
}

Vector4& Vector4::operator *= (const Matrix4& other)
{
	other.Transform(this);
	
	return *this;
}

Vector4& Vector4::operator += (float scalar)
{
	x += scalar;
	y += scalar;
	z += scalar;
	w += scalar;
	
	return *this;
}

Vector4& Vector4::operator -= (float scalar)
{
	x -= scalar;
	y -= scalar;
	z -= scalar;
	w -= scalar;
	
	return *this;
}

Vector4& Vector4::operator *= (float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	
	return *this;
}

Vector4& Vector4::operator /= (float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	
	return *this;
}

Vector4 Vector4::operator-(void) const
{
	return Vector4(-x,-y,-z,-w);
}

bool Vector4::operator == (const Vector4& other) const
{
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Vector4::operator != (const Vector4& other) const
{
	return x != other.x && y != other.y && z != other.z && w != other.w;
}

bool Vector4::operator < (const Vector4& other) const
{
	return x < other.x && y < other.y && z < other.z && w < other.w;
}

bool Vector4::operator > (const Vector4& other) const
{
	return x > other.x && y > other.y && z > other.z && w > other.w;
}

bool Vector4::operator <= (const Vector4& other) const
{
	return x <= other.x && y <= other.y && z <= other.z && w <= other.w;
}

bool Vector4::operator >= (const Vector4& other) const
{
	return x >= other.x && y >= other.y && z >= other.z && w >= other.w;
}

Vector4 operator * (float f,const Vector4& v)
{
	return Vector4(v.x*f,v.y*f,v.z*f,v.w*f);
}

Vector4 operator + (float f,const Vector4& v)
{
	return Vector4(v.x+f,v.y+f,v.z+f,v.w+f);
}