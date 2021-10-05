
#include <load.h>

void LoadGLExtFunctions(PGLExtFunctions glExt) {
    glExt->GenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
    glExt->BindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
    glExt->GenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
    glExt->BindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
    glExt->BufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
    glExt->EnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
    glExt->VertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
    glExt->DisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");

    glExt->CreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
    glExt->ShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
    glExt->CompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
    glExt->GetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
    glExt->GetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
    glExt->CreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
    glExt->AttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
    glExt->LinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
    glExt->GetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
    glExt->GetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
    glExt->DetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
    glExt->DeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
    glExt->UseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");

    glExt->GetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
    glExt->UniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
    glExt->Uniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
    glExt->Uniform3f = (PFNGLUNIFORM3FPROC)wglGetProcAddress ("glUniform3f");
    glExt->Uniform2f = (PFNGLUNIFORM2FPROC)wglGetProcAddress("glUniform2f");
    glExt->Uniform2fv = (PFNGLUNIFORM2FVPROC)wglGetProcAddress("glUniform2fv");
    glExt->Uniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
    glExt->Uniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
    glExt->PointParameteri = (PFNGLPOINTPARAMETERIPROC)wglGetProcAddress("glPointParameteri");
}