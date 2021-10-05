
#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>

typedef struct {
	HINSTANCE instanceHandle;
	HWND windowHandle;
	HGLRC rederContextHandle;
	HDC deviceHandle;
} WindowHandles, *PWindowHandles;

BOOL MakeWindow(PWindowHandles handles, WNDPROC WndProc);
BOOL AddOpenGL(PWindowHandles handles);

#endif