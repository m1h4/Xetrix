#include "Globals.h"
#include "Matrix.h"
#include "Vector.h"

Matrix2::Matrix2(void)
{
}

Matrix2::Matrix2(float _11,float _12,float _21,float _22)
{
	m[0][0] = _11; m[1][0] = _21;
	m[0][1] = _12; m[1][1] = _22;
}

Matrix2::Matrix2(const float** m)
{
	this->m[0][0] = m[0][0]; this->m[1][0] = m[1][0];
	this->m[0][1] = m[0][1]; this->m[1][1] = m[1][1];
}

Matrix2::Matrix2(const Matrix2& other)
{
	m[0][0] = other.m[0][0]; m[1][0] = other.m[1][0];
	m[0][1] = other.m[0][1]; m[1][1] = other.m[1][1];
}

void Matrix2::SetEmpty(void)
{
	m[0][0] = 0.0f; m[1][0] = 0.0f;
	m[0][1] = 0.0f; m[1][1] = 0.0f;
}

bool Matrix2::Empty(void) const
{
	return 
		m[0][0] == 0.0f && m[1][0] == 0.0f &&
		m[0][1] == 0.0f && m[1][1] == 0.0f;
}

void Matrix2::SetIdentity(void)
{
	m[0][0] = 1.0f; m[1][0] = 0.0f;
	m[0][1] = 0.0f; m[1][1] = 1.0f;
}

bool Matrix2::Identity(void) const
{
	return 
		m[0][0] == 1.0f && m[1][0] == 0.0f &&
		m[0][1] == 0.0f && m[1][1] == 1.0f;
}

bool Matrix2::operator == (const Matrix2& other) const
{
	return 
		m[0][0] == other.m[0][0] && m[1][0] == other.m[1][0] &&
		m[0][1] == other.m[0][1] && m[1][1] == other.m[1][1];
}

bool Matrix2::operator != (const Matrix2& other) const
{
	return 
		m[0][0] != other.m[0][0] && m[1][0] != other.m[1][0] &&
		m[0][1] != other.m[0][1] && m[1][1] != other.m[1][1];
}

void Matrix2::Rotate(float theta)
{
	float c = cosf(theta);
	float s = sinf(theta);

	m[0][0] = c;
	m[0][1] = s;
	m[1][0] =-s;
	m[1][1] = c;
}

void Matrix2::Scale(const Vector2& scale)
{
	m[0][0] = scale.x;
	m[0][1] = 0.0f;
	m[1][0] = 0.0f;
	m[1][1] = scale.y;
}

void Matrix2::Transform(Vector2* vec) const
{
	float vecm[] = {vec->m[0],vec->m[1]};

	vec->m[0] = vecm[0] * m[0][0] + vecm[1] * m[1][0];
	vec->m[1] = vecm[0] * m[0][1] + vecm[1] * m[1][1];
}

void Matrix2::TransformTransposed(Vector2* vec) const
{
	float vecm[] = {vec->m[0],vec->m[1]};

	vec->m[0] = vecm[0] * m[0][0] + vecm[1] * m[0][1];
	vec->m[1] = vecm[0] * m[1][0] + vecm[1] * m[1][1];
}

Matrix2 Matrix2::operator + (const Matrix2& other) const
{
	Matrix2 result;

	result.m[0][0] = m[0][0] + other.m[0][0]; result.m[1][0] = m[1][0] + other.m[1][0];
	result.m[0][1] = m[0][1] + other.m[0][1]; result.m[1][1] = m[1][1] + other.m[1][1];

	return *this;
}

Matrix2 Matrix2::operator - (const Matrix2& other) const
{
	Matrix2 result;

	result.m[0][0] = m[0][0] - other.m[0][0]; result.m[1][0] = m[1][0] - other.m[1][0];
	result.m[0][1] = m[0][1] - other.m[0][1]; result.m[1][1] = m[1][1] - other.m[1][1];
	
	return *this;
}

Matrix2 Matrix2::operator * (const Matrix2& other) const
{
	Matrix2 result;

	result.m[0][0] = m[0][0] * other.m[0][0] + m[0][0] * other.m[1][0];
	result.m[0][1] = m[0][1] * other.m[0][1] + m[0][1] * other.m[1][1];
	result.m[1][0] = m[1][0] * other.m[0][0] + m[1][0] * other.m[1][0];
	result.m[1][1] = m[1][1] * other.m[0][1] + m[1][1] * other.m[1][1];

	return result;
}

Matrix2 Matrix2::operator ^ (const Matrix2& other) const
{
	Matrix2 result;

	result.m[0][0] = m[0][0] * other.m[0][0] + m[0][1] * other.m[0][1];
	result.m[0][1] = m[0][0] * other.m[1][0] + m[0][1] * other.m[1][1];
	result.m[1][0] = m[1][0] * other.m[0][0] + m[1][1] * other.m[0][1];
	result.m[1][1] = m[1][0] * other.m[1][0] + m[1][1] * other.m[1][1];

	return result;
}

Matrix2 Matrix2::operator * (float s) const
{
	Matrix2 result;

	result.m[0][0] = m[0][0] * s; result.m[1][0] = m[1][0] * s;
	result.m[0][1] = m[0][1] * s; result.m[1][1] = m[1][1] * s;

	return result;
}

Matrix2 Matrix2::operator / (float s) const
{
	Matrix2 result;

	result.m[0][0] = m[0][0] / s; result.m[1][0] = m[1][0] / s;
	result.m[0][1] = m[0][1] / s; result.m[1][1] = m[1][1] / s;

	return result;
}

Matrix2& Matrix2::operator += (const Matrix2& other)
{
	m[0][0] += other.m[0][0]; m[1][0] += other.m[1][0];
	m[0][1] += other.m[0][1]; m[1][1] += other.m[1][1];

	return *this;
}

Matrix2& Matrix2::operator -= (const Matrix2& other)
{
	m[0][0] -= other.m[0][0]; m[1][0] -= other.m[1][0];
	m[0][1] -= other.m[0][1]; m[1][1] -= other.m[1][1];

	return *this;
}

Matrix2& Matrix2::operator *= (float s)
{
	m[0][0] *= s; m[1][0] *= s;
	m[0][1] *= s; m[1][1] *= s;

	return *this;
}

Matrix2& Matrix2::operator /= (float s)
{
	m[0][0] /= s; m[1][0] /= s;
	m[0][1] /= s; m[1][1] /= s;

	return *this;
}

Matrix4::Matrix4(void)
{
}

Matrix4::Matrix4(float _11,float _12,float _13,float _14,float _21,float _22,float _23,float _24,float _31,float _32,float _33,float _34,float _41,float _42,float _43,float _44)
{
	m[0][0] = _11; m[1][0] = _21; m[2][0] = _31; m[3][0] = _41;
	m[0][1] = _12; m[1][1] = _22; m[2][1] = _32; m[3][1] = _42;
	m[0][2] = _13; m[1][2] = _23; m[2][2] = _33; m[3][2] = _43;
	m[0][3] = _14; m[1][3] = _24; m[2][3] = _34; m[3][3] = _44;
}

Matrix4::Matrix4(const float** m)
{
	this->m[0][0] = m[0][0]; this->m[1][0] = m[1][0]; this->m[2][0] = m[2][0]; this->m[3][0] = m[3][0];
	this->m[0][1] = m[0][1]; this->m[1][1] = m[1][1]; this->m[2][1] = m[2][1]; this->m[3][1] = m[3][1];
	this->m[0][2] = m[0][2]; this->m[1][2] = m[1][2]; this->m[2][2] = m[2][2]; this->m[3][2] = m[3][2];
	this->m[0][3] = m[0][3]; this->m[1][3] = m[1][3]; this->m[2][3] = m[2][3]; this->m[3][3] = m[3][3];
}

Matrix4::Matrix4(const Matrix4& other)
{
	m[0][0] = other.m[0][0]; m[1][0] = other.m[1][0]; m[2][0] = other.m[2][0]; m[3][0] = other.m[3][0];
	m[0][1] = other.m[0][1]; m[1][1] = other.m[1][1]; m[2][1] = other.m[2][1]; m[3][1] = other.m[3][1];
	m[0][2] = other.m[0][2]; m[1][2] = other.m[1][2]; m[2][2] = other.m[2][2]; m[3][2] = other.m[3][2];
	m[0][3] = other.m[0][3]; m[1][3] = other.m[1][3]; m[2][3] = other.m[2][3]; m[3][3] = other.m[3][3];
}

void Matrix4::SetEmpty(void)
{
	m[0][0] = 0.0f; m[1][0] = 0.0f; m[2][0] = 0.0f; m[3][0] = 0.0f;
	m[0][1] = 0.0f; m[1][1] = 0.0f; m[2][1] = 0.0f; m[3][1] = 0.0f;
	m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 0.0f; m[3][2] = 0.0f;
	m[0][3] = 0.0f; m[1][3] = 0.0f; m[2][3] = 0.0f; m[3][3] = 0.0f;
}

bool Matrix4::Empty(void) const
{
	return 
		m[0][0] == 0.0f && m[1][0] == 0.0f && m[2][0] == 0.0f && m[3][0] == 0.0f &&
		m[0][1] == 0.0f && m[1][1] == 0.0f && m[2][1] == 0.0f && m[3][1] == 0.0f &&
		m[0][2] == 0.0f && m[1][2] == 0.0f && m[2][2] == 0.0f && m[3][2] == 0.0f &&
		m[0][3] == 0.0f && m[1][3] == 0.0f && m[2][3] == 0.0f && m[3][3] == 0.0f;
}

void Matrix4::SetIdentity(void)
{
	m[0][0] = 1.0f; m[1][0] = 0.0f; m[2][0] = 0.0f; m[3][0] = 0.0f;
	m[0][1] = 0.0f; m[1][1] = 1.0f; m[2][1] = 0.0f; m[3][1] = 0.0f;
	m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f; m[3][2] = 0.0f;
	m[0][3] = 0.0f; m[1][3] = 0.0f; m[2][3] = 0.0f; m[3][3] = 1.0f;
}

bool Matrix4::Identity(void) const
{
	return 
		m[0][0] == 1.0f && m[1][0] == 0.0f && m[2][0] == 0.0f && m[3][0] == 0.0f &&
		m[0][1] == 0.0f && m[1][1] == 1.0f && m[2][1] == 0.0f && m[3][1] == 0.0f &&
		m[0][2] == 0.0f && m[1][2] == 0.0f && m[2][2] == 1.0f && m[3][2] == 0.0f &&
		m[0][3] == 0.0f && m[1][3] == 0.0f && m[2][3] == 0.0f && m[3][3] == 1.0f;
}

void Matrix4::LookAt(const Vector3& eye,const Vector3& at,const Vector3& up)
{
	Vector3 z = at - eye;
	Vector3 x = Vector3Cross(up,z);
	Vector3 y = Vector3Cross(z,x);

	x.Normalize();
	y.Normalize();
	z.Normalize();

	// TODO Maybe asume it's already a identity

	m[0][0]	= x.x;
	m[0][1] = y.x;
	m[0][2] = z.x;
	m[0][3] = 0.0f;

	m[1][0]	= x.y;
	m[1][1] = y.y;
	m[1][2] = z.y;
	m[1][3] = 0.0f;

	m[2][0]	= x.z;
	m[2][1] = y.z;
	m[2][2] = z.z;
	m[2][3] = 0.0f;

	m[3][0]	= -Vector3Dot(x,eye);
	m[3][1] = -Vector3Dot(y,eye);
	m[3][2] = -Vector3Dot(z,eye);
	m[3][3] = 1.0f;
}

void Matrix4::Orthographic(float left,float right,float bottom,float top,float znear,float zfar)
{
	float sx = 1.0f / (right - left);
	float sy = 1.0f / (top - bottom);
	float sz = 1.0f / (zfar - znear);

	// TODO Maybe asume it's already a identity

	m[0][0]	= 2.0f * sx;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = -(right + left) * sx;

	m[1][0] = 0.0f;
	m[1][1] = 2.0f * sy;
	m[1][2] = 0.0f;
	m[1][3] =  -(top + bottom) * sy;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = -2.0f * sz;
	m[2][3] = -(znear + zfar) * sz;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

void Matrix4::Perspective(float left,float right,float top,float bottom,float znear,float zfar)
{
	// TODO Maybe asume it's already a identity

	m[0][0]	= 2.0f * znear / (right - left);
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 2.0f * znear / (top - bottom);
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = zfar / (zfar - znear);
	m[2][3] = znear * zfar / (znear - zfar);

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 1.0f;
	m[3][3] = 0.0f;
}

void Matrix4::Perspective(float fov,float aspect,float znear,float zfar)
{
	// TODO Maybe asume it's already a identity

	float yscale = 1.0f/tanf(fov/2.0f);
	float xscale = yscale/aspect;	// TODO Reverse

	m[0][0]	= xscale;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = yscale;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = zfar / (zfar - znear);
	m[2][3] = 1.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = znear * zfar / (znear - zfar);
	m[3][3] = 0.0f;
}

void Matrix4::Translate(const Vector4& trans)
{
	// TODO Maybe asume it's already a identity

	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
	m[2][3] = 0.0f;

	m[3][0] = trans.x;
	m[3][1] = trans.y;
	m[3][2] = trans.z;
	m[3][3] = trans.w;
}

void Matrix4::Translate(const Vector3& trans)
{
	// TODO Maybe asume it's already a identity

	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
	m[2][3] = 0.0f;

	m[3][0] = trans.x;
	m[3][1] = trans.y;
	m[3][2] = trans.z;
	m[3][3] = 0.0f;
}

void Matrix4::Translate(const Vector2& trans)
{
	// TODO Maybe asume it's already a identity

	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
	m[2][3] = 0.0f;

	m[3][0] = trans.x;
	m[3][1] = trans.y;
	m[3][2] = 0.0f;
	m[3][3] = 0.0f;
}

void Matrix4::Rotate(const Vector3& axis,float theta)
{
	// TODO Maybe asume it's already a identity

	float s = sinf(theta);
	float c = cosf(theta);
	float t = 1.0f - c;

	m[0][0] = c + t * axis.x;
	m[0][1] = t * axis.x * axis.y + s * axis.z;
	m[0][2] = t * axis.x * axis.z - s * axis.y;
	m[0][3] = 0.0f;

	m[1][0] = t * axis.y * axis.x - s * axis.z;
	m[1][1] = c + t * powf(axis.y,2.0f);
	m[1][2] = t * axis.y * axis.z + s * axis.x;
	m[1][3] = 0.0f;

	m[2][0] = t * axis.z * axis.x + s * axis.y;
	m[2][1] = t * axis.z * axis.z - s * axis.x;
	m[2][2] = c + t * powf(axis.z,2.0f);
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

void Matrix4::Rotate(float azimuth,float elevation)
{
	// TODO Maybe asume it's already a identity

	float ca = cosf(azimuth);
	float sa = sinf(azimuth);
	float cb = cosf(elevation);
	float sb = sinf(elevation);

	m[0][0] = cb;
	m[0][1] = -sa * sb;
	m[0][2] = ca * sb;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = ca;
	m[1][2] = sa;
	m[1][3] = 0.0f;

	m[2][0] = -sb;
	m[2][1] = -sa * cb;
	m[2][2] = ca * cb;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

void Matrix4::RotateX(float theta)
{
	// TODO Maybe asume it's already a identity

	//m[0][0] = cosf(theta) + 1.0f - cosf(theta);
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = cosf(theta);
	m[1][2] = sinf(theta);
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = -m[1][2];
	m[2][2] = m[1][1];
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;

	m[0][0] = m[1][1] + 1.0f - m[1][1];
}

void Matrix4::RotateY(float theta)
{
	// TODO Maybe asume it's already a identity

	m[0][0] = cosf(theta);
	m[0][1] = 0.0f;
	m[0][2] = -sinf(theta);
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = m[0][0] + 1.0f - m[0][0];
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = -m[0][2];
	m[2][1] = 0.0f;
	m[2][2] = m[0][0];
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

void Matrix4::RotateZ(float theta)
{
	// TODO Maybe asume it's already a identity

	m[0][0] = cosf(theta);
	m[0][1] = sinf(theta);
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = -m[0][1];
	m[1][1] = m[0][0];
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 1.0f - m[0][0];
	m[2][2] = m[0][0] + 1.0f - m[0][0];
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

void Matrix4::Scale(const Vector4& scale)
{
	// TODO Maybe asume it's already a identity

	m[0][0] = scale.x;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = scale.y;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = scale.z;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = scale.w;
}

void Matrix4::Scale(const Vector3& scale)
{
	// TODO Maybe asume it's already a identity

	m[0][0] = scale.x;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = scale.y;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = scale.z;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

void Matrix4::Scale(const Vector2& scale)
{
	// TODO Maybe asume it's already a identity

	m[0][0] = scale.x;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = scale.y;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

//void Perspective(float fovy,float aspect,float zn,float zf)
//{
//	D3DXMatrixPerspectiveFovLH((LPD3DXMATRIX)this,fovy,aspect,zn,zf);	// TODO Write own function
//}

//void View(const nVector3& eye,const nVector3& lookat,const nVector3& up,const nVector3& right)
//{
//	D3DXMatrixLookAtLH((LPD3DXMATRIX)this,(LPD3DXVECTOR3)&eye,(LPD3DXVECTOR3)&lookat,(LPD3DXVECTOR3)&up);	// TODO Write own function
//}

//void Matrix4::Transform(Vector4* vec) const
//{
//	float vecm[] = {vec->m[0],vec->m[1],vec->m[2],vec->m[3]};
//
//	vec->m[0] = vecm[0] * m[0][0] + vecm[1] * m[1][0] + vecm[2] * m[2][0] + vecm[3] * m[3][0];
//	vec->m[1] = vecm[0] * m[0][1] + vecm[1] * m[1][1] + vecm[2] * m[2][1] + vecm[3] * m[3][1];
//	vec->m[2] = vecm[0] * m[0][2] + vecm[1] * m[1][2] + vecm[2] * m[2][2] + vecm[3] * m[3][2];
//	vec->m[3] = vecm[0] * m[0][3] + vecm[1] * m[1][3] + vecm[2] * m[2][3] + vecm[3] * m[3][3];
//}

void Matrix4::Transform(Vector4* vec) const
{
	float vecm[] = {vec->m[0],vec->m[1],vec->m[2],vec->m[3]};

	vec->m[0] = vecm[0] * m[0][0] + vecm[1] * m[1][0] + vecm[2] * m[2][0] + vecm[3] * m[3][0];
	vec->m[1] = vecm[0] * m[0][1] + vecm[1] * m[1][1] + vecm[2] * m[2][1] + vecm[3] * m[3][1];
	vec->m[2] = vecm[0] * m[0][2] + vecm[1] * m[1][2] + vecm[2] * m[2][2] + vecm[3] * m[3][2];
	vec->m[3] = vecm[0] * m[0][3] + vecm[1] * m[1][3] + vecm[2] * m[2][3] + vecm[3] * m[3][3];
}

void Matrix4::Transform(Vector3* vec) const
{
	float vecm[] = {vec->m[0],vec->m[1],vec->m[2]};

	vec->m[0] = vecm[0] * m[0][0] + vecm[1] * m[1][0] + vecm[2] * m[2][0] + m[3][0];
	vec->m[1] = vecm[0] * m[0][1] + vecm[1] * m[1][1] + vecm[2] * m[2][1] + m[3][1];
	vec->m[2] = vecm[0] * m[0][2] + vecm[1] * m[1][2] + vecm[2] * m[2][2] + m[3][2];
}

//void Matrix4::Transform(Vector2* vec) const
//{
//	float vecm[] = {vec->m[0],vec->m[1]};
//
//	vec->m[0] = vecm[0] * m[0][0] + vecm[1] * m[1][0] + m[2][0] + m[3][0];
//	vec->m[1] = vecm[0] * m[0][1] + vecm[1] * m[1][1] + m[2][1] + m[3][1];
//}

bool Matrix4::operator == (const Matrix4& other) const
{
	return 
		m[0][0] == other.m[0][0] && m[1][0] == other.m[1][0] && m[2][0] == other.m[2][0] && m[3][0] == other.m[3][0] &&
		m[0][1] == other.m[0][1] && m[1][1] == other.m[1][1] && m[2][1] == other.m[2][1] && m[3][1] == other.m[3][1] &&
		m[0][2] == other.m[0][2] && m[1][2] == other.m[1][2] && m[2][2] == other.m[2][2] && m[3][2] == other.m[3][2] &&
		m[0][3] == other.m[0][3] && m[1][3] == other.m[1][3] && m[2][3] == other.m[2][3] && m[3][3] == other.m[3][3];
}

bool Matrix4::operator != (const Matrix4& other) const
{
	return 
		m[0][0] != other.m[0][0] && m[1][0] != other.m[1][0] && m[2][0] != other.m[2][0] && m[3][0] != other.m[3][0] &&
		m[0][1] != other.m[0][1] && m[1][1] != other.m[1][1] && m[2][1] != other.m[2][1] && m[3][1] != other.m[3][1] &&
		m[0][2] != other.m[0][2] && m[1][2] != other.m[1][2] && m[2][2] != other.m[2][2] && m[3][2] != other.m[3][2] &&
		m[0][3] != other.m[0][3] && m[1][3] != other.m[1][3] && m[2][3] != other.m[2][3] && m[3][3] != other.m[3][3];
}

Matrix4 Matrix4::operator + (const Matrix4& other) const
{
	Matrix4 result;

	result.m[0][0] = m[0][0] + other.m[0][0]; result.m[1][0] = m[1][0] + other.m[1][0]; result.m[2][0] = m[2][0] + other.m[2][0]; result.m[3][0] = m[3][0] + other.m[3][0];
	result.m[0][1] = m[0][1] + other.m[0][1]; result.m[1][1] = m[1][1] + other.m[1][1]; result.m[2][1] = m[2][1] + other.m[2][1]; result.m[3][1] = m[3][1] + other.m[3][1];
	result.m[0][2] = m[0][2] + other.m[0][2]; result.m[1][2] = m[1][2] + other.m[1][2]; result.m[2][2] = m[2][2] + other.m[2][2]; result.m[3][2] = m[3][2] + other.m[3][2];
	result.m[0][3] = m[0][3] + other.m[0][3]; result.m[1][3] = m[1][3] + other.m[1][3]; result.m[2][3] = m[2][3] + other.m[2][3]; result.m[3][3] = m[3][3] + other.m[3][3];

	return *this;
}

Matrix4 Matrix4::operator - (const Matrix4& other) const
{
	Matrix4 result;

	result.m[0][0] = m[0][0] - other.m[0][0]; result.m[1][0] = m[1][0] - other.m[1][0]; result.m[2][0] = m[2][0] - other.m[2][0]; result.m[3][0] = m[3][0] - other.m[3][0];
	result.m[0][1] = m[0][1] - other.m[0][1]; result.m[1][1] = m[1][1] - other.m[1][1]; result.m[2][1] = m[2][1] - other.m[2][1]; result.m[3][1] = m[3][1] - other.m[3][1];
	result.m[0][2] = m[0][2] - other.m[0][2]; result.m[1][2] = m[1][2] - other.m[1][2]; result.m[2][2] = m[2][2] - other.m[2][2]; result.m[3][2] = m[3][2] - other.m[3][2];
	result.m[0][3] = m[0][3] - other.m[0][3]; result.m[1][3] = m[1][3] - other.m[1][3]; result.m[2][3] = m[2][3] - other.m[2][3]; result.m[3][3] = m[3][3] - other.m[3][3];
	
	return *this;
}

Matrix4 Matrix4::operator * (const Matrix4& other) const
{
	Matrix4 result;

	result.m[0][0] = m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0] + m[0][2] * other.m[2][0] + m[0][3] * other.m[3][0];
	result.m[0][1] = m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1] + m[0][2] * other.m[2][1] + m[0][3] * other.m[3][1];
	result.m[0][2] = m[0][0] * other.m[0][2] + m[0][1] * other.m[1][2] + m[0][2] * other.m[2][2] + m[0][3] * other.m[3][2];
	result.m[0][3] = m[0][0] * other.m[0][3] + m[0][1] * other.m[1][3] + m[0][2] * other.m[2][3] + m[0][3] * other.m[3][3];

	result.m[1][0] = m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0] + m[1][2] * other.m[2][0] + m[1][3] * other.m[3][0];
	result.m[1][1] = m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1] + m[1][2] * other.m[2][1] + m[1][3] * other.m[3][1];
	result.m[1][2] = m[1][0] * other.m[0][2] + m[1][1] * other.m[1][2] + m[1][2] * other.m[2][2] + m[1][3] * other.m[3][2];
	result.m[1][3] = m[1][0] * other.m[0][3] + m[1][1] * other.m[1][3] + m[1][2] * other.m[2][3] + m[1][3] * other.m[3][3];

	result.m[2][0] = m[2][0] * other.m[0][0] + m[2][1] * other.m[1][0] + m[2][2] * other.m[2][0] + m[2][3] * other.m[3][0];
	result.m[2][1] = m[2][0] * other.m[0][1] + m[2][1] * other.m[1][1] + m[2][2] * other.m[2][1] + m[2][3] * other.m[3][1];
	result.m[2][2] = m[2][0] * other.m[0][2] + m[2][1] * other.m[1][2] + m[2][2] * other.m[2][2] + m[2][3] * other.m[3][2];
	result.m[2][3] = m[2][0] * other.m[0][3] + m[2][1] * other.m[1][3] + m[2][2] * other.m[2][3] + m[2][3] * other.m[3][3];

	result.m[3][0] = m[3][0] * other.m[0][0] + m[3][1] * other.m[1][0] + m[3][2] * other.m[2][0] + m[3][3] * other.m[3][0];
	result.m[3][1] = m[3][0] * other.m[0][1] + m[3][1] * other.m[1][1] + m[3][2] * other.m[2][1] + m[3][3] * other.m[3][1];
	result.m[3][2] = m[3][0] * other.m[0][2] + m[3][1] * other.m[1][2] + m[3][2] * other.m[2][2] + m[3][3] * other.m[3][2];
	result.m[3][3] = m[3][0] * other.m[0][3] + m[3][1] * other.m[1][3] + m[3][2] * other.m[2][3] + m[3][3] * other.m[3][3];

	return result;
}

Matrix4 Matrix4::operator * (float s) const
{
	Matrix4 result;

	result.m[0][0] = m[0][0] * s; result.m[1][0] = m[1][0] * s; result.m[2][0] = m[2][0] * s; result.m[3][0] = m[3][0] * s;
	result.m[0][1] = m[0][1] * s; result.m[1][1] = m[1][1] * s; result.m[2][1] = m[2][1] * s; result.m[3][1] = m[3][1] * s;
	result.m[0][2] = m[0][2] * s; result.m[1][2] = m[1][2] * s; result.m[2][2] = m[2][2] * s; result.m[3][2] = m[3][2] * s;
	result.m[0][3] = m[0][3] * s; result.m[1][3] = m[1][3] * s; result.m[2][3] = m[2][3] * s; result.m[3][3] = m[3][3] * s;

	return result;
}

Matrix4 Matrix4::operator / (float s) const
{
	Matrix4 result;

	result.m[0][0] = m[0][0] / s; result.m[1][0] = m[1][0] / s; result.m[2][0] = m[2][0] / s; result.m[3][0] = m[3][0] / s;
	result.m[0][1] = m[0][1] / s; result.m[1][1] = m[1][1] / s; result.m[2][1] = m[2][1] / s; result.m[3][1] = m[3][1] / s;
	result.m[0][2] = m[0][2] / s; result.m[1][2] = m[1][2] / s; result.m[2][2] = m[2][2] / s; result.m[3][2] = m[3][2] / s;
	result.m[0][3] = m[0][3] / s; result.m[1][3] = m[1][3] / s; result.m[2][3] = m[2][3] / s; result.m[3][3] = m[3][3] / s;

	return result;
}

Matrix4& Matrix4::operator += (const Matrix4& other)
{
	m[0][0] += other.m[0][0]; m[1][0] += other.m[1][0]; m[2][0] += other.m[2][0]; m[3][0] += other.m[3][0];
	m[0][1] += other.m[0][1]; m[1][1] += other.m[1][1]; m[2][1] += other.m[2][1]; m[3][1] += other.m[3][1];
	m[0][2] += other.m[0][2]; m[1][2] += other.m[1][2]; m[2][2] += other.m[2][2]; m[3][2] += other.m[3][2];
	m[0][3] += other.m[0][3]; m[1][3] += other.m[1][3]; m[2][3] += other.m[2][3]; m[3][3] += other.m[3][3];

	return *this;
}

Matrix4& Matrix4::operator -= (const Matrix4& other)
{
	m[0][0] -= other.m[0][0]; m[1][0] -= other.m[1][0]; m[2][0] -= other.m[2][0]; m[3][0] -= other.m[3][0];
	m[0][1] -= other.m[0][1]; m[1][1] -= other.m[1][1]; m[2][1] -= other.m[2][1]; m[3][1] -= other.m[3][1];
	m[0][2] -= other.m[0][2]; m[1][2] -= other.m[1][2]; m[2][2] -= other.m[2][2]; m[3][2] -= other.m[3][2];
	m[0][3] -= other.m[0][3]; m[1][3] -= other.m[1][3]; m[2][3] -= other.m[2][3]; m[3][3] -= other.m[3][3];

	return *this;
}

Matrix4& Matrix4::operator *= (float s)
{
	m[0][0] *= s; m[1][0] *= s; m[2][0] *= s; m[3][0] *= s;
	m[0][1] *= s; m[1][1] *= s; m[2][1] *= s; m[3][1] *= s;
	m[0][2] *= s; m[1][2] *= s; m[2][2] *= s; m[3][2] *= s;
	m[0][3] *= s; m[1][3] *= s; m[2][3] *= s; m[3][3] *= s;

	return *this;
}

Matrix4& Matrix4::operator /= (float s)
{
	m[0][0] /= s; m[1][0] /= s; m[2][0] /= s; m[3][0] /= s;
	m[0][1] /= s; m[1][1] /= s; m[2][1] /= s; m[3][1] /= s;
	m[0][2] /= s; m[1][2] /= s; m[2][2] /= s; m[3][2] /= s;
	m[0][3] /= s; m[1][3] /= s; m[2][3] /= s; m[3][3] /= s;

	return *this;
}