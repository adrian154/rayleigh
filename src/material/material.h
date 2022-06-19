// BSDFs and texture sampling
// Each BSDF implements two features:
// - evaluating the BSDF for a pair of incident/outgoing directions
// - drawing a sample from a distribution well-suited for sampling the BSDF (ideally, sampling the BSDF itself)

#ifndef __MATERIAL_H
#define __MATERIAL_H

#include <vector.h>

typedef enum {
    DIFFUSE,
    MIX
} BSDFType;

#endif