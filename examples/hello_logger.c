/*
 * Use the Log functions to output to an attached console.
 * In this example, press tab to rotate log levels and see which logs appear.
 *
 * Why not printf? You can use printf in some cases, but if you link dynamically
 * you need to set it up by calling freopen from the game code.
 */
#define LIBGAME_MAIN
#include "libgame.h"

int main(int argc, char** argv) {
    InitWindow("hello logger");
    InitConsole();

    SetTargetFps(60);
    LogLevel level = LOG_INFO;

    while (IsWindowOpen()) {
        ProcessInput();
        SleepUntilNextFrame();

        if (IsKeyPressed(KeyTab)) {
            LogDebug("hello debug\n");
            LogInfo("hello info\n");
            Log(LOG_INFO, "hello info with parameter\n");
            LogWarning("hello warning\n");
            LogError("hello error\n");

            LogError("=============================\n");

            level = (level + 1) % (LOG_ERROR + 1);
            SetLogLevel(level);
        }
    }

    return 0;
}
