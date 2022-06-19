#include <texture.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

ConstantTexture *makeConstTexture(Vec3 value) {
    ConstantTexture *texture = malloc(sizeof(ConstantTexture));
    texture->type = CONSTANT_TEXTURE;
    return texture;
}

ImageTexture *loadTexture(const char *filename) {
    ImageTexture *texture = malloc(sizeof(ImageTexture));
    texture->type = IMAGE_TEXTURE;
    unsigned char *data = stbi_load(filename, &(texture->width), &(texture->height), &(texture->channels), 0);
    if(data == NULL) {
        printf("texture loading failed: %s\n", stbi_failure_reason());
        free(texture);
        return NULL;
    }
    texture->data = data;
    return texture;
}

Vec3 sampleImageTexture(ImageTexture *texture, float u, float v) {
    // TODO
}

Vec3 sampleTexture(void *texture, float u, float v) {
    TextureType type = *(TextureType *)texture;
    switch(type) {
        case CONSTANT_TEXTURE:
            return ((ConstantTexture *)texture)->value;
        case IMAGE_TEXTURE:
            return sampleImageTexture((ImageTexture *)texture, u, v);
        case BLEND_TEXTURE: ;
            BlendTexture *blend = (BlendTexture *)texture;
            float factor = sampleTexture(blend->factor, u, v).x; // FIXME: we only use R channel for this
            return add(mul(sampleTexture(blend->A, u, v), factor), mul(sampleTexture(blend->B, u, v), 1 - factor));
    }
}