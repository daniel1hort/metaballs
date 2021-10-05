
#ifndef _SHADER_H_
#define _SHADER_H_

#include <windows.h>
#include <gl/gl.h>
#include <gl/glext.h>
#include <load.h>

BOOL LoadShader(GLuint programID, const char* filePathVert, const char* filePathFrag, GLExtFunctions gl);

#endif