#include "vector.h"

typedef union _Mat3{
    float r[9];
    float a[3][3];
} Mat3;

typedef union _Mat4{
    float r[16];
    float a[4][4];
}Mat4;