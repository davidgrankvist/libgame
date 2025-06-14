# Developer Guide

## Code Structure

- src/ - the engine code
- src/include - public headers
- src/common - platform independent shared utils
- src/platform - platform specific library entrypoint

The platform entrypoint is responsible for:
1. initializing things for the src/common code (setting up OpenGL, etc.)
2. calling internal src/common functions at the right time in response to platform events (input, draw, etc.)

## Building

There are platform specific build script under scripts/.

### Windows

First set up vendor/ with `setup_vendor_win32.ps1`. Then build with `build_win32*.bat` from a VS developer shell.

## Vendor

Summary of vendor/ directory contents.

### OpenGL

Even when OpenGL is supported by a platform, many functions are not declared in the core `<gl/gl.h>` header.
Those functions need to be loaded dynamically and called via function pointers.

There are some extension headers that define the types of the dynamically loaded functions. These are helpful for setting up the function pointers and figuring which functions are available in which OpenGL version.

### Includes

| Include | Purpose | Location | Source |
| ------- | ------- | -------- | ------ |
| `#include <gl/glext.h>` | Render backend calls. Platform independent, but varies for different OpenGL versions.| vendor/include/gl/glext.h | [OpenGL registry](https://github.com/KhronosGroup/OpenGL-Registry/blob/main/api/GL/glext.h) |
| `#include <KHR/khrplatform.h>` | This is a dependency for glext.h.  | vendor/include/KHR/khrplatform.h | [Khronos registry](https://registry.khronos.org/EGL/api/KHR/khrplatform.h) |
| `#include <gl/wglext.h>` | WGL calls. This is for Windows specific OpenGL initialization.  | vendor/include/gl/wglext.h | [OpenGL registry](https://github.com/KhronosGroup/OpenGL-Registry/blob/main/api/GL/wglext.h) |

## Porting

For the most part function pointers are used to avoid a ton of ifdefs.

To port, you need to:
- add a new library entrypoint in src/platform
- implement and set up the function pointers defined in src/common/platform_setup.h
- update platform the library export and initialization parts of src/include/libgame.h

To target a specific OpenGL version, you need to define a macro at build time (LIBGAME_OPENGL_RENDER_330 for OpenGL 3.3.0). The macro is used in src/common/platform_setup.h to define which OpenGL functions to load dynamically.

