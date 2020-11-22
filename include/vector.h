#ifndef _vector_
#define _vector_

#include <stddef.h>

typedef union _Vector2{
    struct{
        float x,y;
    };
    float r[2];
} Vector2;

typedef union _Vector3{
    struct {
        float x,y,z;
    };
    float r[3];
} Vector3;

typedef union _Vector4{
    struct{
        float x,y,z,w;
    };
    float r[4];
} Vector4;

Vector2 vec2n(float a0,float a1);
Vector3 vec3n(float a0,float a1,float a2);
Vector4 vec4n(float a0,float a1,float a2,float a3);

Vector2 vec2(const float* data);
Vector3 vec3(const float* data);
Vector4 vec4(const float* data);

Vector2 add2f(Vector2 vec,float f);
Vector2 add22(Vector2 lhs,Vector2 rhs);

Vector2 sub2f(Vector2 vec,float f);
Vector2 sub22(Vector2 lhs,Vector2 rhs);

Vector2 mul2f(Vector2 vec,float f);
Vector2 mul22(Vector2 lhs,Vector2 rhs);

Vector2 div2f(Vector2 vec,float f);

float dot2(Vector2 lhs,Vector2 rhs);


Vector3 add3f(Vector3 vec,float f);
Vector3 add33(Vector3 lhs,Vector3 rhs);

Vector3 sub3f(Vector3 vec,float f);
Vector3 sub33(Vector3 lhs,Vector3 rhs);

Vector3 mul3f(Vector3 vec,float f);
Vector3 mul33(Vector3 lhs,Vector3 rhs);

Vector3 div3f(Vector3 vec,float f);

float dot3(Vector3 lhs,Vector3 rhs);
Vector3 cross(Vector3 lhs,Vector3 rhs);



Vector4 add4f(Vector4 vec,float f);
Vector4 add44(Vector4 lhs,Vector4 rhs);

Vector4 sub4f(Vector4 vec,float f);
Vector4 sub44(Vector4 lhs,Vector4 rhs);

Vector4 mul4f(Vector4 vec,float f);
Vector4 mul44(Vector4 lhs,Vector4 rhs);

Vector4 div4f(Vector4 vec,float f);

float dot4(Vector4 lhs,Vector4 rhs);

#endif