#include <material/diffuse.h>
#include <texture.h>
#include <math.h>
#include <misc/math_defines.h>

Vec3 evaluateDiffuseBSDF(DiffuseBSDF *bsdf, Vec3 incident, Vec3 outgoing, Vec3 normal, float u, float v) {
    return mul(sampleTexture(bsdf->colorTexture, u, v), 1 / M_PI);
}