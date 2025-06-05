#ifndef GLOBALS_H
#define GLOBALS_H

#include <GL/glew.h>
#include <glm/glm.hpp>

//================================================================================
// 全局常量（constexpr 可以直接放在头文件中）
//================================================================================
constexpr float PI = 3.14159265358979323846f;
constexpr float SCALE = 1.0f;

// 车架与轮组几何参数
constexpr float R_WHEEL = 0.12f;      // 轮半径
constexpr float REAR_X = -0.28f, FRONT_X = 0.28f;
constexpr float BB_X = -0.05f, BB_Z = 0.16f;
constexpr float HEAD_L = 0.23f, HEAD_H = 0.38f;
constexpr float SEAT_Z = 0.33f, HANDLE_UP = 0.04f;

// 曲柄尺寸
constexpr float VERT_LEN = 0.06f, HORIZ_LEN = 0.08f, OFFSET_X = 0.01f;

// 齿轮与链条参数
constexpr float R_CHAINRING = 0.06f, R_SPROCKET = 0.015f;
constexpr int   LINK_CNT = 90;
constexpr float LINK_LEN = 0.012f, PIN_R = 0.0022f;

// 车叉/车把偏移
constexpr float FORK_Y = 0.03f;
constexpr float FORK_SPLIT = 0.45f;

// Tessellation 参数（此处不使用 Tessellation，只做网格细分）
constexpr int SEGMENTS_CYLINDER = 32;   // 圆柱圆周切片
constexpr int SEGMENTS_SPHERE = 32;     // 球的纬线/经线
constexpr int SEGMENTS_TORUS_R = 32;    // 圆环（轮胎/轮圈）主环切片
constexpr int SEGMENTS_TORUS_T = 32;    // 圆环截面切片

//================================================================================
// 全局变量声明
//================================================================================
// 动画状态
extern bool   running;
extern double g_crankAngle;
extern float  g_wheelAngle;
extern double g_chainOff;

// 方向/座椅调整
extern double steerDeg;
extern float  seatShift;

// 摄像机/窗口
extern int    windowW, windowH;
extern float  camAngleX, camAngleY, camDist;
extern int    lastMouseX, lastMouseY;

// 着色器/VAO 全局
extern GLuint gShaderProgram;

// Cylinder (用于大多数圆柱构件)
extern GLuint  gVAO_Cylinder, gVBO_CylPos, gVBO_CylNorm, gEBO_Cyl;
extern GLsizei gCylIndexCount;

// Sphere (用于座垫、简化曲柄踏板盒子等)
extern GLuint  gVAO_Sphere, gVBO_SphPos, gVBO_SphNorm, gEBO_Sph;
extern GLsizei gSphIndexCount;

// Torus (用于轮胎/轮圈)
extern GLuint  gVAO_Tire, gVBO_TirePos, gVBO_TireNorm, gEBO_Tire;
extern GLsizei gTireIndexCount;
extern GLuint  gVAO_Rim, gVBO_RimPos, gVBO_RimNorm, gEBO_Rim;
extern GLsizei gRimIndexCount;

// Cube (用于踏板盒子)
extern GLuint  gVAO_Cube, gVBO_CubePos, gVBO_CubeNorm, gEBO_Cube;
extern GLsizei gCubeIndexCount;

// Gear (chainring + sprocket)
// Chainring
extern GLuint  gVAO_Chainring, gVBO_CRPos, gVBO_CRNorm, gEBO_CR;
extern GLsizei gCRIndexCount;
// Sprocket
extern GLuint  gVAO_Sprocket, gVBO_SRPos, gVBO_SRNorm, gEBO_SR;
extern GLsizei gSRIndexCount;

//================================================================================
// 光照/视图/材质
//================================================================================
extern glm::vec3 lightPos;
extern glm::vec3 viewPos;
extern glm::vec3 lightColor;

//================================================================================
// 关键点 (glm::vec3)
//================================================================================
extern const glm::vec3 P_A;   // 后轮轴心
extern const glm::vec3 P_F;   // 前轮轴心
extern const glm::vec3 P_B;   // 中轴
extern const glm::vec3 P_C;   // 立管底部
extern const glm::vec3 P_D;   // 立管顶部
extern const glm::vec3 H;     // 把手中心
extern const glm::vec3 P_S;   // 座杆底部
extern const glm::vec3 P_FS;  // 立管分叉点

#endif // GLOBALS_H
