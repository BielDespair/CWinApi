#include <math/vector.hh>
#include <cmath>

inline float Vec3::length() const {
    return std::sqrt(x*x + y*y + z*z);
}

Vec3 Vec3::operator+(const Vec3& other) const {
    return { x + other.x, y + other.y, z + other.z };
}

Vec2 Vec2::operator-(const Vec2 &other) const {
    return { x - other.x, y - other.y };
}

float Vec2::cross(const Vec2 &other) const {
    return x * other.y - y * other.x;
}
Vec3 Vec3::operator*(float alpha) const {
    return { x * alpha, y * alpha, z * alpha };
}
float Vec2::length() const {
    return std::sqrt(x*x + y*y);
}