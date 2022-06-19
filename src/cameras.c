#include <cameras.h>
#include <assert.h>
#include <stdlib.h>

void initCamera(Camera *camera) {
    camera->pos = ZERO;
    camera->direction = EZ;
    camera->up = EY;
}

OrthoCamera *createOrthoCamera(float scale) {
    OrthoCamera *camera = malloc(sizeof(OrthoCamera));
    initCamera((Camera *)camera);
    camera->camera.type = ORTHO_CAMERA;
    camera->scale = scale;
    return camera;
}

PerspectiveCamera *createPerspectiveCamera(float fovDegrees) {
    PerspectiveCamera *camera = malloc(sizeof(PerspectiveCamera));
    initCamera((Camera *)camera);
    camera->camera.type = PERSPECTIVE_CAMERA;
    setCameraFOV(camera, fovDegrees);
    return camera;
}

void setCameraFOV(PerspectiveCamera *camera, float fovDegrees) {
    camera->focalLength = 1 / tanf(fovDegrees / 2);
}

// The <camera>GetRay functions return Rays in the coordinate space defined by the basis vectors in Camera
// The transformation to world space is performed in getCameraRay

Ray orthoCameraGetRay(OrthoCamera *camera, float ix, float iy) {
    float scale = camera->scale;
    return (Ray) {
        (Vec3) {ix * scale, iy * scale, 0},
        EZ
    };
}

Ray perspectiveCameraGetRay(PerspectiveCamera *camera, float ix, float iy) {
    return (Ray) {
        ZERO,
        normalize((Vec3) {ix, iy, camera->focalLength})  
    };
}

Ray getCameraRay(Camera *camera, float ix, float iy) {

    Ray cameraRay;
    switch(camera->type) {
        case ORTHO_CAMERA:
            cameraRay = orthoCameraGetRay((OrthoCamera *)camera, ix, iy);
            break;
        case PERSPECTIVE_CAMERA:
            cameraRay = perspectiveCameraGetRay((PerspectiveCamera *)camera, ix, iy);
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