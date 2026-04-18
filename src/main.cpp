
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

GLfloat vertices[] = {
    // pos               // color
     0.0f,  0.9f, 0.0f,   1.0f, 0.0f, 0.0f,
     0.35f, 1.0f, 0.0f,   1.0f, 0.2f, 0.0f,
     0.7f,  0.7f, 0.0f,   1.0f, 0.4f, 0.0f,
     0.6f,  0.2f, 0.0f,   1.0f, 0.6f, 0.0f,
     0.3f, -0.2f, 0.0f,   0.8f, 0.8f, 0.0f,
     0.0f, -0.8f, 0.0f,   0.0f, 1.0f, 0.0f,
    -0.3f, -0.2f, 0.0f,   0.0f, 0.8f, 0.2f,
    -0.6f, 0.2f, 0.0f,    0.0f, 0.6f, 0.6f,
    -0.7f, 0.7f, 0.0f,    0.0f, 0.4f, 1.0f,
    -0.35f, 1.0f, 0.0f,   0.5f, 0.2f, 1.0f
};

GLuint indices[] = {
    0, 1, 2,
    0, 2, 3,
    9, 0, 3,
    9, 3, 4,
    9, 4, 5,
    9, 5, 6,
    9, 6, 7,
    7, 8, 9
};





float angleX = 0.0f;
bool keys[256] = {0};

Input input;
Game game(input);

void* GetAnyGLFuncAddress(const char *name)
{
    void *p = (void *)wglGetProcAddress(name);

    if(p == 0 || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1))
    {
        HMODULE module = LoadLibraryA("opengl32.dll");
        p = (void *)GetProcAddress(module, name);
    }
    
    return p;
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
        RECT r;
        GetClientRect(hwnd, &r);
        glViewport(0, 0, r.right, r.bottom);
        break;

    case WM_MOUSEMOVE:
        input.OnMouseMove(LOWORD(lParam), HIWORD(lParam));
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
    gladLoadGL();




    //Renderer renderer = Renderer();
    //renderer.init(hwnd);

    ShowWindow(hwnd, nCmdShow);
    MSG msg = {0};

    RECT r;
    GetClientRect(hwnd, &r);
    glViewport(0, 0, r.right, r.bottom);
    
    Shader shaderProgram = Shader::Shader("basic/basic.glsl", "basic/frag.glsl");
    
    VAO VAO1;
    
    VAO1.Bind();
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // Axis
    VAO axisVAO;
    axisVAO.Bind();

    VBO axisVBO(axis, sizeof(axis));

    axisVAO.LinkAttrib(axisVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    axisVAO.LinkAttrib(axisVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    
    VAO arrowsVAO;
    getArrowsModel(arrows, arrowsIndices);
    arrowsVAO.Bind();
    VBO arrowsVBO(arrows, sizeof(arrows));
    EBO arrowsEBO(arrowsIndices, sizeof(arrowsIndices));
    VAO1.LinkAttrib(arrowsVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(arrowsVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));



    Shader planeShader = Shader::Shader("debug/plane.glsl", "basic/frag.glsl");
    VAO planeVAO;
    planeVAO.Bind();

    // Unbind do estado global (para evitar conflitos)
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint projectionID = glGetUniformLocation(shaderProgram.ID, "projection");
    GLuint viewID = glGetUniformLocation(shaderProgram.ID, "view");
    GLuint modelID = glGetUniformLocation(shaderProgram.ID, "model");

    GLuint planeVP_ID = glGetUniformLocation(planeShader.ID, "gVP");

    
    Player player;
    
    float rotSpeed = 10.1f; // rad/s
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


    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    LARGE_INTEGER last;
    QueryPerformanceCounter(&last);
    while (running)
    {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        float dt = (float)(now.QuadPart - last.QuadPart) / (float)freq.QuadPart;
        last = now;


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


        if (input.IsActionDown(Action::MoveCamera)) {
            ax += input.deltaY * rotSpeed * dt * -1;
            ay += input.deltaX * rotSpeed * dt * -1;
        }
        if (input.IsActionDown(Action::MoveForward)) tz -= rotSpeed * dt;
        if (input.IsActionDown(Action::MoveBackward))tz += rotSpeed * dt;
        if (input.IsActionDown(Action::MoveLeft))  tx += rotSpeed * dt;
        if (input.IsActionDown(Action::MoveRight)) tx -= rotSpeed * dt;

        if (input.IsActionPressed(Action::Debug)) {
            debug = !debug;
            ax = ay = az = tx = ty = tz = player.x = player.y = player.z = 0.0f;
        }

        input.EndFrame();
        
        ax = fmodf(ax, TWO_PI);
        ay = fmodf(ay, TWO_PI);

        glm::vec3 position(tx, ty, tz);
        glm::vec3 rotation(ax, ay, az);
        glm::vec3 scale(1.0f);

        glm::mat4 model(1.0f);


        model = glm::translate(model, position);
        model = glm::rotate(model, rotation.y, glm::vec3(0,1,0));
        model = glm::rotate(model, rotation.x, glm::vec3(1,0,0));
        model = glm::rotate(model, rotation.z, glm::vec3(0,0,1));
        model = glm::scale(model, scale);

        glm::mat4 view = glm::lookAt(
            glm::vec3(0.0f, 10.0f, 0.0f), // camera pos
            glm::vec3(0.0f, 0.0f, 0.0f), // target
            glm::vec3(0.0f, 0.0f, 1.0f)  // up
        );

        glm::mat4 projection = glm::perspective(
            glm::radians(60.0f),
            (float)width / (float)height,
            0.1f,
            100.0f
        );

        glm::mat4 gVP = projection * view;
        gVP = glm::mat4(1.0f);
        

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glPolygonMode(GL_FRONT_AND_BACK, debug ? GL_LINE : GL_FILL);
        glEnable(GL_DEPTH_TEST);

        shaderProgram.Activate();
        VAO1.Bind();
        glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);
        
        //Axis
        axisVAO.Bind();
        glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_LINES, 0, 6);

        // Axis Arrows
        arrowsVAO.Bind();
        glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, sizeof(arrowsIndices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);
        

        // Plane
        planeShader.Activate();
        glPolygonMode(GL_FRONT_AND_BACK, debug ? GL_LINE : GL_FILL);
        planeVAO.Bind();
        glUniformMatrix4fv(planeVP_ID, 1, GL_FALSE, glm::value_ptr(gVP));
        glEnable(GL_DEPTH_TEST);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        SwapBuffers(hdc);
        

        /*
        update();
        renderer.begin();
        render(renderer);
        renderer.end();
        */
    }


    // Liberação de recursos
    VAO1.Delete();
    VBO1.Delete();
    axisVBO.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    
    return EXIT_SUCCESS;
}