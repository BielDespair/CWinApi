struct Color {
    float r, g, b, a;

    constexpr Color(float r, float g, float b, float a = 1.0f)
        : r(r), g(g), b(b), a(a) {}
};








namespace Colors {
    constexpr Color Black     {0.f, 0.f, 0.f};
    constexpr Color White     {1.f, 1.f, 1.f};
    constexpr Color DarkGray  {0.1f, 0.1f, 0.1f};
    constexpr Color Red       {1.f, 0.f, 0.f};
}