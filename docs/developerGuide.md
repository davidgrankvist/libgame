# Developer Guide

## Directories

- src/include - public headers
- src/common - platform independent shared utils
- src/platform - platform specific library entrypoint
- scripts/ - build/release scripts
- bin/ - binaries
- release/ - release artifacts, including headers and static/dynamic libraries
- vendor/ - external headers (downloaded with scripts)
- examples/ - showcases library features

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

For the most part function pointers are used to avoid a ton of ifdefs (but there are some).

To port, you need to:
- add a new library entrypoint in src/platform. The platform specific code needs to:
    - implement and set up the function pointers defined in src/common/platform_setup.h
    - respond to relevant platform events and call into src/common utilities (for example updating input buffers)
    - if OpenGL is used, implement and set up OpenGL loading defined in src/common/opengl_render.h
- update platform specifc library export and initialization parts of src/include/libgame.h

### Ifdef macros

The ifdefs that do exist have the following conventions:
- build time macros start with LIBGAME_BUILD
- conditional include macros start with LIBGAME_WITH
- prefer function pointers over conditional include macros
- prefer conditional include macros over build time macros

## Examples

Under examples/ there are some small reference applications to showcase different features. There are scripts launching individual examples or building all of them. This is handy for prototyping features, documenting what works and checking the impact of breaking changes.
