#include <game.hh>
#include <render/renderer.hh>
#include <math/vector.hh>
#include <cstdio>



Vec2 pos = {0, 0};
const Vec2 vel = {0.01, 0.01};

Vec2 dir = {1, 1};

const int width = 100;
const int height = 100;

const Vec2 size = {width, height};

void update() {
    
    if (pos.x + width > WIDTH) {
        dir.x = -1;
    }
    if (pos.y + height > HEIGHT) {
        dir.y = -1;
    }

    if (pos.x + width < 0) {
        dir.x = 1;
    }
    if (pos.y < 0) {
        dir.y = 1;
    }
    
    pos.x += vel.x * dir.x;
    pos.y += vel.y * dir.y;
}


void render(Renderer& render) {
    render.draw_rect(pos, size);
}