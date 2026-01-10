
#ifndef UNICODE
#define UNICODE
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            wprintf(L"WM_CREATE\n");
            break;
        case WM_MOVE:
            wprintf(L"WM_MOVE\n");
            break;
        case WM_SIZE:
            wprintf(L"WM_SIZE\n");
            break;
        case WM_DESTROY:
            PostQuitMessage(EXIT_SUCCESS);
            return EXIT_SUCCESS;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
    
    if (!AllocConsole()) {
        return EXIT_FAILURE;
    }

    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);

    wprintf(L"hInstance: %p\n", hInstance);
    wprintf(L"lpCmdLine: %hs\n", lpCmdLine);
    wprintf(L"nCmdShow: %d\n", nCmdShow);

    

    const wchar_t* CLASS_NAME = TEXT("WindowClass");

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);
    

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        TEXT("Janela"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, // x position
        CW_USEDEFAULT, // y position
        CW_USEDEFAULT, // width
        CW_USEDEFAULT, // height
        NULL, // Parent window
        NULL, // Menu
        hInstance, // Instance Handle,
        NULL
    );

    if (hwnd == NULL) {
        return EXIT_FAILURE;
    }

    ShowWindow(hwnd, nCmdShow);


    MSG msg = { 0 };

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return EXIT_SUCCESS;


}