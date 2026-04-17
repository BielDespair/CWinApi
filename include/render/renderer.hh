// render/renderer.hh
#pragma once
#include <Windows.h>

#include <math/vector.hh>


class Renderer {
public:
    void init(HWND hwnd);
    void begin();
    void draw_rect(Vec2 pos, Vec2 size);
    void end();

private:
    HWND hwnd;
    HDC hdc;
};