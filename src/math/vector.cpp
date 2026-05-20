#include <math/Vector.hh>
#include <cmath>
#include "Vector.hh"

inline float Vec3::length() const {
    return std::sqrt(x*x + y*y + z*z);
}

Vec3 Vec3::operator+(const Vec3& other) const {
    return { x + other.x, y + other.y, z + other.z };
}

Vec3 Vec3::operator-(const Vec3& other) const {
    return { x - other.x, y - other.y, z - other.z };
}

Vec3& Vec3::operator+=(const Vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vec3 Vec3::operator*(float alpha) const {
    return { x * alpha, y * alpha, z * alpha };
}

Vec3 Vec3::operator/(float alpha) const {
    float inv = 1.0f / alpha;

    return { x * inv, y * inv, z * inv };
}

Vec3 Vec3::normalize() const {
    float length = this->length();

    if (length == 0.0f)
        return { 0, 0, 0 };

    float inv = 1.0f / length;
    return { x * inv, y * inv, z * inv };
}

Vec3 Vec3::cross(const Vec3& other) const {
    return {
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    };
}


// Vec2
Vec2 Vec2::operator+(const Vec2 &other) const
{
    return { x + other.x, y + other.y };
}

Vec2 Vec2::operator-(const Vec2 &other) const {
    return { x - other.x, y - other.y };
}

Vec2 Vec2::operator*(float alpha) const
{
    return { x * alpha, y * alpha };
}

float Vec2::cross(const Vec2 &other) const {
    return x * other.y - y * other.x;
}

float Vec2::length() const {
    return std::sqrt(x*x + y*y);
}