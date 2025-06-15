/*
 * Read keyboard input and print things when pressing space.
 * Draw a triangle at the mouse position.
 */

#define LIBGAME_MAIN
#include "libgame.h"

void DrawCursor();

int main(int argc, char** argv) {
    InitWindow("hello input");
    InitConsole();
    SetTargetFps(60);

    while (IsWindowOpen()) {
        ProcessInput();
        SleepUntilNextFrame();

        if (IsKeyPressed(KeyEsc)) {
            CloseCurrentWindow();
        }
        if (IsKeyPressed(KeySpace)) {
            LogInfo("Started to hold down space\n");
        }
        if (IsKeyDown(KeySpace)) {
            LogInfo("Holding down space\n");
        }
        if (IsKeyReleased(KeySpace)) {
            LogInfo("Released space\n");
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
