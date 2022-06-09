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