/*
 * Cameras map image-plane coordinates to rays.
 * The image plane coordinate system:
 *  
 *            (0, 1)
 *              |
 *              |
 *              |
 * (-1, 0) -----+----- (1, 0)
 *              |
 *              |
 *              |
 *           (0, -1)
 */
#ifndef __CAMERA_H
#define __CAMERA_H

#include <vector.h>

// TODO: add environment camera which outputs a spheremap
typedef enum {
    ORTHO_CAMERA,
    PERSPECTIVE_CAMERA,
} CameraType;

/* `direction` and `up` form an orthonormal basis */
typedef struct {
    CameraType type;
    Vec3 pos;
    Vec3 direction;
    Vec3 up;
} Camera;

typedef struct {
    Camera camera;
    float scale;
} OrthoCamera;

typedef struct {
    Camera camera;
    float focalLength;
} PerspectiveCamera;

OrthoCamera *createOrthoCamera(float scale);
PerspectiveCamera *createPerspectiveCamera(float fovDegrees);
void setCameraFOV(PerspectiveCamera *camera, float fovDegrees);
Ray getCameraRay(Camera *camera, float ix, float iy);

#endif