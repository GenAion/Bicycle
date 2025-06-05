#ifndef SHADERS_H
#define SHADERS_H

#include <GL/glew.h>

// ����һ�� GLSL shader
GLuint compileShader(GLenum type, const char* src);

// �������� shader��vertex + fragment����һ�� program
GLuint linkProgram(GLuint vs, GLuint fs);

// ��ʼ��������/���Ӷ�����ɫ����Ƭ����ɫ��
void initShaders();

#endif // SHADERS_H
