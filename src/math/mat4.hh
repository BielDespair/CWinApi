#pragma once
#include <cmath>

constexpr float PI = 3.14159265358979323846f;
constexpr float TWO_PI = 2 * PI;

struct Mat4
{
    float m[16];

    // Acesso direto
    inline float* data() { return m; }
    inline const float* data() const { return m; }

    // Factory
    static Mat4 Identity();
    static Mat4 Translate(float tx, float ty, float tz);
    static Mat4 Scale(float sx, float sy, float sz);
    static Mat4 RotateX(float angle);
    static Mat4 RotateY(float angle);
    static Mat4 RotateZ(float angle);

    // Multiplicação
    static Mat4 Mul(const Mat4& a, const Mat4& b);

    // Conveniência
    static Mat4 TRS(
        float tx, float ty, float tz,
        float rx, float ry, float rz,
        float sx, float sy, float sz
    );
};