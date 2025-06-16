/*
 * Rotate a triangle using a delta time.
 * This is to animate based on time rather than the specific frame rate.
 */

#define LIBGAME_WITH_MAIN
#include "libgame.h"
#include "libgame_math.h"

typedef struct {
    Vec2 a;
    Vec2 b;
    Vec2 c;
    Vec2 origin;
    float angle;
} GameState;

void GameUpdate(float deltaTime, GameState* state);

int main(int argc, char** argv) {
    InitWindow("hello delta time");
    SetTargetFps(60);

    GameState state = {0};
    state.a = (Vec2) { 100, 100 };
    state.b = (Vec2) { 300, 100 };
    state.c = (Vec2) { 300, 300 };
    state.origin = state.c;
    state.angle = 0;

    uint64_t ticks = GetTicks();

    while (IsWindowOpen()) {
        ProcessInput();
        SleepUntilNextFrame();

        uint64_t ellapsed = GetTicks() - ticks;
        float deltaTime = TICKS_TO_SECONDS(ellapsed);

        GameUpdate(deltaTime, &state);

        ticks = GetTicks();
    }

    return 0;
}

Color backgroundColor = { 1, 1, 1, 1 };
Color triangleColor = { 1, 0, 0, 1 };
float angularSpeed = 1;

void GameUpdate(float deltaTime, GameState* state) {
    state->angle += deltaTime * angularSpeed;
    Vec2 aRot = Vec2RotateAboutOrigin(state->a, state->origin, state->angle);
    Vec2 bRot = Vec2RotateAboutOrigin(state->b, state->origin, state->angle);
    Vec2 cRot = Vec2RotateAboutOrigin(state->c, state->origin, state->angle);

    ClearScreen(backgroundColor);
    DrawTriangle2D(aRot, bRot, cRot, triangleColor);
    MakeDrawCall();
    EndFrame();
}
