#ifndef opengl_render_h
#define opengl_render_h

// -- OpenGL prerequisites --

#ifdef LIBGAME_WITH_OPENGL_PREREQS
    #ifdef _WIN32
        #define WIN32_LEAN_AND_MEAN
        #include <windows.h>
    #endif
#endif

#include "libgame.h"

// -- OpenGL render backend --

// call before swapping buffers
void EndDrawGl();
// call at window resize
void SetResolutionGl(int width, int height);

// use these to set up PlatformRender
void ConfigureRenderGl(RenderSettings settings);
void ClearScreenGl(Color color);
void SetTransformGl(Mat4 mat);
void EndFrameGl();
void SetCamera2DGl(Camera2D* camera);
void SetCamera3DGl(Camera3D* camera);
void DrawTriangle2DGl(Vec2 a, Vec2 b, Vec2 c, Color color);
void DrawTriangle3DGl(Vec3 a, Vec3 b, Vec3 c, Color color);
void DrawQuad3DGl(Vec3 topLeft, Vec3 topRight, Vec3 bottomLeft, Vec3 bottomRight, Color color);

// -- OpenGL initialization --

#ifdef LIBGAME_WITH_OPENGL_330
    #include <gl/gl.h>

    #define GL_VERSION_3_3 1
    #define GL_GLEXT_PROTOTYPES
    #include <gl/glext.h>

    typedef struct {
        PFNGLBINDBUFFERPROC glBindBuffer;
        PFNGLGENBUFFERSPROC glGenBuffers;
        PFNGLBUFFERDATAPROC glBufferData;
        PFNGLATTACHSHADERPROC glAttachShader;
        PFNGLCOMPILESHADERPROC glCompileShader;
        PFNGLCREATEPROGRAMPROC glCreateProgram;
        PFNGLCREATESHADERPROC glCreateShader;
        PFNGLDELETESHADERPROC glDeleteShader;
        PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
        PFNGLLINKPROGRAMPROC glLinkProgram;
        PFNGLSHADERSOURCEPROC glShaderSource;
        PFNGLUSEPROGRAMPROC glUseProgram;
        PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
        PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
        PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
        PFNGLGETSHADERIVPROC glGetShaderiv;
        PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
        PFNGLGETPROGRAMIVPROC glGetProgramiv;
        PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
        PFNGLBUFFERSUBDATAPROC glBufferSubData;
        PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
        PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
    } OpenGlExt;

    void InitGraphicsGl(OpenGlExt openglExt); // call at window creation
#else
    #error "Unsupported platform. No supported OpenGL version was enabled."
#endif

#endif
