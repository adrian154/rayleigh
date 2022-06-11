// simple vectors/rays implementation

#ifndef __VECTOR_H
#define __VECTOR_H

#include <math.h>

typedef struct {
    float x, y, z;
} Vec3;

typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;

// null vector (sometimes useful)
#define ZERO (Vec3) {0, 0, 0}
#define EX (Vec3) {1, 0, 0}
#define EY (Vec3) {0, 1, 0}
#define EZ (Vec3) {0, 0, 1}

static inline Vec3 add(Vec3 A, Vec3 B) {
    return (Vec3) {A.x + B.x, A.y + B.y, A.z + B.z};
}

static inline Vec3 sub(Vec3 A, Vec3 B) {
    return (Vec3) {A.x - B.x, A.y - B.y, A.z - B.z};
}

// dot product
static inline float dot(Vec3 A, Vec3 B) {
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

// scalar multiplication
static inline Vec3 mul(Vec3 V, float S) {
    return (Vec3) {V.x * S, V.y * S, V.z * S};
}

// cross product
static inline Vec3 cross(Vec3 A, Vec3 B) {
    return (Vec3) {
        A.y * B.z - A.z * B.y,
        A.z * B.x - A.x * B.z,
        A.x * B.y - A.y * B.x
    };
}

// length squared (useful when comparing lengths because it avoids a costly sqrt)
static inline float vecLengthSquared(Vec3 V) {
    return dot(V, V);
}

// length 
static inline float vecLength(Vec3 V) {
    return sqrtf(vecLengthSquared(V));
}

// convert from coordinate space
static inline Vec3 fromCoordSpace(Vec3 V, Vec3 bx, Vec3 by, Vec3 bz) {
    return (Vec3) {
        V.x * bx.x + V.y * by.x + V.z * bz.x,
        V.x * bx.y + V.y * by.y + V.z * bz.y,
        V.x * bx.z + V.y * by.z + V.z * bz.z  
    };
}

static inline Vec3 normalize(Vec3 V) {
    return mul(V, 1 / vecLength(V));
}

#endif