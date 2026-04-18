
#include "renderer.hh"

void Renderer::init(HWND h) {
    hwnd = h;
}

void Renderer::begin() {
    hdc = GetDC(hwnd);
}

void Renderer::draw_rect(Vec2 pos, Vec2 size) {
    Rectangle(
        hdc,
        (int)pos.x,
        (int)pos.y,
        (int)(pos.x + size.x),
        (int)(pos.y + size.y)
    );
}

void Renderer::end() {
    ReleaseDC(hwnd, hdc);
}