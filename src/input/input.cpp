#include "input.hh"



void Input::OnKeyDown(int key)
{
    if (key < 256)
        keys[key] = true;
}

void Input::OnKeyUp(int key)
{
    if (key < 256)
        keys[key] = false;
}

void Input::OnMouseMove(int x, int y) {
    deltaX = x - mouseX;
    deltaY = y - mouseY;

    mouseX = x;
    mouseY = y;
}

void Input::OnMouseScroll(short delta) {
    wheelDelta += delta;
}

bool Input::IsActionDown(Action a) const
{
    if (!currentMap)
        return false;

    auto it = currentMap->find(a);
    if (it == currentMap->end())
        return false;

    for (int i : it->second)
    {
        if (i < 256 && keys[i])
            return true;
    }

    return false;
}

bool Input::IsActionPressed(Action a) const
{
    if (!currentMap)
        return false;

    auto it = currentMap->find(a);
    if (it == currentMap->end())
        return false;

    for (int i : it->second)
    {
        if (i < 256 && keys[i] && !prevKeys[i]) {
            printf("Action is pressed: %d\n", a);
            return true;
        }
    }

    return false;
}

void Input::EndFrame() {
    deltaX = 0;
    deltaY = 0;
    wheelDelta = 0;
    memcpy(prevKeys, keys, sizeof(keys));
}

void Input::SetupDefaultBindings()
{
    //Debug 
    bindings[InputContext::Gameplay][Action::Debug]  = { VK_ESCAPE };
    bindings[InputContext::Gameplay][Action::ZoomIn]  = { VK_OEM_PLUS };
    bindings[InputContext::Gameplay][Action::ZoomOut] = { VK_OEM_MINUS };
    bindings[InputContext::Menu][Action::Debug]  = { VK_ESCAPE };




    // Gameplay
    bindings[InputContext::Gameplay][Action::MoveForward]  = { 'W' };
    bindings[InputContext::Gameplay][Action::MoveBackward] = { 'S' };
    bindings[InputContext::Gameplay][Action::MoveLeft]     = { 'A' };
    bindings[InputContext::Gameplay][Action::MoveRight]    = { 'D' };



    bindings[InputContext::Gameplay][Action::MoveCamera]    = { VK_MBUTTON };


    bindings[InputContext::Gameplay][Action::CameraMoveForward]    = { 'W' };
    bindings[InputContext::Gameplay][Action::CameraMoveBackwards]    = { 'S' };
    bindings[InputContext::Gameplay][Action::CameraMoveLeft]    = { 'A' };
    bindings[InputContext::Gameplay][Action::CameraMoveRight]    = { 'D' };










    bindings[InputContext::Gameplay][Action::LookUp]  = { VK_UP };
    bindings[InputContext::Gameplay][Action::LookDown] = { VK_DOWN };
    bindings[InputContext::Gameplay][Action::LookLeft]     = { VK_LEFT };
    bindings[InputContext::Gameplay][Action::LookRight]    = { VK_RIGHT };

    bindings[InputContext::Gameplay][Action::Jump]   = { VK_SPACE };
    bindings[InputContext::Gameplay][Action::Attack] = { 'X', VK_LBUTTON };

    // Menu
    bindings[InputContext::Menu][Action::Confirm] = { 'E', VK_RETURN };
    bindings[InputContext::Menu][Action::Cancel]  = { VK_ESCAPE };
}

void Input::SetContext(InputContext c) {
    currentContext = c;
    currentMap = &bindings[c];
}

Input::Input()
{
    SetupDefaultBindings();
    SetContext(InputContext::Gameplay);
}
