/*
 * Draw a 3D quad and use a camera to orbit around it.
 */

#define LIBGAME_MAIN
#include "libgame.h"
#include "libgame_math.h"

int main(int argc, char** argv) {
    InitWindow("hello 3D camera");
    SetTargetFps(60);

    Color backgroundColor = { 1, 1, 1, 1 };
    Color quadColor = { 1, 0, 0, 1 };

    Vec3 topLeft = { 50, 250, 0 };
    Vec3 topRight = { 250, 250, 0 };
    Vec3 bottomLeft = { 50, 50, 0 };
    Vec3 bottomRight = { 250, 50, 0 };
    Vec3 center = Vec3Lerp(topLeft, bottomRight, 0.5);

    Camera3D camera = GetDefaultCamera3D();
    camera.target = center;
    float angleSpeed = 0.01;

    while (IsWindowOpen()) {
        ProcessInput();
        SleepUntilNextFrame();

        OrbitCameraAboutTarget(&camera, angleSpeed, angleSpeed);
        SetCamera3D(&camera);

        ClearScreen(backgroundColor);
        DrawQuad3D(topLeft, topRight, bottomLeft, bottomRight, quadColor);
        MakeDrawCall();
        EndFrame();
    }

    return 0;
}
