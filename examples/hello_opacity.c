/*
 * Draw a mixture of opaque and transparent triangles.
 *
 * Transparency is supported, but requires some setup on the caller side.
 * Transparency mode is applied per draw call, so you need two separate
 * draw calls for opaque and transparent objects.
 */

#define LIBGAME_WITH_MAIN
#include "libgame.h"

typedef struct {
    Vec3 a;
    Vec3 b;
    Vec3 c;
    Color color;
} Triangle;

#define IS_TRANSPARENT(trianglePtr) (trianglePtr->color.a < (1 - EPSILON))
#define APPEND_TRIANGLE(t) triangles[numTriangles++] = t

int main(int argc, char** argv) {
    InitWindow("hello opacity");
    SetTargetFps(60);

    Color backgroundColor = { 1, 1, 1, 1 };

    int numTriangles = 0;
    Triangle triangles[3];

    // opaque
    Triangle t1 = {
        .a = { 0, 0, 100 },
        .b = { 100, 0, 100 },
        .c = { 0, 100, 100 },
        .color = { 0, 1, 0, 1 },
    };
    APPEND_TRIANGLE(t1);

    // transparent behind opaque
    Triangle t2 = {
        .a = { 50, 0, 120 },
        .b = { 150, 0, 120 },
        .c = { 50, 100, 120 },
        .color = { 0, 0, 1, 0.5 },
    };
    APPEND_TRIANGLE(t2);

    // transparent in front of opaque
    Triangle t3 = {
        .a = { -50, 0, 0 },
        .b = { 50, 0, 0 },
        .c = { -50, 100, 0 },
        .color = { 1, 0, 0, 0.5 },
    };
    APPEND_TRIANGLE(t3);

    Camera3D camera = GetDefaultCamera3D();

    while (IsWindowOpen()) {
        ProcessInput();
        SleepUntilNextFrame();

        SetCamera3D(&camera);

        ClearScreen(backgroundColor);

        /*
         * first pass - opaque objects
         *
         * Draw opaque objects first to do occlusion without blending.
         */
        for (int i = 0; i < numTriangles; i++) {
            Triangle* t = &triangles[i];
            if (IS_TRANSPARENT(t)) {
               continue;
            }

            DrawTriangle3D(t->a, t->b, t->c, t->color);
        }
        MakeDrawCall();

        /*
         * second pass - transparent objects
         *
         * Order matters! Transparent objects must be sorted back-to-front,
         * because colors are blended based on previosly drawn fragments.
         *
         * In 3D, sort by distance from the camera.
         */
        for (int i = 0; i < numTriangles; i++) {
            Triangle* t = &triangles[i];
            if (!IS_TRANSPARENT(t)) {
                continue;
            }

            DrawTriangle3D(t->a, t->b, t->c, t->color);
        }
        SetTransparencyMode(true);
        MakeDrawCall();
        SetTransparencyMode(false);

        EndFrame();
    }

    return 0;
}
