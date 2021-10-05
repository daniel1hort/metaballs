// MetaBalls.cpp : Defines the entry point for the application.
//

#include "MetaBalls.h"

WindowHandles handles;
GLExtFunctions gl;
GLfloat aspectRatio = 1280.0f/720.0f;


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE: {
        DestroyWindow(hwnd);
        exit(0);
    }
    case WM_SIZE: {
        aspectRatio = (float)LOWORD(lParam) / (float)HIWORD(lParam);
        glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
        break;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

#ifndef RAND_PRECIZION
#define RAND_PRECISION 32767 // the bigger the merrier
#define RAND_PRECIZIONf 32767.0f
// random value between 0 and 1 
float sampled_random() { return (rand() % RAND_PRECISION / RAND_PRECIZIONf); }
// random value between -1 and 1
#define sampled_randomN() (sampled_random() * 2.0f - 1.0f)
#endif

// maximum between 2 numeric values
#define max(a, b) (((a) > (b))?(a):(b))
// minimum between 2 numeric values
#define min(a, b) (((a) > (b))?(b):(a))
// if a < b then returns b
// if a > c then returns c
// else (b <= a <= c) return a
#define clamp(a, b, c) min(max(a, b), c)
#define CIRCLE_COUNT_MAX 1000

int main()
{
    printf("Hello world!\n");
    srand(time(NULL));

    /*-----------------------------------------------------------------------------------------------------*/

    GLuint programID;
    GLint deltaTimeUniformID,
        elapsedTimeUniformID,
        aspectRatioUniformID,
        circlesUniformID,
        circleCountUniformID;
    GLfloat deltaTime;
    DWORD lastTimeValue, now;
    float circles[3*CIRCLE_COUNT_MAX] = {0};
    float circlesVelocities[2*CIRCLE_COUNT_MAX] = { 0 };
    int circleCount = 4;

    MakeWindow(&handles, WndProc);
    AddOpenGL(&handles);
    printf("openGL version: %s\n\n", (char*)glGetString(GL_VERSION));
    LoadGLExtFunctions(&gl);
    programID = gl.CreateProgram();
    LoadShader(programID, "../../../../MetaBalls/test.vert", "../../../../MetaBalls/test.frag", gl);
    
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    deltaTimeUniformID = gl.GetUniformLocation(programID, "deltaTime");
    elapsedTimeUniformID = gl.GetUniformLocation(programID, "elapsedTime");
    aspectRatioUniformID = gl.GetUniformLocation(programID, "aspectRatio");
    circlesUniformID = gl.GetUniformLocation(programID, "circles");
    circleCountUniformID = gl.GetUniformLocation(programID, "circleCount");

    lastTimeValue = timeGetTime();
    circleCount = 10;
    for (int i = 0; i < circleCount; i++) {
        circles[3 * i] = sampled_random();
        circles[3 * i + 1] = sampled_random();
        circles[3 * i + 2] = sampled_random() * 0.1f + 0.05f;
    }

    for (int i = 0; i < circleCount * 2; i++) {
        circlesVelocities[i] = sampled_randomN() * 0.2;
    }


    MSG msg;
    while (TRUE) {
        if (PeekMessage(&msg, handles.windowHandle, 0, 0, PM_NOREMOVE)) {
            GetMessage(&msg, (HWND)NULL, 0, 0);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        now = timeGetTime();
        deltaTime = (float)(now - lastTimeValue) * 0.001;
        lastTimeValue = now;

        for (int i = 0; i < circleCount; i++) {
            float newX, newY, r;
            r = circles[3 * i + 2];
            newX = circles[3 * i] + circlesVelocities[2 * i] * deltaTime;
            newY = circles[3 * i + 1] + circlesVelocities[2 * i + 1] * deltaTime;
            if (newX > 1.0f - r || newX < 0.0f + r) circlesVelocities[2 * i] *= -1.0f;
            if (newY > 1.0f - r || newY < 0.0f + r) circlesVelocities[2 * i + 1] *= -1.0f;
            circles[3 * i] = clamp(newX, 0.0f + r, 1.0f - r);
            circles[3 * i + 1] = clamp(newY, 0.0f + r, 1.0f - r);
        }

        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);
        gl.Uniform1f(deltaTimeUniformID, deltaTime);
        gl.Uniform1f(elapsedTimeUniformID, (GLfloat)lastTimeValue * 0.001);
        gl.Uniform1i(circleCountUniformID, circleCount);
        gl.Uniform3fv(circlesUniformID, CIRCLE_COUNT_MAX, circles);
        gl.Uniform1f(aspectRatioUniformID, aspectRatio);
        gl.UseProgram(programID);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glLoadIdentity();
        SwapBuffers(handles.deviceHandle);
    }

	return 0;
}
