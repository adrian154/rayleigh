#ifndef __DIFFUSE_H
#define __DIFFUSE_H

#include <material/material.h>
#include <vector.h>

typedef struct {
    BSDFType type;
    void *colorTexture;
} DiffuseBSDF;

Vec3 evaluateDiffuseBSDF(DiffuseBSDF *bsdf, Vec3 incident, Vec3 outgoing, Vec3 normal, float u, float v);

#endif