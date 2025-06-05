#ifndef GLOBALS_H
#define GLOBALS_H

#include <GL/glew.h>
#include <glm/glm.hpp>

//================================================================================
// ȫ�ֳ�����constexpr ����ֱ�ӷ���ͷ�ļ��У�
//================================================================================
constexpr float PI = 3.14159265358979323846f;
constexpr float SCALE = 1.0f;

// ���������鼸�β���
constexpr float R_WHEEL = 0.12f;      // �ְ뾶
constexpr float REAR_X = -0.28f, FRONT_X = 0.28f;
constexpr float BB_X = -0.05f, BB_Z = 0.16f;
constexpr float HEAD_L = 0.23f, HEAD_H = 0.38f;
constexpr float SEAT_Z = 0.33f, HANDLE_UP = 0.04f;

// �����ߴ�
constexpr float VERT_LEN = 0.06f, HORIZ_LEN = 0.08f, OFFSET_X = 0.01f;

// ��������������
constexpr float R_CHAINRING = 0.06f, R_SPROCKET = 0.015f;
constexpr int   LINK_CNT = 90;
constexpr float LINK_LEN = 0.012f, PIN_R = 0.0022f;

// ����/����ƫ��
constexpr float FORK_Y = 0.03f;
constexpr float FORK_SPLIT = 0.45f;

// Tessellation �������˴���ʹ�� Tessellation��ֻ������ϸ�֣�
constexpr int SEGMENTS_CYLINDER = 32;   // Բ��Բ����Ƭ
constexpr int SEGMENTS_SPHERE = 32;     // ���γ��/����
constexpr int SEGMENTS_TORUS_R = 32;    // Բ������̥/��Ȧ��������Ƭ
constexpr int SEGMENTS_TORUS_T = 32;    // Բ��������Ƭ

//================================================================================
// ȫ�ֱ�������
//================================================================================
// ����״̬
extern bool   running;
extern double g_crankAngle;
extern float  g_wheelAngle;
extern double g_chainOff;

// ����/���ε���
extern double steerDeg;
extern float  seatShift;

// �����/����
extern int    windowW, windowH;
extern float  camAngleX, camAngleY, camDist;
extern int    lastMouseX, lastMouseY;

// ��ɫ��/VAO ȫ��
extern GLuint gShaderProgram;

// Cylinder (���ڴ����Բ������)
extern GLuint  gVAO_Cylinder, gVBO_CylPos, gVBO_CylNorm, gEBO_Cyl;
extern GLsizei gCylIndexCount;

// Sphere (�������桢������̤����ӵ�)
extern GLuint  gVAO_Sphere, gVBO_SphPos, gVBO_SphNorm, gEBO_Sph;
extern GLsizei gSphIndexCount;

// Torus (������̥/��Ȧ)
extern GLuint  gVAO_Tire, gVBO_TirePos, gVBO_TireNorm, gEBO_Tire;
extern GLsizei gTireIndexCount;
extern GLuint  gVAO_Rim, gVBO_RimPos, gVBO_RimNorm, gEBO_Rim;
extern GLsizei gRimIndexCount;

// Cube (����̤�����)
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
// ����/��ͼ/����
//================================================================================
extern glm::vec3 lightPos;
extern glm::vec3 viewPos;
extern glm::vec3 lightColor;

//================================================================================
// �ؼ��� (glm::vec3)
//================================================================================
extern const glm::vec3 P_A;   // ��������
extern const glm::vec3 P_F;   // ǰ������
extern const glm::vec3 P_B;   // ����
extern const glm::vec3 P_C;   // ���ܵײ�
extern const glm::vec3 P_D;   // ���ܶ���
extern const glm::vec3 H;     // ��������
extern const glm::vec3 P_S;   // ���˵ײ�
extern const glm::vec3 P_FS;  // ���ֲܷ��

#endif // GLOBALS_H
