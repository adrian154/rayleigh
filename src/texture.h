// texture loading and operations

#ifndef __TEXTURE_H
#define __TEXTURE_H

#include "vector.h"

typedef enum {
    CONSTANT,
    IMAGE,
    BLEND
} TextureType;

typedef struct {
    TextureType type;
    Vec3 value;
} ConstantTexture;

typedef struct {
    TextureType type;

} ImageTexture;

typedef struct {
    TextureType type;
    void *A, *B, *factor;
} BlendTexture;

#endif