#pragma once

#pragma warning(push)
#pragma warning(disable:4201)

class Vector2
{
public:
	Vector2(void) {}
	Vector2(float x,float y) { this->x = x; this->y = y; }
	Vector2(float xy) { x = y = xy; }
	Vector2(const float* m) { this->m[0] = m[0]; this->m[1] = m[1]; }
	Vector2(const Vector2& other) { x = other.x; y = other.y; }

	void SetEmpty(void) { x = y = 0.0f; }
	bool IsEmpty(void) const { return x == 0.0f && y == 0.0f; }

	float GetLength(void) const;
	float GetLengthSqr(void) const { return x * x + y * y; }

	float Normalize(void);
	bool IsNormalized(void) const { return GetLengthSqr() == 1.0f; }

	void LinearInterp(const Vector2& dest,float s);
	void CubicInterp(const Vector2& dest,float s);
	void CosInterp(const Vector2& dest,float s);
	void TransitionInterp(const Vector2& dest,float s);

	Vector2 operator + (const Vector2& other) const { return Vector2(x + other.x,y + other.y); }
	Vector2 operator - (const Vector2& other) const { return Vector2(x - other.x,y - other.y); }
	float operator * (const Vector2& other) const { return x * other.x + y * other.y; }	// Dot product
	float operator ^ (const Vector2& other) const { return x * other.y - y * other.x; }	// Cross product
	Vector2 operator / (const Vector2& other) const { return Vector2(x / other.x,y / other.y); }

	Vector2 operator + (float scalar) const { return Vector2(x + scalar,y + scalar); }
	Vector2 operator - (float scalar) const { return Vector2(x - scalar,y - scalar); }
	Vector2 operator * (float scalar) const { return Vector2(x * scalar,y * scalar); }
	Vector2 operator / (float scalar) const { return Vector2(x / scalar,y / scalar); }

	Vector2 operator * (const class Matrix2& other) const;
	Vector2 operator ^ (const class Matrix2& other) const;
	//Vector2 operator * (const class Matrix4& other) const;

	friend Vector2 operator * (const Matrix2& mat,const Vector2& vec) { return vec * mat; }
	friend Vector2 operator ^ (const Matrix2& mat,const Vector2& vec) { return vec ^ mat; }
	//friend Vector2 operator * (const Matrix4& mat,const Vector2& vec) { return vec * mat; }
    
	Vector2& operator += (const Vector2& other) { x += other.x; y += other.y; return *this; }
	Vector2& operator -= (const Vector2& other) { x -= other.x; y -= other.y; return *this; }
	Vector2& operator /= (const Vector2& other) { x /= other.x; y /= other.y; return *this; }

	Vector2& operator *= (const class Matrix2& other);
	Vector2& operator ^= (const class Matrix2& other);
	//Vector2& operator *= (const class Matrix4& other);

	Vector2& operator += (float scalar) { x += scalar; y += scalar; return *this; }
	Vector2& operator -= (float scalar) { x -= scalar; y -= scalar; return *this; }
	Vector2& operator *= (float scalar) { x *= scalar; y *= scalar; return *this; }
	Vector2& operator /= (float scalar) { x /= scalar; y /= scalar; return *this; }

	friend Vector2 operator * (float scalar,const Vector2& other) { return Vector2(other.x * scalar,other.y * scalar); }
	friend Vector2 operator + (float scalar,const Vector2& other) { return Vector2(other.x + scalar,other.y + scalar); }

	Vector2 operator - (void) const { return Vector2(-x,-y); }

	bool operator == (const Vector2& other) const { return x == other.x && y == other.y; }
	bool operator != (const Vector2& other) const { return x != other.x && y != other.y; }
	bool operator < (const Vector2& other) const { return x < other.x && y < other.y; }
	bool operator > (const Vector2& other) const { return x > other.x && y > other.y; }
	bool operator <= (const Vector2& other) const { return x <= other.x && y <= other.y; }
	bool operator >= (const Vector2& other) const { return x >= other.x && y >= other.y; }

	operator float*(void) { return m; }
	operator const float*(void) const { return m; }

public:
	union 
	{
        struct 
		{
        	float x;
			float y;
        };

        float m[2];
    };
};

class Vector3
{
public:
	Vector3(void) {}
	Vector3(float x,float y,float z) { this->x = x; this->y = y; this->z = z; }
	Vector3(float xyz) { x = y = z = xyz; }
	Vector3(const float* m) { this->m[0] = m[0]; this->m[1] = m[1]; this->m[2] = m[2]; }
	Vector3(const Vector3& other) { x = other.x; y = other.y; z = other.z; }

	void SetEmpty(void) { x = y = z = 0.0f; }
	bool IsEmpty(void) const { return x == 0.0f && y == 0.0f && z == 0.0f; }

	float GetLength(void) const;
	float GetLengthSqr(void) const;

	float Normalize(void);
	bool IsNormalized(void) const { return GetLengthSqr() == 1.0f; }

	void LinearInterp(const Vector3& dest,float s);
	void CubicInterp(const Vector3& dest,float s);
	void CosInterp(const Vector3& dest,float s);
	void TransitionInterp(const Vector3& dest,float s);

	Vector3 operator + (const Vector3& other) const { return Vector3(x + other.x,y + other.y,z + other.z); }
	Vector3 operator - (const Vector3& other) const { return Vector3(x - other.x,y - other.y,z - other.z); }
	float operator * (const Vector3& other) const { return x * other.x + y * other.y + z * other.z; }	// Dot product
	Vector3 operator ^ (const Vector3& other) const { return Vector3(y * other.z - z * other.y,z * other.x - x * other.z,x * other.y - y * other.x); }	// Cross product
	Vector3 operator / (const Vector3& other) const { return Vector3(x / other.x,y / other.y,z / other.z); }

	Vector3 operator + (float scalar) const { return Vector3(x + scalar,y + scalar,z + scalar); }
	Vector3 operator - (float scalar) const { return Vector3(x - scalar,y - scalar,z - scalar); }
	Vector3 operator * (float scalar) const { return Vector3(x * scalar,y * scalar,z * scalar); }
	Vector3 operator / (float scalar) const { return Vector3(x / scalar,y / scalar,z / scalar); }

	Vector3 operator * (const class Matrix4& other) const;
    
	Vector3& operator += (const Vector3& other) { x += other.x; y += other.y; z += other.z; return *this; }
	Vector3& operator -= (const Vector3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	Vector3& operator ^= (const Vector3& other) { *this = *this ^ other; return *this; }	// Cross product
	Vector3& operator /= (const Vector3& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

	Vector3& operator *= (const class Matrix4& other);

	Vector3& operator += (float scalar) { x += scalar; y += scalar; z += scalar; return *this; }
	Vector3& operator -= (float scalar) { x -= scalar; y -= scalar; z -= scalar; return *this; }
	Vector3& operator *= (float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
	Vector3& operator /= (float scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

	friend Vector3 operator * (float scalar,const Vector3& other) { return Vector3(other.x * scalar,other.y * scalar,other.z * scalar); }
	friend Vector3 operator + (float scalar,const Vector3& other) { return Vector3(other.x + scalar,other.y + scalar,other.z + scalar); }

	Vector3 operator - (void) const { return Vector3(-x,-y,-z); }

	bool operator == (const Vector3& other) const { return x == other.x && y == other.y && z == other.z; }
	bool operator != (const Vector3& other) const { return x != other.x && y != other.y && z != other.z; }
	bool operator < (const Vector3& other) const { return x < other.x && y < other.y && z < other.z; }
	bool operator > (const Vector3& other) const { return x > other.x && y > other.y && z > other.z; }
	bool operator <= (const Vector3& other) const { return x <= other.x && y <= other.y && z <= other.z; }
	bool operator >= (const Vector3& other) const { return x >= other.x && y >= other.y && z >= other.z; }

	operator float*(void) { return m; }
	operator const float*(void) const { return m; }

public:
	union 
	{
        struct 
		{
        	float x;
			float y;
			float z;
        };

        float m[3];
    };
};

class Vector4
{
public:
	Vector4(void) {}
	Vector4(float x,float y,float z,float w) { this->x = x; this->y = y; this->z = z; this->w = w; }
	Vector4(float xyzw) { x = y = z = w = xyzw; }
	Vector4(const float* m) { this->m[0] = m[0]; this->m[1] = m[1]; this->m[2] = m[2]; this->m[3] = m[3]; }
	Vector4(const Vector4& other) { x = other.x; y = other.y; z = other.z; w = other.w; }

	void SetEmpty(void);
	bool Empty(void) const;

	float Length(void) const;
	float LengthSqr(void) const;

	float Normalize(void);
	bool Normalized(void) const;

	void LinearInterp(const Vector4& dest,float s);
	void CubicInterp(const Vector4& dest,float s);
	void CosInterp(const Vector4& dest,float s);
	void TransitionInterp(const Vector4& dest,float s);

	Vector4 operator + (const Vector4& other) const;
	Vector4 operator - (const Vector4& other) const;
	float operator * (const Vector4& other) const;	// Dot product
	Vector4 operator ^ (const Vector4& other) const;	// Cross product
	Vector4 operator / (const Vector4& other) const;

	Vector4 operator + (float scalar) const;
	Vector4 operator - (float scalar) const;
	Vector4 operator * (float scalar) const;
	Vector4 operator / (float scalar) const;

	Vector4 operator * (const class Matrix4& other) const;
    
	Vector4& operator += (const Vector4& other);
	Vector4& operator -= (const Vector4& other);
	Vector4& operator ^= (const Vector4& other);	// Cross product
	Vector4& operator /= (const Vector4& other);

	Vector4& operator *= (const class Matrix4& other);

	Vector4& operator += (float scalar);
	Vector4& operator -= (float scalar);
	Vector4& operator *= (float scalar);
	Vector4& operator /= (float scalar);

	friend Vector4 operator * (float,const Vector4&);
	friend Vector4 operator + (float,const Vector4&);

	Vector4 operator-(void) const;

	bool operator == (const Vector4& other) const;
	bool operator != (const Vector4& other) const;
	bool operator < (const Vector4& other) const;
	bool operator > (const Vector4& other) const;
	bool operator <= (const Vector4& other) const;
	bool operator >= (const Vector4& other) const;

	operator float*(void) { return m; }
	operator const float*(void) const { return m; }

public:
	union 
	{
        struct 
		{
        	float x;
			float y;
			float z;
			float w;
        };

        float m[4];
    };
};

inline float Vector2Distance(const Vector2& v1,const Vector2& v2)
{
	return (v2 - v1).GetLength();
}

inline float Vector3Distance(const Vector3& v1,const Vector3& v2)
{
	return (v2 - v1).GetLength();
}

inline float Vector4Distance(const Vector4& v1,const Vector4& v2)
{
	return (v2 - v1).Length();
}

inline Vector2 Vector2Normalize(const Vector2& v)
{
	Vector2 out(v);

	out.Normalize();

	return out;
}

inline Vector3 Vector3Normalize(const Vector3& v)
{
	Vector3 out(v);

	out.Normalize();

	return out;
}

inline Vector4 Vector4Normalize(const Vector4& v)
{
	Vector4 out(v);

	out.Normalize();

	return out;
}

inline float Vector2Dot(const Vector2& v1,const Vector2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

inline float Vector3Dot(const Vector3& v1,const Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float Vector4Dot(const Vector4& v1,const Vector4& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

inline Vector2 Vecotr2LinearInterpolation(const Vector2& v1,const Vector2& v2,float s)
{
	return Vector2(v1 + (v2 - v1) * s);
}

inline Vector3 Vector3LinearInterpolation(const Vector3& v1,const Vector3& v2,float s)
{
	return Vector3(v1 + (v2 - v1) * s);
}

inline Vector2 Vector2CubicInterpolation(const Vector2& v1,const Vector2& v2,float s)
{
	float s1 = 2.0f * powf(s,3.0f);
	float s2 = 3.0f * powf(s,2.0f);

	return Vector2(v1 * (s1 - s2 + 1.0f) + v2 * (s2 - s1));
}

inline Vector3 Vector3CubicInterpolation(const Vector3& v1,const Vector3& v2,float s)
{
	float s1 = 2.0f * powf(s,3.0f);
	float s2 = 3.0f * powf(s,2.0f);

	return Vector3(v1 * (s1 - s2 + 1.0f) + v2 * (s2 - s1));
}

inline Vector3 Vector3HermiteInterpolation(const Vector3& v1,const Vector3& v2,const Vector3& v3,const Vector3& v4, float s)
{
	float t2 = s * s;
	float t3 = t2 * s;

	float kp0 = (2.0f * t2 - t3 - s) / 2.0f;
	float kp1 = (3.0f * t3 - 5.0f * t2 + 2.0f) / 2.0f;
	float kp2 = (4.0f * t2 - 3.0f * t3 + s) / 2.0f;
	float kp3 = (t3 - t2) / 2.0f;

	return v1 * kp0 + v2 * kp1 + v3 * kp2 + v4 * kp3;
}

inline Vector3 Vector3CatmullRomInterpolation(const Vector3& v1,const Vector3& v2,const Vector3& v3,const Vector3& v4, float s)
{
	float s2 = powf(s,2.0f);
	float s3 = powf(s,3.0f);

	return (v1 * (-s3 + 2.0f * s2 - s) + v2 * (3.0f * s3 - 5.0f * s2 + 2.0f) + v3 * (-3.0f * s3 + 4.0f * s2 + s) + v4 * (s3 - s2)) / 2.0f;
}

inline Vector3 Vector3CatmullRomTangentInterpolation(const Vector3& v1,const Vector3& v2,const Vector3& t1,const Vector3& t2, float s)
{
	float s3 = powf(s,3.0f);
	float s2 = powf(s,2.0f);

	return v1 * (2.0f * s3 - 3.0f * s2 + 1.0f) + v2 * (3.0f * s2 - 2.0f * s3) + t1 * (s3 - 2.0f * s2 + s) + t2 * (s3 - s2);
}

inline Vector2 Vector2Perpendicular(const Vector2& vec)
{
	return Vector2(-vec.y,vec.x);
}

inline float Vector2Cross(const Vector2& v1,const Vector2& v2)
{
	return (v1.x * v2.y) - (v1.y * v2.x);
}

inline Vector3 Vector3Cross(const Vector3& v1,const Vector3& v2)
{
	return Vector3(v1.y * v2.z - v1.z * v2.y,v1.z * v2.x - v1.x * v2.z,v1.x * v2.y - v1.y * v2.x);
}

inline Vector3 Vector3Normal(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{
	return Vector3Normalize(Vector3Cross(v3 - v1,v2 - v1));
}

#pragma warning(pop)