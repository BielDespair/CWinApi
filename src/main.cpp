
#ifndef UNICODE
#define UNICODE
#endif


#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

#include <glad/glad.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Windows.h>


#include <math/Vector.hh>
#include <render/renderer.hh>
#include <game/game.hh>
#include <input/input.hh>
#include <graphics/triangulation.hh>
#include <render/Shader.hh>

#include <render/buffers/VAO.hh>
#include <render/buffers/VBO.hh>
#include <render/buffers/EBO.hh>
#include <math/mat4.hh>

#include "game/player/Player.hh"
#include "debug/axis.hh"
#include <stddef.h>
#include "graphics/Camera.hh"
#include <iostream>
#include "render/Model.h"
#include "graphics/Colors.hh"

typedef BOOL (WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int);
PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = nullptr;


const Color CLEAR_COLOR = Colors::DarkGray;
Input input;
Game game(input);
Camera camera(input);
Player player;

const glm::mat4 identity(1.0f);

void resizeWindow(HWND& hwnd) {
    RECT r;
    GetClientRect(hwnd, &r);
    glViewport(0, 0, r.right, r.bottom);
    camera.Resize(r.right, r.bottom);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        wprintf(L"WM_CREATE\n");
        break;
    case WM_MOVE:
        //wprintf(L"WM_MOVE\n");
        break;
    case WM_SIZE:
        wprintf(L"WM_SIZE\n");
        resizeWindow(hwnd);
        break;

    case WM_MOUSEMOVE:
        input.OnMouseMove(LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_MOUSEWHEEL:
        input.OnMouseScroll(GET_WHEEL_DELTA_WPARAM(wParam));
        break;
    case WM_DESTROY:
        PostQuitMessage(EXIT_SUCCESS);
        return EXIT_SUCCESS;
    case WM_KEYDOWN:
        input.OnKeyDown(wParam);
        break;

    case WM_KEYUP:
        input.OnKeyUp(wParam);
        break;
    case WM_LBUTTONDOWN:
        input.OnKeyDown(VK_LBUTTON);
        break;
    case WM_LBUTTONUP:
        input.OnKeyUp(VK_LBUTTON);
        break;

    case WM_RBUTTONDOWN:
        input.OnKeyDown(VK_RBUTTON);
        break;
    case WM_RBUTTONUP:
        input.OnKeyUp(VK_RBUTTON);
        break;

    case WM_MBUTTONDOWN:
        input.OnKeyDown(VK_MBUTTON);
        break;
    case WM_MBUTTONUP:
        input.OnKeyUp(VK_MBUTTON);
        break;
    }
    
    

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{


    
    if (!AllocConsole())
    {
        return EXIT_FAILURE;
    }

    FILE *fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);

    wprintf(L"hInstance: %p\n", hInstance);
    wprintf(L"lpCmdLine: %hs\n", lpCmdLine);
    wprintf(L"nCmdShow: %d\n", nCmdShow);

    const wchar_t *CLASS_NAME = TEXT("WindowClass");

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // HWND ->
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        TEXT("Janela"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, // x position
        CW_USEDEFAULT, // y position
        CW_USEDEFAULT, // width
        CW_USEDEFAULT, // height
        NULL,          // Parent window
        NULL,          // Menu
        hInstance,     // Instance Handle,
        NULL);

    if (hwnd == NULL)
    {
        return EXIT_FAILURE;
    }

    HDC hdc = GetDC(hwnd);
    
    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pf = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pf, &pfd);
    HGLRC glrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, glrc);
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
    wglSwapIntervalEXT(0);
    gladLoadGL();




    //Renderer renderer = Renderer();
    //renderer.init(hwnd);

    ShowWindow(hwnd, nCmdShow);
    MSG msg = {0};

    RECT r;
    GetClientRect(hwnd, &r);
    glViewport(0, 0, r.right, r.bottom);
    camera.Resize(r.right, r.bottom);
    
    Shader shaderProgram = Shader::Shader("basic/basic.glsl", "basic/frag.glsl");
    Shader planeShader = Shader::Shader("debug/plane.glsl", "debug/planeFrag.glsl");
    
    Model myCube("resources/models/Untitled.obj");
    Model arrowsModel = getArrowsModel();

    Mesh cyl = buildCylinder(
    0.5f,              // raio
    2.0f,              // altura
    30,                // segmentos
    Vec3{0,0,0},       // centro
    Vec3{0,1,0},       // direção (eixo Y)
    Vec3{0.2f,0.7f,1}  // cor
    );

    // Axis
    VAO axisVAO;
    axisVAO.Bind();

    VBO axisVBO(axis, sizeof(axis));

    axisVAO.LinkAttrib(axisVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    axisVAO.LinkAttrib(axisVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    






    GLuint viewProjID = glGetUniformLocation(shaderProgram.ID, "viewProj");
    GLuint modelID = glGetUniformLocation(shaderProgram.ID, "model");

    // Plane
    GLuint planeVP_ID = glGetUniformLocation(planeShader.ID, "gVP");
    GLuint planeCameraID = glGetUniformLocation(planeShader.ID, "gCameraWorldPos");

    

    
    float rotSpeed = 0.005f; // rad/s
    float ax = 0.0f;
    float ay = 0.0f;
    float az = 0.0f;

    float tx = 0.0f;
    float ty = 0.0f;
    float tz = 0.0f;

    bool running = true;
    bool debug = false;

    int width = r.right;
    int height = r.bottom;

    float scaleValue = 1.0f;


    

    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    LARGE_INTEGER last;
    QueryPerformanceCounter(&last);

    int frames = 0;
    float acc = 0.0f;
    int fps = 0;
    
    while (running)
    {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        float dt = (float)(now.QuadPart - last.QuadPart) / (float)freq.QuadPart;
        last = now;
        acc += dt;
        frames++;

        if (acc >= 1.0f) {
            fps = frames;
            frames = 0;
            acc = 0.0f;
            std::string title = "FPS: " + std::to_string(fps);
            SetWindowTextA(hwnd, title.c_str());
        }


        


        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                running = false;
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (!running) break;


        camera.Update(dt);
        
        if (!input.IsActionDown(Action::MoveCamera)) {
            ax += input.deltaY * rotSpeed * -1;
            ay += input.deltaX * rotSpeed * -1;
            
        }

        if (input.IsActionPressed(Action::Debug)) {
            debug = !debug;
            ax = ay = az = tx = ty = tz = player.x = player.y = player.z = 0.0f;
            camera.Reset();
        }

        if (input.IsActionDown(Action::ZoomIn)) {
            scaleValue += dt;
        }
        if (input.IsActionDown(Action::ZoomOut)) {
            scaleValue -= dt;
        }

        

        input.EndFrame();
        
        ax = fmodf(ax, TWO_PI);
        ay = fmodf(ay, TWO_PI);

        glm::vec3 position(tx, ty, tz);
        glm::vec3 rotation(ax, ay, az);
        glm::vec3 scale(scaleValue);

        glm::mat4 model(1.0f);


        model = glm::translate(model, position);
        model = glm::rotate(model, rotation.y, glm::vec3(0,1,0));
        model = glm::rotate(model, rotation.x, glm::vec3(1,0,0));
        model = glm::rotate(model, rotation.z, glm::vec3(0,0,1));
        model = glm::scale(model, scale);


        glm::mat4 projection = glm::perspective(
            glm::radians(60.0f),
            (float)width / (float)height,
            0.1f,
            100.0f
        );
        

        
        glClearColor(CLEAR_COLOR.r, CLEAR_COLOR.g, CLEAR_COLOR.b, CLEAR_COLOR.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        
        
        // Plane
        
        planeShader.Activate();
        planeShader.SetVec3(planeCameraID, camera.position);
        planeShader.SetMat4(planeVP_ID, camera.matrix);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_DEPTH_TEST);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // OBJ
        glPolygonMode(GL_FRONT_AND_BACK, debug ? GL_LINE : GL_FILL);
        shaderProgram.Activate();
        shaderProgram.SetMat4(modelID, model);
        shaderProgram.SetMat4(viewProjID, camera.matrix);

        //cyl.Draw(shaderProgram, camera);
        myCube.Draw(shaderProgram, camera);
        
        //Axis
        axisVAO.Bind();
        glUniformMatrix4fv(viewProjID, 1, GL_FALSE, glm::value_ptr(camera.matrix));
        glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(identity));
        glDrawArrays(GL_LINES, 0, 6);

        // Axis Arrows
        shaderProgram.SetMat4(viewProjID, camera.matrix);
        shaderProgram.SetMat4(modelID, identity);
        arrowsModel.Draw(shaderProgram, camera);
        
        




        SwapBuffers(hdc);
        

        /*
        update();
        renderer.begin();
        render(renderer);
        renderer.end();
        */
    }


    // Liberação de recursos

    axisVBO.Delete();
    shaderProgram.Delete();
    
    return EXIT_SUCCESS;
}