#include "vector.h"
#include <string.h>

inline Vector2 vec2n(float a0,float a1){
    Vector2 v;
    v.x = a0;
    v.y = a1;
    return v;
}

inline Vector3 vec3n(float a0,float a1,float a2){
    Vector3 v;
    v.x = a0;
    v.y = a1;
    v.z = a2;
    return v;
}

inline Vector4 vec4n(float a0,float a1,float a2,float a3){
    Vector4 v;
    v.x = a0;
    v.y = a1;
    v.z = a2;
    v.w = a3;
    return v;
}


inline Vector2 vec2(const float* data){
    Vector2 v;
    memcpy(v.r,data,sizeof(float) * 2);
    return v;
}

inline Vector3 vec3(const float* data){
    Vector3 v;
    memcpy(v.r,data,sizeof(float) * 3);
    return v;
}

inline Vector4 vec4(const float* data){
    Vector4 v;
    memcpy(v.r,data,sizeof(float) * 4);
    return v;
}


inline Vector2 add2f(Vector2 vec,float f){
    float v[2] = {vec.x + f,vec.y + f};
    return vec2(v);
}
inline Vector2 add22(Vector2 lhs,Vector2 rhs){
    float v[2] = {lhs.x + rhs.x,lhs.y + rhs.y};
    return vec2(v);
}

inline Vector2 sub2f(Vector2 vec,float f){
    float v[2] = {vec.x - f,vec.y - f};
    return vec2(v);
}
inline Vector2 sub22(Vector2 lhs,Vector2 rhs){
    float v[2] = {lhs.x - rhs.x,lhs.y - rhs.y};
    return vec2(v);
}

inline Vector2 mul2f(Vector2 vec,float f){
    float v[2] = {vec.x * f,vec.y * f};
    return vec2(v);
}

inline Vector2 mul22(Vector2 lhs,Vector2 rhs){
    float v[2] = {lhs.x * rhs.x,lhs.y * rhs.y};
    return vec2(v);
}

inline Vector2 div2f(Vector2 vec,float f){
    float v[2] = {vec.x / f,vec.y / f};
    return vec2(v);
}

inline float dot2(Vector2 lhs,Vector2 rhs){
    return lhs.x * rhs.x + lhs.y * rhs.y;
}


inline Vector3 add3f(Vector3 vec,float f){
    float v[3] = {vec.x + f,vec.y + f,vec.z + f};
    return vec3(v);
}
inline Vector3 add33(Vector3 lhs,Vector3 rhs){
    float v[3] = {lhs.x + rhs.x,lhs.y + rhs.y,lhs.z + rhs.z};
    return vec3(v);
}

inline Vector3 sub3f(Vector3 vec,float f){
    float v[3] = {vec.x - f,vec.y - f,vec.z - f};
    return vec3(v);
}
inline Vector3 sub33(Vector3 lhs,Vector3 rhs){
    float v[3] = {lhs.x - rhs.x,lhs.y - rhs.y,lhs.z - rhs.z};
    return vec3(v);
}

inline Vector3 mul3f(Vector3 vec,float f){
    float v[3] = {vec.x * f,vec.y * f,vec.z * f};
    return vec3(v);
}
inline Vector3 mul33(Vector3 lhs,Vector3 rhs){
    float v[3] = {lhs.x * rhs.x,lhs.y * rhs.y,lhs.z * rhs.z};
    return vec3(v);
}

inline Vector3 div3f(Vector3 vec,float f){
    float v[3] = {vec.x / f,vec.y / f,vec.z / f};
    return vec3(v);
}

inline float dot3(Vector3 lhs,Vector3 rhs){
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
inline Vector3 cross(Vector3 lhs,Vector3 rhs){
    float v[3] = {lhs.y * rhs.z - lhs.z * rhs.y,
                  lhs.z * rhs.x - lhs.x * rhs.z,
                  lhs.x * rhs.y - lhs.y * rhs.x};
    return vec3(v);
}

inline Vector4 add4f(Vector4 vec,float f){
    float v[4] = {vec.x + f,vec.y + f,vec.z + f,vec.w + f};
    return vec4(v);
}
inline Vector4 add44(Vector4 lhs,Vector4 rhs){
    float v[4] = {lhs.x + rhs.x,lhs.y + rhs.y,lhs.z + rhs.z,lhs.w + rhs.w};
    return vec4(v);
}

inline Vector4 sub4f(Vector4 vec,float f){
    float v[4] = {vec.x - f,vec.y - f,vec.z - f,vec.w - f};
    return vec4(v);
}
inline Vector4 sub44(Vector4 lhs,Vector4 rhs){
    float v[4] = {lhs.x - rhs.x,lhs.y - rhs.y,lhs.z - rhs.z,lhs.w - rhs.w};
    return vec4(v);
}

inline Vector4 mul4f(Vector4 vec,float f){
    float v[4] = {vec.x * f,vec.y * f,vec.z * f,vec.w * f};
    return vec4(v);
}
inline Vector4 mul44(Vector4 lhs,Vector4 rhs){
    float v[4] = {lhs.x * rhs.x,lhs.y * rhs.y,lhs.z * rhs.z,lhs.w * rhs.w};
    return vec4(v);
}

inline Vector4 div4f(Vector4 vec,float f){
    float v[4] = {vec.x / f,vec.y / f,vec.z / f,vec.w /f};
    return vec4(v);
}

inline float dot4(Vector4 lhs,Vector4 rhs){
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}