/*
 * Draw a fixed triangle and move a 2D camera around with WASD.
 */

#define LIBGAME_WITH_MAIN
#include "libgame.h"

int main(int argc, char** argv) {
    InitWindow("hello 2D camera");
    SetTargetFps(60);

    Color backgroundColor = { 1, 1, 1, 1 };
    Color triangleColor = { 1, 0, 0, 1 };

    Vec2 a = { 50, 50 };
    Vec2 b = { 250, 50 };
    Vec2 c = { 50, 250 };
    Camera2D camera = {0};
    float cameraSpeed = 4;

    while (IsWindowOpen()) {
        ProcessInput();
        SleepUntilNextFrame();

        if (IsKeyDown(KeyW)) {
            camera.origin.y += cameraSpeed;
        }
        if (IsKeyDown(KeyA)) {
            camera.origin.x -= cameraSpeed;
        }
        if (IsKeyDown(KeyS)) {
            camera.origin.y -= cameraSpeed;
        }
        if (IsKeyDown(KeyD)) {
            camera.origin.x += cameraSpeed;
        }

        SetCamera2D(&camera);

        ClearScreen(backgroundColor);
        DrawTriangle2D(a, b, c, triangleColor);
        MakeDrawCall();
        EndFrame();
    }

    return 0;
}
