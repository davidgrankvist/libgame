/*
 * Create a window with a triangle.
 *
 * In the file with main(), you need to define LIBGAME_WITH_MAIN
 * before the include.
 */

#define LIBGAME_WITH_MAIN
#include "libgame.h"

int main(int argc, char** argv) {
    InitWindow("hello triangle");
    SetTargetFps(60);

    Color backgroundColor = { 1, 1, 1, 1 };
    Color triangleColor = { 1, 0, 0, 1 };

    Vec2 a = { 50, 50 };
    Vec2 b = { 250, 50 };
    Vec2 c = { 50, 250 };

    while (IsWindowOpen()) {
        ProcessInput();
        SleepUntilNextFrame();

        ClearScreen(backgroundColor);
        DrawTriangle2D(a, b, c, triangleColor);
        MakeDrawCall();
        EndFrame();
    }

    return 0;
}
