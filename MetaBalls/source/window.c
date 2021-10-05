
#include <window.h>

BOOL MakeWindow(PWindowHandles handles, WNDPROC WndProc) {
    WNDCLASSEX wcx;

    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc = WndProc;
    wcx.cbClsExtra = 0;
    wcx.cbWndExtra = 0;
    wcx.hInstance = handles->instanceHandle;
    wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = GetStockObject(WHITE_BRUSH);
    wcx.lpszMenuName = "MainMenu";
    wcx.lpszClassName = "MainWClass";
    wcx.hIconSm = LoadImage(
        handles->instanceHandle,
        MAKEINTRESOURCE(5),
        IMAGE_ICON,
        GetSystemMetrics(SM_CXSMICON),
        GetSystemMetrics(SM_CYSMICON),
        LR_DEFAULTCOLOR);

    if (!RegisterClassEx(&wcx)) {
        return FALSE;
    }

    handles->windowHandle = CreateWindow(
        "MainWClass",
        "Sick cunt",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1280,
        720,
        (HWND)NULL,
        (HMENU)NULL,
        handles->instanceHandle,
        (LPVOID)NULL);

    if (!handles->windowHandle)
        return FALSE;

    ShowWindow(handles->windowHandle, TRUE);
    UpdateWindow(handles->windowHandle);
    return TRUE;
}

BOOL AddOpenGL(PWindowHandles handles) {
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,     // Flags
        PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
        32,                   // Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,                   // Number of bits for the depthbuffer
        8,                    // Number of bits for the stencilbuffer
        0,                    // Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    handles->deviceHandle = GetDC(handles->windowHandle);
    int pixelFormat = ChoosePixelFormat(handles->deviceHandle, &pfd);
    SetPixelFormat(handles->deviceHandle, pixelFormat, &pfd);
    handles->rederContextHandle = wglCreateContext(handles->deviceHandle);
    return wglMakeCurrent(handles->deviceHandle, handles->rederContextHandle);
}