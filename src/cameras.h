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

typedef struct {
    float scale;
} OrthoCameraParams;

typedef struct {
    float focalLength;
} PerspectiveCameraParams;

Camera *createCamera();
Camera *createOrthoCamera(float scale);
Camera *createPerspectiveCamera(float fovDegrees);
void setCameraFOV(Camera *camera, float fovDegrees);
void freeCamera(Camera *camera);

#endif