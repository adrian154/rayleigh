// texture loading and operations

#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <vector.h>

typedef enum {
    CONSTANT_TEXTURE,
    IMAGE_TEXTURE,
    BLEND_TEXTURE
} TextureType;

typedef struct {
    TextureType type;
    Vec3 value;
} ConstantTexture;

typedef struct {
    TextureType type;
    int width;
    int height;
    int channels;
    unsigned char *data;
} ImageTexture;

typedef struct {
    TextureType type;
    void *A, *B, *factor;
} BlendTexture;

ConstantTexture *makeConstTexture(Vec3 value);
ImageTexture *loadTexture(const char *filename);
Vec3 sampleTexture(void *texture, float u, float v);

#endif