/*
 * Read keyboard input and print things.
 * Draw a triangle at the mouse position.
 */

#define LIBGAME_MAIN
#include "libgame.h"
#include <stdio.h>

void DrawCursor();

int main(int argc, char** argv) {
    InitWindow("hello input");
    InitConsole(); // set up console for printf
    SetTargetFps(60);

    while (IsWindowOpen()) {
        ProcessInput();
        SleepUntilNextFrame();

        if (IsKeyPressed(KeyEsc)) {
            CloseCurrentWindow();
        }
        if (IsKeyDown(KeySpace)) {
            printf("Holding down space\n");
        }
        if (IsKeyPressed(KeySpace)) {
            printf("Started to hold down space\n");
        }
        if (IsKeyReleased(KeySpace)) {
            printf("Released space\n");
        }

        DrawCursor();
    }

    return 0;
}

void DrawCursor() {
    int mouseX = GetMouseInputX();
    int mouseY = GetMouseInputY();
    int width = GetClientWidth();
    int height = GetClientHeight();

    int screenX = mouseX;
    int screenY = height - mouseY;

    int side = 50;
    Vec2 a = { screenX, screenY };
    Vec2 b = { screenX + side, screenY };
    Vec2 c = { screenX, screenY + side };

    Color backgroundColor = { 1, 1, 1, 1 };
    Color triangleColor = { 1, 0, 0, 1 };

    ClearScreen(backgroundColor);
    DrawTriangle2D(a, b, c, triangleColor);
    MakeDrawCall();
    EndFrame();
}
