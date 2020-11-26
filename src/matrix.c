#include "matrix.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

#ifndef PI
#define PI 3.1415926536 
#endif


static inline int equals(float a,float b){
    static const float tolerance = 1e-8;
    float dis = a - b;
    return dis * dis < tolerance;
}

Mat3 mat3(const float* data){
    Mat3 mat;
    memcpy(mat.r,data,sizeof(float) * 9);
    return mat;
}
Mat4 mat4(const float* data){
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


float mat4det_special_solver(const Mat4* mat){
    return (mat->a[0][0] * mat->a[1][1] * mat->a[2][2] 
     - mat->a[0][0] * mat->a[1][2] * mat->a[2][1] 
     + mat->a[0][1] * mat->a[1][2] * mat->a[2][0]
     - mat->a[0][1] * mat->a[1][0] * mat->a[2][2]
     + mat->a[0][2] * mat->a[1][0] * mat->a[2][1]
     - mat->a[0][2] * mat->a[1][1] * mat->a[2][0]) * mat->a[3][3];
}

static void add_matrix_row_to(Mat4* mat,int source,int dest,float scale){
    for(int i = 0;i != 4;i++){
        mat->a[dest][i] += mat->a[source][i] * scale;
    }
}

static void scale_matrix_row(Mat4* mat,int dest,float scale){
    for(int i = 0;i != 4;i++){
        mat->a[dest][i] *= scale;
    }
}


float mat4det_general_solver(const Mat4* mat){
    Mat4 copy = mat4(mat->r);
    int non0index = -1;
    for(int i = 0;i != 4;i++){
        if(equals(mat->a[i][0],0)){
            non0index = i;
            break;
        }
    }
    if(non0index < 0) return 0;
    if(non0index != 0){
        add_matrix_row_to(&copy,non0index,0,1.);
    }
    for(int i = 1;i != 4;i++){
        add_matrix_row_to(&copy,0,i,- copy.a[i][0] / copy.a[0][0]);
    }

    Mat3 submat = mat3n(copy.a[1][1],copy.a[1][2],copy.a[1][3],
                        copy.a[2][1],copy.a[2][2],copy.a[2][3],
                        copy.a[3][1],copy.a[3][2],copy.a[3][3]);
    float detsub = mat3det(&submat);
    return detsub * copy.a[0][0];
}



float mat4det(const Mat4* mat){
    //special solver for special matrixs
    if(equals(mat->a[3][0],0.) &&
        equals(mat->a[3][1],0.) &&
        equals(mat->a[3][2],0.)){
        
        return mat4det_special_solver(mat);
    }else{
        return mat4det_general_solver(mat);
    }
}

M_BOOL mat3inv(const Mat3* mat,Mat3* output){
    float matdet = mat3det(mat);
    if(equals(matdet,0)) return M_FALSE;
    float detinv = 1. / matdet;

    output->a[0][0] = detinv * (mat->a[1][1]  * mat->a[2][2] - mat->a[1][2] * mat->a[2][1]);
    output->a[0][1] =-detinv * (mat->a[0][1]  * mat->a[2][2] - mat->a[0][2] * mat->a[2][1]);
    output->a[0][2] = detinv * (mat->a[0][1]  * mat->a[1][2] - mat->a[1][1] * mat->a[0][2]);
    output->a[1][0] =-detinv * (mat->a[1][0]  * mat->a[2][2] - mat->a[2][0] * mat->a[1][2]);
    output->a[1][1] = detinv * (mat->a[0][0]  * mat->a[2][2] - mat->a[0][2] * mat->a[2][0]);
    output->a[1][2] =-detinv * (mat->a[0][0]  * mat->a[1][2] - mat->a[1][0] * mat->a[0][2]);
    output->a[2][0] = detinv * (mat->a[1][0]  * mat->a[2][1] - mat->a[2][0] * mat->a[1][1]);
    output->a[2][1] =-detinv * (mat->a[0][0]  * mat->a[2][1] - mat->a[2][0] * mat->a[0][1]);
    output->a[2][2] = detinv * (mat->a[0][0]  * mat->a[1][1] - mat->a[1][0] * mat->a[0][1]);
    return M_TRUE;
}


static M_BOOL mat4inv_special_solver(const Mat4* mat,Mat4* output){
    float matdet = mat4det_special_solver(mat);
    if(equals(matdet,0)) return M_FALSE;
    float detinv = 1. / matdet *  mat->a[3][3];

    output->a[0][0] = detinv * (mat->a[1][1]  * mat->a[2][2] - mat->a[1][2] * mat->a[2][1]);
    output->a[0][1] =-detinv * (mat->a[0][1]  * mat->a[2][2] - mat->a[0][2] * mat->a[2][1]);
    output->a[0][2] = detinv * (mat->a[0][1]  * mat->a[1][2] - mat->a[1][1] * mat->a[0][2]);
    output->a[1][0] =-detinv * (mat->a[1][0]  * mat->a[2][2] - mat->a[2][0] * mat->a[1][2]);
    output->a[1][1] = detinv * (mat->a[0][0]  * mat->a[2][2] - mat->a[0][2] * mat->a[2][0]);
    output->a[1][2] =-detinv * (mat->a[0][0]  * mat->a[1][2] - mat->a[1][0] * mat->a[0][2]);
    output->a[2][0] = detinv * (mat->a[1][0]  * mat->a[2][1] - mat->a[2][0] * mat->a[1][1]);
    output->a[2][1] =-detinv * (mat->a[0][0]  * mat->a[2][1] - mat->a[2][0] * mat->a[0][1]);
    output->a[2][2] = detinv * (mat->a[0][0]  * mat->a[1][1] - mat->a[1][0] * mat->a[0][1]);


    output->a[3][0] = output->a[3][1] = output->a[3][2] = 0.f;
    output->a[3][3] = 1. / mat->a[3][3];

    output->a[0][3] =-(output->a[0][0] * mat->a[0][3] + output->a[0][1] * mat->a[1][3] + output->a[0][2] * mat->a[2][3]) /  mat->a[3][3];
    output->a[1][3] =-(output->a[1][0] * mat->a[0][3] + output->a[1][1] * mat->a[1][3] + output->a[1][2] * mat->a[2][3]) /  mat->a[3][3];
    output->a[2][3] =-(output->a[2][0] * mat->a[0][3] + output->a[2][1] * mat->a[1][3] + output->a[2][2] * mat->a[2][3]) /  mat->a[3][3];

    return M_TRUE;
}

static M_BOOL mat4inv_general_solver(const Mat4* mat,Mat4* output){
    *output = mat4i;
    Mat4 copy = mat4(mat->r);
    for(int col = 0;col != 4;col++){
        int currrow = col;
        if(equals(copy.a[currrow][col],0.)){
            int non0index = -1;
            for(int j = currrow + 1;j < 4;j++){
                if(!equals(copy.a[j][col],0.)){
                    non0index = j;
                    break;
                }
            }
            if(non0index < 0){
                //the det of the matrix is 0,it is uninversable
                return M_FALSE;
            }
            add_matrix_row_to(&copy,non0index,currrow,1.);
            add_matrix_row_to(output,non0index,currrow,1.);
        }

        float scale = 1. / copy.a[currrow][col];
        scale_matrix_row(&copy,currrow,scale);
        scale_matrix_row(output,currrow,scale);

        for(int j = 0;j < 4;j++){
            if(j == currrow) continue;
            float scale = - copy.a[j][col];
            add_matrix_row_to(&copy,currrow,j,scale);
            add_matrix_row_to(output,currrow,j,scale);
        }
    }
    return M_TRUE;
}


M_BOOL mat4inv(const Mat4* mat,Mat4* output){
    if(equals(mat->a[3][0],0.) &&
        equals(mat->a[3][1],0.) &&
        equals(mat->a[3][2],0.)){
        
        return mat4inv_special_solver(mat,output);
    }else{
        return mat4inv_general_solver(mat,output);
    }
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

void printm3(Mat3* mat){
    printf("%.4f,%.4f,%.4f\n%.4f,%.4f,%.4f\n%.4f,%.4f,%.4f\n",
            mat->a[0][0],mat->a[0][1],mat->a[0][2],
            mat->a[1][0],mat->a[1][1],mat->a[1][2],
            mat->a[2][0],mat->a[2][1],mat->a[2][2]);
}

void printm4(Mat4* mat){
    printf("%.4f,%.4f,%.4f,%.4f\n%.4f,%.4f,%.4f,%.4f\n%.4f,%.4f,%.4f,%.4f\n%.4f,%.4f,%.4f,%.4f\n",
            mat->a[0][0],mat->a[0][1],mat->a[0][2],mat->a[0][3],
            mat->a[1][0],mat->a[1][1],mat->a[1][2],mat->a[1][3],
            mat->a[2][0],mat->a[2][1],mat->a[2][2],mat->a[2][3],
            mat->a[3][0],mat->a[3][1],mat->a[3][2],mat->a[3][3]);
}


Mat4 mat4perspect(float aspect,float near,float far,float fov){
    float fovdiv2tan = tanf(fov / 360. * M_PI);
    
    return mat4n(1. / (fovdiv2tan * aspect),0.                     ,0.                ,0.,
                 0.                        ,1./ fovdiv2tan         ,0.                ,0.,
                 0.                        ,0.                     ,far / (far - near),near * far / (near - far),
                 0.                        ,0.                     ,1.                ,0.);
}