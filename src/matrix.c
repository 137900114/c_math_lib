#include "matrix.h"
#include <string.h>
#include <math.h>

#ifndef PI
#define PI 3.1415926536 
#endif

Mat3 mat3(float* data){
    Mat3 mat;
    memcpy(mat.r,data,sizeof(float) * 9);
    return mat;
}
Mat4 mat4(float* data){
    Mat4 mat;
    memcpy(mat.r,data,sizeof(float) * 16);
    return mat;
}

Mat3 mat3n(float a00,float a01,float a02,
           float a10,float a11,float a12,
           float a20,float a21,float a22){
    
    Mat3 mat;
    mat.a[0][0] = a00,mat.a[0][1] = a01,mat.a[0][2] = a02,
    mat.a[1][0] = a10,mat.a[1][1] = a11,mat.a[1][2] = a12,
    mat.a[2][0] = a20,mat.a[2][1] = a21,mat.a[2][2] = a22;

    return mat;
}

Mat4 mat4n(float a00,float a01,float a02,float a03,
           float a10,float a11,float a12,float a13,
           float a20,float a21,float a22,float a23,
           float a30,float a31,float a32,float a33){
    
    Mat4 mat;
    mat.a[0][0] = a00,mat.a[0][1] = a01,mat.a[0][2] = a02,mat.a[0][3] = a03,
    mat.a[1][0] = a10,mat.a[1][1] = a11,mat.a[1][2] = a12,mat.a[1][3] = a13,
    mat.a[2][0] = a20,mat.a[2][1] = a21,mat.a[2][2] = a22,mat.a[2][3] = a23,
    mat.a[3][0] = a30,mat.a[3][1] = a31,mat.a[3][2] = a32,mat.a[3][3] = a33;

    return mat;
}

inline Mat3 mat3m4(const Mat4* mat){
    return mat3n(mat->a[0][0],mat->a[0][1],mat->a[0][2],
                 mat->a[1][0],mat->a[1][1],mat->a[1][2],
                 mat->a[2][0],mat->a[2][1],mat->a[2][2]);
}
inline Mat4 mat4m3(const Mat3* mat){
    return mat4n(mat->a[0][0],mat->a[0][1],mat->a[0][2],0.f,
                 mat->a[1][0],mat->a[1][1],mat->a[1][2],0.f,
                 mat->a[2][0],mat->a[2][1],mat->a[2][2],0.f,
                 0.f         ,0.f         ,0.f         ,1.f);
}

//the identity 3x3 matrix
const Mat3 mat3i = {1.f,0.f,0.f,
              0.f,1.f,0.f,
              0.f,0.f,1.f};
//the identity 4x4 matrix
const Mat4 mat4i = {1.f,0.f,0.f,0.f,
              0.f,1.f,0.f,0.f,
              0.f,0.f,1.f,0.f,
              0.f,0.f,0.f,1.f};

//the zero mat of 3x3 matrix
const Mat3 mat3zero = {
    0.f,0.f,0.f,
    0.f,0.f,0.f,
    0.f,0.f,0.f
};
//the zero mat of 4x4 matrix
const Mat4 mat4zero = {
    0.f,0.f,0.f,0.f,
    0.f,0.f,0.f,0.f,
    0.f,0.f,0.f,0.f,
    0.f,0.f,0.f,0.f
};

float mat3det(const Mat3* mat){
    return mat->a[0][0] * mat->a[1][1] * mat->a[2][2] 
     - mat->a[0][0] * mat->a[1][2] * mat->a[2][1] 
     + mat->a[0][1] * mat->a[1][2] * mat->a[2][0]
     - mat->a[0][1] * mat->a[1][0] * mat->a[2][2]
     + mat->a[0][2] * mat->a[1][0] * mat->a[2][1]
     - mat->a[0][2] * mat->a[1][1] * mat->a[2][0];
}
float mat4det(const Mat4* mat){
    /*TODO*/
    return 0;
}

Mat3 mat3inv(const Mat3* mat){
    /*TODO*/
    return mat3zero;
}
Mat4 mat4inv(const Mat4* mat){
    /*TODO*/
    return mat4zero;
}


Mat3 mulm3m3(const Mat3* lhs,const Mat3* rhs){
    Vector3 lrow1 = vec3(lhs->a[0]),lrow2 = vec3(lhs->a[1]),lrow3 = vec3(lhs->a[2]);
    Vector3 rcol1 = vec3n(rhs->a[0][0],rhs->a[1][0],rhs->a[2][0]),
            rcol2 = vec3n(rhs->a[0][1],rhs->a[1][1],rhs->a[2][1]),
            rcol3 = vec3n(rhs->a[0][2],rhs->a[1][2],rhs->a[2][2]);

    return mat3n(dot3(lrow1,rcol1),dot3(lrow1,rcol2),dot3(lrow1,rcol3),
                dot3(lrow2,rcol1),dot3(lrow2,rcol2),dot3(lrow2,rcol3),
                dot3(lrow3,rcol1),dot3(lrow3,rcol2),dot3(lrow3,rcol3));
}
Vector3 mulm33(const Mat3* lhs,Vector3 v){
    Vector3 lrow1 = vec3(lhs->a[0]),lrow2 = vec3(lhs->a[1]),lrow3 = vec3(lhs->a[2]);
    return vec3n(dot3(lrow1,v),dot3(lrow2,v),dot3(lrow3,v));
}
Mat3 mulm3f(const Mat3* lhs,float f){
    return mat3n(lhs->a[0][0] * f,lhs->a[0][1] * f,lhs->a[0][2] * f,
                 lhs->a[1][0] * f,lhs->a[1][1] * f,lhs->a[1][2] * f,
                 lhs->a[2][0] * f,lhs->a[2][1] * f,lhs->a[2][2] * f);
}

Mat4 mulm4m4(const Mat4* lhs,const Mat4* rhs){
    Vector4 lrow1 = vec4(lhs->a[0]),lrow2 = vec4(lhs->a[1]),lrow3 = vec4(lhs->a[2]),lrow4 = vec4(lhs->a[3]);
    Vector4 rcol1 = vec4n(rhs->a[0][0],rhs->a[1][0],rhs->a[2][0],rhs->a[3][0]),
            rcol2 = vec4n(rhs->a[0][1],rhs->a[1][1],rhs->a[2][1],rhs->a[3][1]),
            rcol3 = vec4n(rhs->a[0][2],rhs->a[1][2],rhs->a[2][2],rhs->a[3][2]),
            rcol4 = vec4n(rhs->a[0][3],rhs->a[1][3],rhs->a[2][3],rhs->a[3][3]);

    return mat4n(dot4(lrow1,rcol1),dot4(lrow1,rcol2),dot4(lrow1,rcol3),dot4(lrow1,rcol4),
                dot4(lrow2,rcol1),dot4(lrow2,rcol2),dot4(lrow2,rcol3),dot4(lrow2,rcol4),
                dot4(lrow3,rcol1),dot4(lrow3,rcol2),dot4(lrow3,rcol3),dot4(lrow3,rcol4),
                dot4(lrow4,rcol1),dot4(lrow4,rcol2),dot4(lrow4,rcol3),dot4(lrow4,rcol4));
}
Vector4 mulm44(const Mat4* lhs,Vector4 v){
    Vector4 lrow1 = vec4(lhs->a[0]),lrow2 = vec4(lhs->a[1]),lrow3 = vec4(lhs->a[2]),lrow4 = vec4(lhs->a[3]);
    return vec4n(dot4(lrow1,v),dot4(lrow2,v),dot4(lrow3,v),dot4(lrow4,v));
}
Mat4 mulm4f(const Mat4* lhs,float f){
    return mat4n(lhs->a[0][0] * f,lhs->a[0][1] * f,lhs->a[0][2] * f,lhs->a[0][3] * f,
                 lhs->a[1][0] * f,lhs->a[1][1] * f,lhs->a[1][2] * f,lhs->a[1][3] * f,
                 lhs->a[2][0] * f,lhs->a[2][1] * f,lhs->a[2][2] * f,lhs->a[2][3] * f,
                 lhs->a[3][0] * f,lhs->a[3][1] * f,lhs->a[3][2] * f,lhs->a[3][3] * f);
}


inline Mat3 mat3pos(float x,float y){
    return mat3n(1.f,0.f,x   ,
                 0.f,1.f,y   ,
                 0.f,0.f,1.f);
}
Mat3 mat3rotate(float angle){
    float sangle = sinf(angle * PI / 180.),
          cangle = cosf(angle * PI / 180.);
    return mat3n(cangle,-sangle,0.f,
                 sangle, cangle,0.f,
                 0.f   , 0.f   ,1.f);
}
Mat3 mat3scale(float x,float y){
    return mat3n(x  ,0.f,0.f,
                 0.f,y  ,0.f,
                 0.f,0.f,1.f);
}

//translate a vector2 value as a point by a 3x3 transform matrix
inline Vector2 trans2point(const Mat3* mat,Vector2 v){
    Vector3 vp = vec3n(v.x,v.y,1.f);
    vp = mulm33(mat,vp);
    return vec2n(vp.x,vp.y);
}
//translate a vector2 value as a vector by a 3x3 transform matrix
inline Vector2 trans2vec(const Mat3* mat,Vector2 v){
    Vector3 vv = vec3n(v.x,v.y,0.f);
    vv = mulm33(mat,vv);
    return vec2n(vv.x,vv.y);
}

Mat4 mat4pos(float x,float y,float z){
    return mat4n(1.f,0.f,0.f,x  ,
                 0.f,1.f,0.f,y  ,
                 0.f,0.f,1.f,z  ,
                 0.f,0.f,0.f,1.f);
}

Mat4 mat4rotatex(float x){
    float ca = cosf(x * PI / 180.),sa = sinf(x * PI / 180.);
    return mat4n(
        1.f,0.f,0.f,0.f,
        0.f,ca ,-sa,0.f,
        0.f,sa , ca,0.f,
        0.f,0.f,0.f,1.f
    );
}
Mat4 mat4rotatey(float x){
    float ca = cosf(x * PI / 180.),sa = sinf(x * PI / 180.);
    return mat4n(
        ca ,0.f,-sa,0.f,
        0.f,1.f,0.f,0.f,
        sa ,0.f, ca,0.f,
        0.f,0.f,0.f,1.f
    );
}
Mat4 mat4rotatez(float x){
    float ca = cosf(x * PI / 180.),sa = sinf(x * PI / 180.);
    return mat4n(ca ,-sa,0.f,0.f,
                 sa , ca,0.f,0.f,
                 0.f,0.f,1.f,0.f,
                 0.f,0.f,0.f,1.f);
}

//we use ZYX euler angle system
inline Mat4 mat4rotate(float eulerx,float eulery,float eulerz){
    Mat4 X = mat4rotatex(eulerx),Y = mat4rotatey(eulery),Z = mat4rotatez(eulerz);
    Y = mulm4m4(&Y,&Z);
    return mulm4m4(&X,&Y);
}
Mat4 mat4scale(float x,float y,float z){
    return mat4n(
        x  ,0.f,0.f,0.f,
        0.f,y  ,0.f,0.f,
        0.f,0.f,z  ,0.f,
        0.f,0.f,0.f,1.f
    );
}

//Mat4 mat4perspect(float aspect,float near,float far,float fov);

//translate a vector3 value as a point by a 4x4 transform matrix
inline Vector3 trans3point(const Mat4* mat,Vector3 v){
    Vector4 vp = vec4n(v.x,v.y,v.z,1.f);
    vp = mulm44(mat,vp);
    return vec3n(vp.x,vp.y,vp.z);
}
//translate a vector3 value as a vector by a 4x4 transform matrix
inline Vector3 trans3vec(const Mat4* mat,Vector3 v){
    Vector4 vv = vec4n(v.x,v.y,v.z,0.f);
    vv = mulm44(mat,vv);
    return vec3n(vv.x,vv.y,vv.z);
}