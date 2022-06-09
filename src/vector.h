// Code for manipulating 3D vectors and rays

#ifndef __VECTOR_H
#define __VECTOR_H

#include <math.h>

typedef struct {
    float x, y, z;
} vec3;

typedef struct {
    vec3 origin;
    float t;
} ray;

// null vector (sometimes useful)
#define ZERO (vec3) {0, 0, 0};
#define EX (vec3) {1, 0, 0};
#define EY (vec3) {0, 1, 0};
#define EZ (vec3) {0, 0, 1};

static inline vec3 add(vec3 A, vec3 B) {
    return (vec3) {A.x + B.x, A.y + B.y, A.z + B.z};
}

static inline vec3 sub(vec3 A, vec3 B) {
    return (vec3) {A.x - B.x, A.y - B.y, A.z - B.z};
}

// dot product
static inline float dot(vec3 A, vec3 B) {
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

// scalar multiplication
static inline vec3 mul(vec3 V, float S) {
    return (vec3) {V.x * S, V.y * S, V.z * S};
}

// cross product
static inline vec3 cross(vec3 A, vec3 B) {
    return (vec3) {
        A.y * B.z - A.z * B.y,
        A.z * B.x - A.x * B.z,
        A.x * B.y - A.y * B.x
    };
}

// length squared (useful when comparing lengths because it avoids a costly sqrt)
static inline float vecLengthSquared(vec3 V) {
    return dot(V, V);
}

// length 
static inline float vecLength(vec3 V) {
    return sqrtf(vecLengthSquared(V));
}

// convert from coordinate space
static inline vec3 fromCoordSpace(vec3 V, vec3 bx, vec3 by, vec3 bz) {
    return (vec3) {
        V.x * bx.x + V.y * by.x + V.z * bz.x,
        V.x * bx.y + V.y * by.y + V.z * bz.y,
        V.x * bx.z + V.y * by.z + V.z * bz.z  
    };
}

#endif