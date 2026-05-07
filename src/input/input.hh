#pragma once
#include <Windows.h>
#include <unordered_map>
#include <game/Actions.hh>

enum class InputContext {
    Gameplay,
    Menu
};


using ActionMap = std::unordered_map<Action, std::vector<int>>;
using ContextMap = std::unordered_map<InputContext, ActionMap>;


struct Input
{
    ContextMap bindings;
        
    InputContext currentContext;
    const ActionMap* currentMap = nullptr;

    bool keys[256] = {0};

    bool prevKeys[256];

    int mouseX, mouseY;
    int deltaX, deltaY;
    int wheelDelta;

    void OnKeyDown(int key);
    void OnKeyUp(int key);

    void OnMouseMove(int x, int y);
    void OnMouseScroll(short delta);

    bool IsActionDown(Action a) const;
    bool IsActionPressed(Action a) const;

    void EndFrame();

    void SetupDefaultBindings();
    void SetContext(InputContext c);

    Input();

}; 