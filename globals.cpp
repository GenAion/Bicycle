#include "globals.h"
#include <glm/gtc/matrix_transform.hpp> // 用于 glm::mix

//================================================================================
// 动画状态
//================================================================================
bool   running = false;
double g_crankAngle = 0.0;
float  g_wheelAngle = 0.0f;
double g_chainOff = 0.0;

//================================================================================
// 方向/座椅调整
//================================================================================
double steerDeg = 0.0;
float  seatShift = 0.0f;

//================================================================================
// 摄像机/窗口
//================================================================================
int    windowW = 960;
int    windowH = 600;
float  camAngleX = -30.0f;
float  camAngleY = 25.0f;
float  camDist = 1.5f;
int    lastMouseX = -1;
int    lastMouseY = -1;

//================================================================================
// 着色器/VAO 全局
//================================================================================
GLuint gShaderProgram = 0;

// Cylinder
GLuint  gVAO_Cylinder = 0, gVBO_CylPos = 0, gVBO_CylNorm = 0, gEBO_Cyl = 0;
GLsizei gCylIndexCount = 0;

// Sphere
GLuint  gVAO_Sphere = 0, gVBO_SphPos = 0, gVBO_SphNorm = 0, gEBO_Sph = 0;
GLsizei gSphIndexCount = 0;

// Torus
GLuint  gVAO_Tire = 0, gVBO_TirePos = 0, gVBO_TireNorm = 0, gEBO_Tire = 0;
GLsizei gTireIndexCount = 0;
GLuint  gVAO_Rim = 0, gVBO_RimPos = 0, gVBO_RimNorm = 0, gEBO_Rim = 0;
GLsizei gRimIndexCount = 0;

// Cube
GLuint  gVAO_Cube = 0, gVBO_CubePos = 0, gVBO_CubeNorm = 0, gEBO_Cube = 0;
GLsizei gCubeIndexCount = 0;

// Chainring
GLuint  gVAO_Chainring = 0, gVBO_CRPos = 0, gVBO_CRNorm = 0, gEBO_CR = 0;
GLsizei gCRIndexCount = 0;
// Sprocket
GLuint  gVAO_Sprocket = 0, gVBO_SRPos = 0, gVBO_SRNorm = 0, gEBO_SR = 0;
GLsizei gSRIndexCount = 0;

//================================================================================
// 光照/视图/材质
//================================================================================
glm::vec3 lightPos(0.0f, 1.0f, 1.0f);
glm::vec3 viewPos(0.0f, 1.0f, 1.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

//================================================================================
// 关键点
//================================================================================
const glm::vec3 P_A = glm::vec3(REAR_X, 0.0f, R_WHEEL);   // 后轮轴心
const glm::vec3 P_F = glm::vec3(FRONT_X, 0.0f, R_WHEEL);  // 前轮轴心
const glm::vec3 P_B = glm::vec3(BB_X, 0.0f, BB_Z);        // 中轴
const glm::vec3 P_C = glm::vec3(0.23f, 0.0f, HEAD_L);     // 立管底部
const glm::vec3 P_D = glm::vec3(0.20f, 0.0f, HEAD_H);     // 立管顶部
const glm::vec3 H = P_D + glm::vec3(0.0f, 0.0f, HANDLE_UP); // 把手中心
const glm::vec3 P_S = glm::vec3(BB_X, 0.0f, SEAT_Z);      // 座杆底部
const glm::vec3 P_FS = glm::mix(P_C, P_D, FORK_SPLIT);        // 立管分叉点 (glm::mix 来自 <glm/gtc/matrix_transform.hpp>)
