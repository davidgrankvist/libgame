#include <math.h>
#include "libgame.h"

static Vec4 Vec2ToVec4(Vec2 vec);
static Vec3 Vec2ToVec3(Vec2 vec);
static Vec4 Vec3ToVec4(Vec3 vec);
static Vec2 Vec4ToVec2(Vec4 vec);
static Vec3 Vec4ToVec3(Vec4 vec);

float FloatEquals(float a, float b) {
    return fabs(a - b) < EPSILON;
}

float Clamp(float a, float mi, float ma) {
    return fmin(fmax(a, mi), ma);
}

float Lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

Vec2 Vec2Lerp(Vec2 a, Vec2 b, float t) {
    Vec2 lerped = { Lerp(a.x, b.x, t), Lerp(a.y, b.y, t) };
    return lerped;
}

Vec3 Vec3Lerp(Vec3 a, Vec3 b, float t) {
    Vec3 lerped = { Lerp(a.x, b.x, t), Lerp(a.y, b.y, t), Lerp(a.z, b.z, t) };
    return lerped;
}

Mat4 Mat4Identity() {
    Mat4 transform =
    {{
         { 1.0f, 0, 0, 0 },
         { 0, 1.0f, 0, 0 },
         { 0, 0, 1.0f, 0 },
         { 0, 0, 0, 1.0f }
     }};
    return transform;
}

Mat4 Mat4Multiply(Mat4 first, Mat4 second) {
    Mat4 result = {{{0}}};

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            for (int i = 0; i < 4; i++) {
                result.m[y][x] += first.m[y][i] * second.m[i][x];
            }
        }
    }

    return result;
}

Mat4 Mat4MultiplyAll(Mat4 mats[], int size) {
    Mat4 result = mats[0];

    for (int i = 1; i < size; i++) {
        result = Mat4Multiply(result, mats[i]);
    }

    return result;
}

Mat4 Mat4MultiplyAllRev(Mat4 mats[], int size) {
    Mat4 result = mats[size - 1];

    for (int i = size - 2; i >= 0; i--) {
        result = Mat4Multiply(result, mats[i]);
    }

    return result;
}

static Mat4 Mat4AddInternal(Mat4 first, Mat4 second, int sign) {
    Mat4 result = {{{0}}};

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            result.m[y][x] = first.m[y][x] + sign * second.m[y][x];
        }
    }

    return result;
}

Mat4 Mat4Add(Mat4 first, Mat4 second) {
    return Mat4AddInternal(first, second, 1);
}

Mat4 Mat4Subtract(Mat4 first, Mat4 second) {
    return Mat4AddInternal(first, second, -1);
}

Mat4 Mat4RotateX(float angle) {
    Mat4 transform =
    {{
         { 1.0f, 0, 0, 0 },
         { 0, cosf(angle), -sinf(angle), 0 },
         { 0, sinf(angle), cosf(angle), 0 },
         { 0, 0, 0, 1.0f }
     }};
    return transform;
}

Mat4 Mat4RotateY(float angle) {
    Mat4 transform =
    {{
         { cosf(angle), 0, -sinf(angle), 0 },
         { 0, 1.0f, 0, 0 },
         { sinf(angle), 0, cosf(angle), 0 },
         { 0, 0, 0, 1.0f }
     }};
    return transform;
}

Mat4 Mat4RotateZ(float angle) {
    Mat4 transform =
    {{
         { cosf(angle), -sinf(angle), 0, 0 },
         { sinf(angle), cosf(angle), 0, 0 },
         { 0, 0, 1.0f, 0 },
         { 0, 0, 0, 1.0f }
     }};
    return transform;
}

Mat4 Mat4Translate(Vec3 offs) {
    Mat4 transform =
    {{
         { 1.0f, 0, 0, offs.x },
         { 0, 1.0f, 0, offs.y },
         { 0, 0, 1.0f, offs.z },
         { 0, 0, 0, 1.0f }
     }};
    return transform;
}

Mat4 Mat4Translate2D(Vec2 offs) {
    return Mat4Translate(Vec2ToVec3(offs));
}

static Vec4 Vec2ToVec4(Vec2 vec) {
    Vec4 vec4 = { vec.x, vec.y, 0, 1 };
    return vec4;
}

static Vec3 Vec2ToVec3(Vec2 vec) {
    Vec3 vec3 = { vec.x, vec.y, 0, };
    return vec3;
}

static Vec2 Vec4ToVec2(Vec4 vec) {
    Vec2 vec2 = { vec.x, vec.y, };
    return vec2;
}

static Vec4 Vec3ToVec4(Vec3 vec) {
    Vec4 vec4 = { vec.x, vec.y, vec.z, 1 };
    return vec4;
}

static Vec3 Vec4ToVec3(Vec4 vec) {
    Vec3 vec3 = { vec.x, vec.y, vec.z };
    return vec3;
    
}

Vec2 Vec2Scale(Vec2 vec, float scale) {
    Vec2 vec2 = { scale * vec.x, scale * vec.y, };
    return vec2;
}

Vec3 Vec3Scale(Vec3 vec, float scale) {
    Vec3 vec3 = { scale * vec.x, scale * vec.y, scale * vec.z };
    return vec3;
}

Vec4 Vec4Scale(Vec4 vec, float scale) {
    Vec4 result = { vec.x * scale, vec.y * scale, vec.z * scale, 1 };
    return result;
}

Vec2 Vec2Transform(Vec2 vec, Mat4 transform) {
    Vec4 vec4 = Vec2ToVec4(vec);
    Vec4 result4 = Vec4Transform(vec4, transform);
    Vec2 result = Vec4ToVec2(result4);

    return result;
}

Vec3 Vec3Transform(Vec3 vec, Mat4 transform) {
    Vec4 vec4 = Vec3ToVec4(vec);
    Vec4 result4 = Vec4Transform(vec4, transform);
    Vec3 result = Vec4ToVec3(result4);

    return result;
}

Vec4 Vec4Transform(Vec4 vec, Mat4 transform) {
    float vecArr[4] = { vec.x, vec.y, vec.z, vec.w };
    float resultArr[4] = {0};

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            resultArr[y] += transform.m[y][x] * vecArr[x];
        }
    }

    Vec4 result = { resultArr[0], resultArr[1], resultArr[2], resultArr[3] };
    return result;
}

float Vec3Magnitude(Vec3 vec) {
    return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);    
}

Vec3 Vec3Normalize(Vec3 vec) {
   float m = Vec3Magnitude(vec); 
   return (Vec3) { vec.x / m, vec.y / m, vec.z / m };
}

Vec3 Vec3Add(Vec3 a, Vec3 b) {
   return (Vec3) { a.x + b.x, a.y + b.y, a.z + b.z };
}

Vec3 Vec3Sub(Vec3 a, Vec3 b) {
   return (Vec3) { a.x - b.x, a.y - b.y, a.z - b.z };
}

Vec3 Vec3Cross(Vec3 a, Vec3 b) {
    return (Vec3) { 
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    }; 
}

float Vec3Dot(Vec3 a, Vec3 b) {
   return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Mat4 Mat4Rotate2D(float angle) {
    return Mat4RotateZ(angle);
}

Vec2 Vec2Rotate(Vec2 vec, float angle) {
    Mat4 rotate = Mat4Rotate2D(angle);
    Vec2 rotated = Vec2Transform(vec, rotate);
    return rotated;
}

Mat4 Mat4RotateAboutOrigin2D(Vec2 origin, float angle) {
    Vec2 originInverse = Vec2Scale(origin, -1);
    Mat4 translate = Mat4Translate2D(originInverse);
    Mat4 rotate = Mat4RotateZ(angle);
    Mat4 translateBack = Mat4Translate2D(origin);

    Mat4 transforms[] = { translate, rotate, translateBack };
    Mat4 transform = Mat4MultiplyAllRev(transforms, 3);
    return transform;
}

Vec2 Vec2RotateAboutOrigin(Vec2 vec, Vec2 origin, float angle) {
    Mat4 transform = Mat4RotateAboutOrigin2D(origin, angle);
    Vec2 result = Vec2Transform(vec, transform);
    return result;
}

Mat4 Mat4Ortho(float left, float right,
        float bottom, float top,
        float near, float far) {
    Mat4 transform =
    {{
         { 2 / (right - left), 0, 0, -(right + left) / (right - left) },
         { 0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom) },
         { 0, 0, -2 / (far - near), -(far + near) / (far - near) },
         { 0, 0, 0, 1.0f }
     }};
    return transform;
}

Mat4 Mat4ViewTransform(Vec3 target, Vec3 position, Vec3 worldUp) {
    // calculate basis and translation into view space
    Vec3 forward = Vec3Normalize(Vec3Sub(target, position));
    Vec3 right = Vec3Normalize(Vec3Cross(worldUp, forward));
    Vec3 up = Vec3Cross(forward, right);
    float tx = -Vec3Dot(right, position);
    float ty = -Vec3Dot(up, position);
    float tz = -Vec3Dot(forward, position);

    // transform from world space to view space
    Mat4 viewTransform =
    {{
         { right.x, right.y, right.z, tx },
         { up.x, up.y, up.z, ty },
         { forward.x, forward.y, forward.z, tz },
         { 0, 0, 0, 1.0f }
     }};
    
    return viewTransform;
}

Mat4 Mat4Perspective(float fovY, float aspect, float near, float far) {
    float tanHalfFovY = tanf(fovY / 2);
    Mat4 transform =
    {{
         { 1 / (aspect * tanHalfFovY), 0, 0, 0 },
         { 0, 1 / tanHalfFovY, 0, 0 },
         { 0, 0, (far + near) / (far - near), -(2 * far * near) / (far - near) },
         { 0, 0, 1, 0}
     }};
    return transform; 
}

Vec3 Vec3RotateAboutAxis(Vec3 vec, Vec3 axis, float angle) {
    float c = cosf(angle); 
    float s = sinf(angle); 

    // Rodrigues' formula (left-handed)
    Vec3 naxis = Vec3Normalize(axis);
    Vec3 cross = Vec3Cross(naxis, vec);
    float dot = Vec3Dot(naxis, vec);
    Vec3 rotated = {
        vec.x * c - cross.x * s + naxis.x * dot * (1 - c),
        vec.y * c - cross.y * s + naxis.y * dot * (1 - c),
        vec.z * c - cross.z * s + naxis.z * dot * (1 - c),
    };

    return rotated;
}
