#include "math/mat4.hh"

// Column-major (OpenGL)
Mat4 Mat4::Identity()
{
    Mat4 r{};
    r.m[0] = 1; r.m[5] = 1; r.m[10] = 1; r.m[15] = 1;
    return r;
}

Mat4 Mat4::Translate(float tx, float ty, float tz)
{
    Mat4 r = Identity();
    r.m[12] = tx;
    r.m[13] = ty;
    r.m[14] = tz;
    return r;
}

Mat4 Mat4::Scale(float sx, float sy, float sz)
{
    Mat4 r{};
    r.m[0] = sx;
    r.m[5] = sy;
    r.m[10] = sz;
    r.m[15] = 1;
    return r;
}

Mat4 Mat4::RotateX(float a)
{
    Mat4 r = Identity();
    float c = cosf(a);
    float s = sinf(a);

    r.m[5] = c;
    r.m[6] = s;
    r.m[9] = -s;
    r.m[10] = c;

    return r;
}

Mat4 Mat4::RotateY(float a)
{
    Mat4 r = Identity();
    float c = cosf(a);
    float s = sinf(a);

    r.m[0] = c;
    r.m[2] = -s;
    r.m[8] = s;
    r.m[10] = c;

    return r;
}

Mat4 Mat4::RotateZ(float a)
{
    Mat4 r = Identity();
    float c = cosf(a);
    float s = sinf(a);

    r.m[0] = c;
    r.m[1] = s;
    r.m[4] = -s;
    r.m[5] = c;

    return r;
}

Mat4 Mat4::Mul(const Mat4& a, const Mat4& b)
{
    Mat4 r{};

    for (int col = 0; col < 4; col++)
    {
        for (int row = 0; row < 4; row++)
        {
            r.m[col * 4 + row] =
                a.m[0 * 4 + row] * b.m[col * 4 + 0] +
                a.m[1 * 4 + row] * b.m[col * 4 + 1] +
                a.m[2 * 4 + row] * b.m[col * 4 + 2] +
                a.m[3 * 4 + row] * b.m[col * 4 + 3];
        }
    }

    return r;
}

Mat4 Mat4::TRS(
    float tx, float ty, float tz,
    float rx, float ry, float rz,
    float sx, float sy, float sz
)
{
    Mat4 T = Translate(tx, ty, tz);
    Mat4 Rx = RotateX(rx);
    Mat4 Ry = RotateY(ry);
    Mat4 Rz = RotateZ(rz);
    Mat4 S = Scale(sx, sy, sz);

    // R = Rz * Ry * Rx
    Mat4 R = Mul(Mul(Rz, Ry), Rx);

    // model = T * R * S
    return Mul(Mul(T, R), S);
}