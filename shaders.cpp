#include "shaders.h"
#include <cstdio>

//================================================================================
// GLSL 着色器源代码
//================================================================================
static const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 uMVP;
uniform mat4 uModelView;
uniform mat3 uNormalMatrix;

out vec3 vNormal;
out vec3 vFragPos;

void main() {
    vFragPos = vec3(uModelView * vec4(aPos, 1.0));
    vNormal  = normalize(uNormalMatrix * aNormal);
    gl_Position = uMVP * vec4(aPos, 1.0);
}
)";

static const char* fragmentShaderSrc = R"(
#version 330 core
in vec3 vNormal;
in vec3 vFragPos;

out vec4 FragColor;

uniform vec3 uLightPos;     // 视空间位置
uniform vec3 uViewPos;      // 视空间位置
uniform vec3 uLightColor;
uniform vec3 uObjectColor;

void main() {
    // Ambient
    vec3 ambient = 0.1 * uLightColor;

    // Diffuse
    vec3 N = normalize(vNormal);
    vec3 L = normalize(uLightPos - vFragPos);
    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = diff * uLightColor;

    // Specular (Blinn-Phong)
    vec3 V = normalize(uViewPos - vFragPos);
    vec3 H = normalize(L + V);
    float spec = pow(max(dot(N, H), 0.0), 32.0);
    vec3 specular = spec * uLightColor;

    vec3 result = (ambient + diffuse + specular) * uObjectColor;
    FragColor = vec4(result, 1.0);
}
)";

//================================================================================
// 编译一个单独的 shader
//================================================================================
GLuint compileShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        fprintf(stderr, "Shader Compile Error (%d): %s\n", type, log);
    }
    return shader;
}

//================================================================================
// 链接 program
//================================================================================
GLuint linkProgram(GLuint vs, GLuint fs) {
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);
    GLint success;
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(prog, 512, nullptr, log);
        fprintf(stderr, "Program Link Error: %s\n", log);
    }
    return prog;
}

//================================================================================
// 初始化并链接顶点/片段着色器
//================================================================================
void initShaders() {
    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
    GLuint program = linkProgram(vs, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    // 将链接好的 program 存入全局变量
    extern GLuint gShaderProgram;
    gShaderProgram = program;
}
