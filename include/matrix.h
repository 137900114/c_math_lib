#ifndef _matrix_
#define _matrix_

#include "vector.h"

typedef union _Mat3{
    float r[9];
    float a[3][3];
} Mat3;

typedef union _Mat4{
    float r[16];
    float a[4][4];
} Mat4;


Mat3 mat3(float* mat);
Mat4 mat4(float* mat);

Mat3 mat3n(float a00,float a01,float a02,
           float a10,float a11,float a12,
           float a20,float a21,float a22);

Mat4 mat4n(float a00,float a01,float a02,float a03,
           float a10,float a11,float a12,float a13,
           float a20,float a21,float a22,float a23,
           float a30,float a31,float a32,float a33);

Mat3 mat3m4(const Mat4* mat);
Mat4 mat4m3(const Mat3* mat);

//the identity 3x3 matrix
extern const Mat3 mat3i;
//the identity 4x4 matrix
extern const Mat4 mat4i;

//the zero mat of 3x3 matrix
extern const Mat3 mat3zero;
//the zero mat of 4x4 matrix
extern const Mat4 mat4zero;

float mat3det(const Mat3* mat);
float mat4det(const Mat4* mat);

Mat3 mat3inv(const Mat3* mat);
Mat4 mat4inv(const Mat4* mat);


Mat3 mulm3m3(const Mat3* lhs,const Mat3* rhs);
Vector3 mulm33(const Mat3* lhs,Vector3 v);
Mat3 mulm3f(const Mat3* lhs,float f);

Mat4 mulm4m4(const Mat4* lhs,const Mat4* rhs);
Vector4 mulm44(const Mat4* lhs,Vector4 v);
Mat4 mulm4f(const Mat4* lhs,float f);


Mat3 mat3pos(float x,float y);
Mat3 mat3rotate(float angle);
Mat3 mat3scale(float x,float y);

//translate a vector2 value as a point by a 3x3 transform matrix
Vector2 trans2point(const Mat3* mat,Vector2 v);
//translate a vector2 value as a vector by a 3x3 transform matrix
Vector2 trans2vec(const Mat3* mat,Vector2 v);

Mat4 mat4pos(float x,float y,float z);
//we use ZYX euler angle system
Mat4 mat4rotate(float eulerx,float eulery,float eulerz);

Mat4 mat4rotatez(float angle);
Mat4 mat4rotatey(float angle);
Mat4 mat4rotatex(float angle);

Mat4 mat4scale(float x,float y,float z);

//Mat4 mat4perspect(float aspect,float near,float far,float fov);

//translate a vector3 value as a point by a 4x4 transform matrix
Vector3 trans3point(const Mat4* mat,Vector3 v);
//translate a vector3 value as a vector by a 4x4 transform matrix
Vector3 trans3vec(const Mat4* mat,Vector3 v);

#endif