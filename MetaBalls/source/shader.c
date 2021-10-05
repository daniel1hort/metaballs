
#include <shader.h>

BOOL LoadShader(GLuint programID, const char* filePathVert, const char* filePathFrag, GLExtFunctions gl) {
    HANDLE fileHandle;
    char bufferVert[1024];
    char bufferFrag[4096];
    char* bufferPointerVert = bufferVert;
    char* bufferPointerFrag = bufferFrag;
    int bytesCount;
    GLuint shaderIDVert = gl.CreateShader(GL_VERTEX_SHADER);
    GLuint shaderIDFrag = gl.CreateShader(GL_FRAGMENT_SHADER);

    fileHandle = CreateFile(filePathVert, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        printf("file \"%s\" not found\n", filePathVert);
        return FALSE;
    }
    memset(bufferVert, 0, 1024);
    if (!ReadFile(fileHandle, bufferVert, 1023, &bytesCount, NULL)) {
        printf("something went wrong at reading");
    }
    CloseHandle(fileHandle);

    fileHandle = CreateFile(filePathFrag, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        printf("file \"%s\" not found\n", filePathFrag);
        return FALSE;
    }
    memset(bufferFrag, 0, 4096);
    if (!ReadFile(fileHandle, bufferFrag, 4095, &bytesCount, NULL)) {
        printf("something went wrong at reading");
    }
    CloseHandle(fileHandle);

    GLint result = GL_FALSE;
    int length;

    printf("compiling shader\n");
    gl.ShaderSource(shaderIDVert, 1, &bufferPointerVert, NULL);
    gl.CompileShader(shaderIDVert);
    gl.GetShaderiv(shaderIDVert, GL_COMPILE_STATUS, &result);
    gl.GetShaderiv(shaderIDVert, GL_INFO_LOG_LENGTH, &length);
    if (result == GL_FALSE) {
        gl.GetShaderInfoLog(shaderIDVert, 1023, NULL, bufferVert);
        printf("%s\n", bufferVert);
        return FALSE;
    }

    printf("compiling shader\n");
    gl.ShaderSource(shaderIDFrag, 1, &bufferPointerFrag, NULL);
    gl.CompileShader(shaderIDFrag);
    gl.GetShaderiv(shaderIDFrag, GL_COMPILE_STATUS, &result);
    gl.GetShaderiv(shaderIDFrag, GL_INFO_LOG_LENGTH, &length);
    if (result == GL_FALSE) {
        gl.GetShaderInfoLog(shaderIDFrag, 1023, NULL, bufferFrag);
        printf("%s\n", bufferFrag);
        return FALSE;
    }

    gl.AttachShader(programID, shaderIDVert);
    gl.AttachShader(programID, shaderIDFrag);
    gl.LinkProgram(programID);
    gl.GetProgramiv(programID, GL_LINK_STATUS, &result);
    gl.GetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);
    if (result == GL_FALSE) {
        printf("something went wrong at attaching");
        return FALSE;
    }

    gl.DetachShader(programID, shaderIDVert);
    gl.DetachShader(programID, shaderIDFrag);
    gl.DeleteShader(shaderIDVert);
    gl.DeleteShader(shaderIDFrag);
    return TRUE;
}