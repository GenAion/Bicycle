#ifndef SHADERS_H
#define SHADERS_H

#include <GL/glew.h>

// 编译一个 GLSL shader
GLuint compileShader(GLenum type, const char* src);

// 链接两个 shader（vertex + fragment）成一个 program
GLuint linkProgram(GLuint vs, GLuint fs);

// 初始化并编译/链接顶点着色器、片段着色器
void initShaders();

#endif // SHADERS_H
