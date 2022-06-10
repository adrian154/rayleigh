#include "cameras.h"
#include <assert.h>
#include <stdlib.h>

Camera *createCamera() {
    Camera *camera = malloc(sizeof(Camera));
    camera->pos = ZERO;
    camera->direction = EZ;
    camera->up = EY;
    camera->params = NULL;
    return camera;
}

Camera *createOrthoCamera(float scale) {
    Camera *camera = createCamera();
    OrthoCameraParams *params = malloc(sizeof(OrthoCameraParams));
    camera->type = ORTHO_CAMERA;
    camera->params = params;
    params->scale = scale;
    return camera;
}

Camera *createPerspectiveCamera(float fovDegrees) {
    Camera *camera = createCamera();
    PerspectiveCameraParams *params = malloc(sizeof(PerspectiveCameraParams));
    camera->type = PERSPECTIVE_CAMERA;
    camera->params = params;
    setCameraFOV(camera, fovDegrees);
    return camera;
}

void setCameraFOV(Camera *camera, float fovDegrees) {
    assert(camera != NULL);
    assert(camera->type == PERSPECTIVE_CAMERA);
    ((PerspectiveCameraParams *)camera->params)->focalLength = 1 / tanf(fovDegrees / 2);
}

void freeCamera(Camera *camera) {
    assert(camera != NULL);
    free(camera->params);
    free(camera);
}

// The <camera>GetRay functions return Rays in the coordinate space defined by the basis vectors in Camera
// The transformation to world space is performed in getCameraRay

Ray orthoCameraGetRay(Camera *camera, float ix, float iy) {
    float scale = ((OrthoCameraParams *)camera->params)->scale;
    return (Ray) {
        (Vec3) {ix * scale, iy * scale, 0},
        EZ
    };
}

Ray perspectiveCameraGetRay(Camera *camera, float ix, float iy) {
    return (Ray) {
        (Vec3) {0, 0, 0},
        normalize((Vec3) {ix, iy, ((PerspectiveCameraParams *)camera->params)->focalLength})  
    };
}

Ray getCameraRay(Camera *camera, float ix, float iy) {

    Ray cameraRay;
    switch(camera->type) {
        case ORTHO_CAMERA:
            cameraRay = orthoCameraGetRay(camera, ix, iy);
            break;
        case PERSPECTIVE_CAMERA:
            cameraRay = perspectiveCameraGetRay(camera, ix, iy);
            break;
        // FIXME: No error handling on default case
    }

    // complete the basis defined in Camera 
    Vec3 bx = cross(camera->direction, camera->up);
    return (Ray) {
        add(fromCoordSpace(cameraRay.origin, bx, camera->up, camera->direction), camera->pos),
        fromCoordSpace(cameraRay.direction, bx, camera->up, camera->direction)
    };

}