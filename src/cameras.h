/*
 * Cameras map image-plane coordinates to rays.
 * The image plane coordinate system:
 *  
 *            (0, 1)
 *              |
 *              |
 *              |
 * (-1, 0) -----.----- (1, 0)
 *              |
 *              |
 *              |
 *           (0, -1)
 */
#ifndef __CAMERA_H
#define __CAMERA_H

#include <stddef.h>
#include <stdlib.h>
#include "vector.h"

typedef enum {
    ORTHO_CAMERA,
    PERSPECTIVE_CAMERA
} CameraType;

/* `direction` and `up` form an orthonormal basis */
typedef struct {
    CameraType type;
    vec3 pos;
    vec3 direction;
    vec3 up;
    void *params;
} Camera;

static inline Camera *createCamera() {
    Camera *camera = malloc(sizeof(Camera));
    camera->pos = ZERO;
    camera->direction = EZ;
    camera->up = EY;
    camera->params = NULL;
    return camera;
}

static inline Camera *createOrthoCamera(double scale) {
    Camera *camera = createCamera();
    return camera;
}

static inline void releaseCamera(Camera *camera) {
    free(camera->params);
    free(camera);
}

#endif