# libgame

A library for making games.

## About

This is a game-flavoured platform layer. It provides utilities for creating windows, processing input and rendering 2D or 3D graphics.
There are also additional abstractions such as cameras and math helpers.

The library is written from scratch. This is inspired by Casey Muratori's amazing [Handmade Hero](https://guide.handmadehero.org/) series.
The API design is inspired by Ramon Santamaria's fantastic library [raylib](https://www.raylib.com/index.html).

## Usage

The easiest way to get started is by looking in the [examples/](./examples/) directory. Also check out the [public headers](./src/include/).

Here is a simple hello world example.
```cs
/*
 * Create a window with a triangle.
 *
 * The LIBGAME_MAIN macro is only needed in the file with the main function.
 */

#define LIBGAME_MAIN
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
```

## Installation

The library is under construction, so there are no prebuilt binaries at this point. You can still clone the repository and build from source though.

### Building for Windows

These scripts require a Visual Studio developer shell.

Before the first build, run `.\scripts\setup_vendor_win32.ps1` to download external headers. Then you have two options:

1. (recommended) If you want a release build ready for usage, call `.\scripts\release_win32.bat` and use the binaries and headers in the `release` directory.
2. If you want more control like outputting debug symbols you can call `.\scripts\build_win32.bat <debug/release> <dynamic/static>` and use the binaries in the `bin` directory. This will not copy any headers, but you can find the public headers in `src\include`.

## Documentation

There is additional information in the [docs/](./docs/) directory:

- for overview of things like code structure and porting, see [Developer Guide](./docs/developerGuide.md)
- for a summary of some game programming concepts, see [Concepts, Tips and Tricks](./docs/conceptsTipsAndTricks.md)

## Resources

To get started with the Windows APIs, see the [win32 guide](https://learn.microsoft.com/en-us/windows/win32/learnwin32/learn-to-program-for-windows).

To get started with OpenGL, check out [Learn OpenGL](https://learnopengl.com/).
