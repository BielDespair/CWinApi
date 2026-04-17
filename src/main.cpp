
#ifndef UNICODE
#define UNICODE
#endif


#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>


#include <glad/glad.h>
#include <Windows.h>

#include <math/vector.hh>
#include <render/renderer.hh>
#include <game.hh>
#include <graphics/triangulation.hh>
#include <render/Shader.hh>

#include <render/VAO.hh>
#include <render/VBO.hh>
#include <render/EBO.hh>

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
    case WM_DESTROY:
        PostQuitMessage(EXIT_SUCCESS);
        return EXIT_SUCCESS;
    case WM_KEYDOWN:
        switch (wParam) {
            case VK_LEFT:
                angleX -= 0.05f;
                break;
            case VK_RIGHT:
                angleX += 0.05f;
                break;
        }
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


    // Unbind do estado global (para evitar conflitos)
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    bool running = true;
    while (running)
    {
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

        
        float c = cos(angleX);
        float s = sin(angleX);

        float model[] = {
            1, 0, 0, 0,
            0, c, s, 0,
            0,-s, c, 0,
            0, 0, 0, 1
        };
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Activate();
        GLint loc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(loc, 1, GL_TRUE, model);

        VAO1.Bind();
        glEnable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);
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
    EBO1.Delete();
    shaderProgram.Delete();
    
    return EXIT_SUCCESS;
}