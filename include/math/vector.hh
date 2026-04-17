#pragma once



struct Vec2 {
    float x, y;

    float length() const;
    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;
    Vec2 operator*(float alpha) const;

    float cross(const Vec2& other) const;
};



struct Vec3 {
    float x, y, z;
    float length() const;

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator*(float alpha) const;
};


