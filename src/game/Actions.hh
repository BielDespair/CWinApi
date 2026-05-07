#pragma once

enum class Action
{

    // Movement
    MoveForward,
    MoveBackward,
    MoveLeft,
    MoveRight,


    // Actions
    Jump,
    Attack,

    // Menu
    Confirm,
    Cancel,

    MoveUp,
    MoveDown,

    // Camera
    CameraMoveForward,
    CameraMoveBackwards,
    CameraMoveLeft,
    CameraMoveRight,

    LookUp,
    LookDown,
    LookLeft,
    LookRight,
    
    ZoomIn,
    ZoomOut,

    
    // Debug
    Debug,
    MoveCamera,
};