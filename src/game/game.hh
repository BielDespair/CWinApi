#pragma once

#include <render/renderer.hh>
#include <input/input.hh>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;




struct Game {
    Input& input;

    
    void update();
    void render(Renderer& render);
    Game(Input& input);
};
