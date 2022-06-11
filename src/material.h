// BRDFs and texture sampling

#ifndef __MATERIAL_H
#define __MATERIAL_H

typedef enum {
    DIFFUSE,
    MIX
} BRDFType;

typedef struct {
    BRDFType type;

} DiffuseBRDF;



#endif