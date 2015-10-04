#pragma once

#pragma warning(push)
#pragma warning(disable:4201)

/*__declspec(align(16))*/ class Matrix2
{
public:
	Matrix2(void);
	Matrix2(float _11,float _12,float _21,float _22);
	Matrix2(const float** m);
	Matrix2(const Matrix2& other);
	Matrix2(float theta) { Rotate(theta); }	// Quick access

	void SetEmpty(void);
	bool Empty(void) const;

	void SetIdentity(void);
	bool Identity(void) const;

	void Rotate(float theta);

	void Scale(const class Vector2& scale);

	void Transform(class Vector2* vec) const;
	void TransformTransposed(class Vector2* vec) const;

	Matrix2 Transpose(void) const { return Matrix2(m[0][0],m[1][0],m[0][1],m[1][1]); }
	float Determinant(void) const { return m[0][0]*m[1][1]-m[0][1]*m[1][0]; }

	bool operator == (const Matrix2& other) const;
	bool operator != (const Matrix2& other) const;

	Matrix2 operator + (const Matrix2& other) const;
	Matrix2 operator - (const Matrix2& other) const;
	Matrix2 operator * (const Matrix2& other) const;
	Matrix2 operator ^ (const Matrix2& other) const;

	Matrix2 operator * (float s) const;
	Matrix2 operator / (float s) const;

	Matrix2& operator += (const Matrix2& other);
	Matrix2& operator -= (const Matrix2& other);
	Matrix2& operator *= (const Matrix2& other) { *this = *this * other; return *this; }
	Matrix2& operator ^= (const Matrix2& other) { *this = *this ^ other; return *this; }

	Matrix2& operator *= (float s);
	Matrix2& operator /= (float s);

	friend Matrix2 operator * (float,const Matrix2&);

	operator float**(void) { return (float**)m; }
	operator const float**(void) const { return (const float**)m; }

public:
	union 
	{
		struct
		{
			float _11, _12;
			float _21, _22;
        };

		float m[2][2];
	};
};

/*__declspec(align(16))*/ class Matrix4
{
public:
	Matrix4(void);
	Matrix4(float _11,float _12,float _13,float _14,float _21,float _22,float _23,float _24,float _31,float _32,float _33,float _34,float _41,float _42,float _43,float _44);
	Matrix4(const float** m);
	Matrix4(const Matrix4& other);
	
	void SetEmpty(void);
	bool Empty(void) const;

	void SetIdentity(void);
	bool Identity(void) const;

	void LookAt(const class Vector3& eye,const class Vector3& at,const class Vector3& up);

	void Orthographic(float left,float right,float bottom,float top,float znear,float zfar);

	void Perspective(float left,float right,float top,float bottom,float znear,float zfar);
	void Perspective(float fov,float aspect,float znear,float zfar);

	void Translate(const class Vector4& trans);
	void Translate(const class Vector3& trans);
	void Translate(const class Vector2& trans);

	void Rotate(const Vector3& axis,float theta);	// Axis must be normalized
	void Rotate(float azimuth, float elevation);

	void RotateX(float theta);
	void RotateY(float theta);
	void RotateZ(float theta);

	void Scale(const Vector4& scale);
	void Scale(const Vector3& scale);
	void Scale(const Vector2& scale);

	void Transform(class Vector4* vec) const;
	void Transform(class Vector3* vec) const;
	//void Transform(class Vector2* vec) const;

	Matrix4 Transpose(void) const { return Matrix4(m[0][0],m[1][0],m[2][0],m[3][0],m[0][1],m[1][1],m[2][1],m[3][1],m[0][2],m[1][2],m[2][2],m[3][2],m[0][3],m[1][3],m[2][3],m[3][3]); }
	float Determinant(void) const { return -m[0][2]*m[1][1]*m[2][0] + m[0][1]*m[1][2]*m[2][0] + m[0][2]*m[1][0]*m[2][1] - m[0][0]*m[1][2]*m[2][1] - m[0][1]*m[1][0]*m[2][2] + m[0][0]*m[1][1]*m[2][2]; }

	bool operator == (const Matrix4& other) const;
	bool operator != (const Matrix4& other) const;

	Matrix4 operator + (const Matrix4& other) const;
	Matrix4 operator - (const Matrix4& other) const;
	Matrix4 operator * (const Matrix4& other) const;

	Matrix4 operator * (float s) const;
	Matrix4 operator / (float s) const;

	Matrix4& operator += (const Matrix4& other);
	Matrix4& operator -= (const Matrix4& other);
	Matrix4& operator *= (const Matrix4& other)	{ *this = *this * other; return *this; }

	Matrix4& operator *= (float s);
	Matrix4& operator /= (float s);

	friend Matrix4 operator * (float,const Matrix4&);

	operator float**(void) { return (float**)m; }
	operator const float**(void) const { return (const float**)m; }

public:
	union 
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
        };

		float m[4][4];
	};
};

#pragma warning(pop)