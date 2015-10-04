#include "Globals.h"
#include "Interpolations.h"

float LinearInterpolation(float v0,float v1,float s)
{
	return v0 + (v1 - v0) * s;
}

float CubicInterpolation(float v0,float v1,float s)
{
	float s1 = 2.0f * s * s * s;
	float s2 = 3.0f * s * s;

	return v0 * (s1 - s2 + 1.0f) + v1 * (s2 - s1);
}

float CosineInterpolation(float v0,float v1,float s)
{
	float f0 = (1.0f - cosf((float)M_PI * s)) * 0.5f;

	return  v0 * (1.0f - f0) + v1 * f0;
}

void LinearInterpolation(float* result,const float* v0,const float* v1,float s)
{
	result[0] = v0[0] + (v1[0] - v0[0]) * s;
	result[1] = v0[1] + (v1[1] - v0[1]) * s;
	result[2] = v0[2] + (v1[2] - v0[2]) * s;
}

void CubicInterpolation(float* result,const float* v0,const float* v1,float s)
{
	float s1 = 2.0f * s * s * s;
	float s2 = 3.0f * s * s;

	float kp0 = s1 - s2 + 1.0f;
	float kp1 = s2 - s1;

	result[0] = v0[0] * kp0 + v1[0] * kp1;
	result[1] = v0[1] * kp0 + v1[1] * kp1;
	result[2] = v0[2] * kp0 + v1[2] * kp1;
}

void CosineInterpolation(float* result,const float* v0,const float* v1,float s)
{
	float f0 = (1.0f - cosf((float)M_PI * s)) * 0.5f;
	float f1 = 1.0f - f0;

	result[0] = v0[0] * f1 + v1[0] * f0;
	result[1] = v0[1] * f1 + v1[1] * f0;
	result[2] = v0[2] * f1 + v1[2] * f0;
}

void CatmullRomInterpolation(float* result,const float* v0,const float* v1,const float* v2,const float* v3,float s)
{
	float s2 = s * s;
	float s3 = s2 * s;

	float kp0 = (2.0f * s2 -s3 - s) * 0.5f;
	float kp1 = (3.0f * s3 - 5.0f * s2 + 2.0f) * 0.5f;
	float kp2 = (4.0f * s2 - 3.0f * s3 + s) * 0.5f;
	float kp3 = (s3 - s2) * 0.5f;

	result[0] = v0[0] * kp0 + v1[0] * kp1 + v2[0] * kp2 + v3[0] * kp3;
	result[1] = v0[1] * kp0 + v1[1] * kp1 + v2[1] * kp2 + v3[1] * kp3;
	result[2] = v0[2] * kp0 + v1[2] * kp1 + v2[2] * kp2 + v3[2] * kp3;
}

void CatmullRomTangentInterpolation(float* result,const float* v0,const float* v1,const float* t0,const float* t1,float s)
{
	float s2 = s * s;
	float s3 = s2 * s;

	float kp0 = 2.0f * s3 - 3.0f * s2 + 1.0f;
	float kp1 = 3.0f * s2 - 2.0f * s3;
	float kp2 = s3 - 2.0f * s2 + s;
	float kp3 = s3 - s2;

	result[0] = v0[0] * kp0 + v1[0] * kp1 + t0[0] * kp2 + t1[0] * kp3;
	result[1] = v0[1] * kp0 + v1[1] * kp1 + t0[1] * kp2 + t1[1] * kp3;
	result[2] = v0[2] * kp0 + v1[2] * kp1 + t0[2] * kp2 + t1[2] * kp3;
}