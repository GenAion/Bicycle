#include <GL/glew.h>
#include <GL/freeglut.h>

#include "globals.h"
#include "shaders.h"
#include "vao_setup.h"
#include "callbacks.h"
#include "parts.h"

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    // 默认兼容 Profile；若要 Core Profile，可加：
    // glutInitContextVersion(3,3);
    // glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glEnable(GLUT_MULTISAMPLE);
    glutInitWindowSize(windowW, windowH);
    glutCreateWindow("3-D Bicycle (Gears & Chain Animated)");

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // 初始化 Chain 数据
    Chain::init();

    // 初始化 OpenGL 状态 + 网格 + 着色器
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // 固定光照参数 (着色器里主要计算)
    float pos[] = { 0.4f, 0.8f, 1.0f, 0.0f };
    float dif[] = { 1, 1, 1, 1 };
    float amb[] = { 0.25f, 0.25f, 0.25f, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);

    glClearColor(1, 1, 1, 1);

    // 编译/链接着色器
    initShaders();

    // 初始化各 VAO
    setupCylinderVAO();
    setupSphereVAO();
    setupCubeVAO();
    // 轮胎 (主半径=R_WHEEL-0.012, 管径=0.012)
    setupTorusVAO(R_WHEEL - 0.012f, 0.012f,
        gVAO_Tire, gVBO_TirePos, gVBO_TireNorm, gEBO_Tire, gTireIndexCount);
    // 轮圈 (主半径=R_WHEEL-0.03, 管径=0.006)
    setupTorusVAO(R_WHEEL - 0.03f, 0.006f,
        gVAO_Rim, gVBO_RimPos, gVBO_RimNorm, gEBO_Rim, gRimIndexCount);

    // Chainring：24 齿，基圆 R_CHAINRING，齿顶高 0.005，厚度 0.01
    setupGearVAO(24, R_CHAINRING, 0.005f, 0.01f,
        gVAO_Chainring, gVBO_CRPos, gVBO_CRNorm, gEBO_CR, gCRIndexCount);
    // Sprocket：24 齿，基圆 R_SPROCKET，齿顶高 0.002，厚度 0.008
    setupGearVAO(24, R_SPROCKET, 0.002f, 0.008f,
        gVAO_Sprocket, gVBO_SRPos, gVBO_SRNorm, gEBO_SR, gSRIndexCount);

    // 注册回调
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, tick, 0);

    glutMainLoop();
    return 0;
}
