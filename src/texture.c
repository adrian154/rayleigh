#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

Vec3 sampleImageTexture(ImageTexture *texture, float u, float v) {
    // TODO
}

Vec3 sampleTexture(void *texture, float u, float v) {
    TextureType type = *(TextureType *)texture;
    switch(type) {
        case CONSTANT:
            return ((ConstantTexture *)texture)->value;
        case IMAGE:
            return sampleImageTexture((ImageTexture *)texture, u, v);
        case BLEND:
            BlendTexture *blend = (BlendTexture *)texture;
            float factor = sampleTexture(blend->factor, u, v).x; // FIXME: we only use R channel for this
            return add(mul(sampleTexture(blend->A, u, v), factor), mul(sampleTexture(blend->B, u, v), 1 - factor));
    }
}