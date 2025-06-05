#include "callbacks.h"
#include "globals.h"
#include "parts.h"
#include <GL/freeglut.h> // 用于 GLUT 回调函数原型
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <iostream>
//================================================================================
// reshape: 窗口大小改变时调用
//================================================================================
void reshape(int w, int h) {
    windowW = w;
    windowH = h;
    glViewport(0, 0, w, h);
}

//================================================================================
// mouseButton: 鼠标按键/释放回调
//================================================================================
void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        running = !running;
    }
    if (state == GLUT_UP) {
        lastMouseX = lastMouseY = -1;
    }
}

//================================================================================
// mouseMotion: 鼠标拖动回调
//================================================================================
void mouseMotion(int x, int y) {
    if (lastMouseX >= 0) {
        int dx = x - lastMouseX;
        int dy = y - lastMouseY;
        camAngleY += dx * 0.4f;
        camAngleX += dy * 0.4f;
        glutPostRedisplay();
    }
    lastMouseX = x;
    lastMouseY = y;
}

//================================================================================
// keyboard: 键盘回调
//================================================================================
void keyboard(unsigned char key, int, int) {
    if (key == 'a' || key == 'A') {
        steerDeg = std::max(steerDeg - 5.0, -45.0);
    }
    else if (key == 'd' || key == 'D') {
        steerDeg = std::min(steerDeg + 5.0, 45.0);
    }
    else if (key == 'w' || key == 'W') {
        seatShift = std::min(seatShift + 0.01f, 0.12f);
    }
    else if (key == 's' || key == 'S') {
        seatShift = std::max(seatShift - 0.01f, 0.0f);
    }
    glutPostRedisplay();
}

//================================================================================
// tick: 定时器回调，用于更新动画状态
//================================================================================
void tick(int) {
    if (running) {
        constexpr double SPD = 4.0;
        static double tot = 0.0;
        tot += SPD;
        // g_crankAngle 随 tot 增加 (度数)
        g_crankAngle = fmod(tot, 360.0);
        // 计算链条偏移
        double s = tot * PI / 180.0 * R_CHAINRING;
        g_chainOff = fmod(s / Chain::L_tot, 1.0);
        // 计算车轮角度 (度数)
        g_wheelAngle = static_cast<float>(fmod(s / R_WHEEL * 180.0 / PI, 360.0));
    }
    glutPostRedisplay();
    glutTimerFunc(16, tick, 0);
}

//================================================================================
// display: 渲染入口
//================================================================================
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //----- Projection & View -----
    glm::mat4 proj = glm::perspective(glm::radians(45.0f),
        static_cast<float>(windowW) / windowH,
        0.1f, 100.0f);
    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -camDist));
    view = glm::rotate(view, glm::radians(camAngleX), glm::vec3(1, 0, 0));
    view = glm::rotate(view, glm::radians(camAngleY), glm::vec3(0, 1, 0));
    viewPos = glm::vec3(glm::inverse(view)[3]);

    //----- 1) 后轮 -----
    drawWheel(P_A, g_wheelAngle, true, view, proj);

    //----- 2) 车架主体 + 座椅 + 曲柄 + 链条 -----
    drawFrame(view, proj);
    drawSeat(view, proj);
    drawCrank(view, proj);
    Chain::draw(g_chainOff, view, proj);

    //----- 3) 前叉 + 车把 + 前轮 (随 steerDeg 转向) -----
    {
        glm::mat4 T1 = glm::translate(glm::mat4(1.0f), P_C);
        glm::mat4 R = glm::rotate(glm::mat4(1.0f),
            glm::radians(static_cast<float>(steerDeg)),
            glm::vec3(0, 0, 1));
        glm::mat4 T2 = glm::translate(glm::mat4(1.0f), -P_C);
        glm::mat4 model = T1 * R * T2;

        // 视图中先乘入转向矩阵
        glm::mat4 view2 = view * model;

        drawForkAndHandle(view2, proj);
        // !!! 关键修改：让前轮也使用 view2 !!!
        drawWheel(P_F, g_wheelAngle, false, view2, proj);
    }

    glutSwapBuffers();
}
