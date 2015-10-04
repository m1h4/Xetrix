#pragma once

float LinearInterpolation(float v0,float v1,float s);
float CubicInterpolation(float v0,float v1,float s);
float CosineInterpolation(float v0,float v1,float s);

void LinearInterpolation(float* result,const float* v0,const float* v1,float s);
void CubicInterpolation(float* result,const float* v0,const float* v1,float s);
void CosineInterpolation(float* result,const float* v0,const float* v1,float s);
void CatmullRomInterpolation(float* result,const float* v0,const float* v1,const float* v2,const float* v3,float s);
void CatmullRomTangentInterpolation(float* result,const float* v0,const float* v1,const float* t0,const float* t1,float s);