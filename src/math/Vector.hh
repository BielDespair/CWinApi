#pragma once



struct Vec2 {
    float x = 0, y = 0;

    float length() const;
    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;
    Vec2 operator*(float alpha) const;

    float cross(const Vec2& other) const;
};



struct Vec3 {
    float x = 0, y = 0, z = 0;
    float length() const;

    Vec3() = default;
    Vec3(float v) : x(v), y(v), z(v) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3& operator+=(const Vec3& other);
    Vec3 operator*(float alpha) const;
    Vec3 operator/(float alpha) const;

    Vec3 normalize() const;
    Vec3 cross(const Vec3& other) const;
};