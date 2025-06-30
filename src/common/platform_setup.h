#ifndef platform_setup_h
#define platform_setup_h

#include <stdint.h>
#include "libgame.h"

// -- Window --

typedef struct {
    void (*InitWindow)(const char* title);
} PlatformWindow;

void InitPlatformWindow(PlatformWindow platformWindow);

void SetResolution(int clientWidth, int clientHeight);

// -- Console --

typedef struct {
    void (*AttachConsole)();
    const char* stdoutName;
    const char* stderrName;
    const char* stdinName;
} PlatformConsole;

/*
 * Prepares InitConsole for usage.
 *
 * Automatically calls InitConsole if the environment variable DEBUG_CONSOLE is set
 */
void InitPlatformConsole(PlatformConsole platformConsole);


// -- Input --

typedef struct {
    void (*ProcessInput)();
    void (*WarpMousePosition)(int x, int y);
} PlatformInput;

void InitPlatformInput(PlatformInput platformInput);

// -- Timing --

typedef struct {
    int64_t (*GetMicroTicks)();
    void (*MicroSleep)(int us);
} PlatformTiming;

void InitPlatformTiming(PlatformTiming timing);

// -- Graphics --

typedef struct {
    void (*Configure)(RenderSettings settings);
    void (*ClearScreen)(Color color);
    void (*MakeDrawCall)();
    void (*EndFrame)();
    void (*SetTransform)(Mat4 mat);
    void (*SetCamera2D)(Camera2D* camera);
    void (*SetCamera3D)(Camera3D* camera);
    void (*DrawTriangle2D)(Vec2 a, Vec2 b, Vec2 c, Color color);
    void (*DrawTriangle3D)(Vec3 a, Vec3 b, Vec3 c, Color color);
    void (*DrawQuad3D)(Vec3 topLeft, Vec3 topRight, Vec3 bottomLeft, Vec3 bottomRight, Color color);
    void (*SetTransparencyMode)(bool shouldEnable);
} PlatformRender;

void InitPlatformRender(PlatformRender platformRender);

// -- Dynamic library loading --

typedef struct {
    void (*ResolvePath)(char* fileBaseName, FileExtensionType extension, char* out, int outSize);
    bool (*LoadDynamicLibrary)(char* libraryPath, DynamicLibrary* lib);
    void* (*LoadLibraryFunction)(char* functionName, DynamicLibrary* lib);
} PlatformLibraryLoader;

void SetPlatformLibraryLoader(PlatformLibraryLoader libraryLoader);

#endif
