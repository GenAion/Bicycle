#include "callbacks.h"
#include "globals.h"
#include "parts.h"
#include <GL/freeglut.h> // ���� GLUT �ص�����ԭ��
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <iostream>
//================================================================================
// reshape: ���ڴ�С�ı�ʱ����
//================================================================================
void reshape(int w, int h) {
    windowW = w;
    windowH = h;
    glViewport(0, 0, w, h);
}

//================================================================================
// mouseButton: ��갴��/�ͷŻص�
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
// mouseMotion: ����϶��ص�
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
// keyboard: ���̻ص�
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
// tick: ��ʱ���ص������ڸ��¶���״̬
//================================================================================
void tick(int) {
    if (running) {
        constexpr double SPD = 4.0;
        static double tot = 0.0;
        tot += SPD;
        // g_crankAngle �� tot ���� (����)
        g_crankAngle = fmod(tot, 360.0);
        // ��������ƫ��
        double s = tot * PI / 180.0 * R_CHAINRING;
        g_chainOff = fmod(s / Chain::L_tot, 1.0);
        // ���㳵�ֽǶ� (����)
        g_wheelAngle = static_cast<float>(fmod(s / R_WHEEL * 180.0 / PI, 360.0));
    }
    glutPostRedisplay();
    glutTimerFunc(16, tick, 0);
}

//================================================================================
// display: ��Ⱦ���
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

    //----- 1) ���� -----
    drawWheel(P_A, g_wheelAngle, true, view, proj);

    //----- 2) �������� + ���� + ���� + ���� -----
    drawFrame(view, proj);
    drawSeat(view, proj);
    drawCrank(view, proj);
    Chain::draw(g_chainOff, view, proj);

    //----- 3) ǰ�� + ���� + ǰ�� (�� steerDeg ת��) -----
    {
        glm::mat4 T1 = glm::translate(glm::mat4(1.0f), P_C);
        glm::mat4 R = glm::rotate(glm::mat4(1.0f),
            glm::radians(static_cast<float>(steerDeg)),
            glm::vec3(0, 0, 1));
        glm::mat4 T2 = glm::translate(glm::mat4(1.0f), -P_C);
        glm::mat4 model = T1 * R * T2;

        // ��ͼ���ȳ���ת�����
        glm::mat4 view2 = view * model;

        drawForkAndHandle(view2, proj);
        // !!! �ؼ��޸ģ���ǰ��Ҳʹ�� view2 !!!
        drawWheel(P_F, g_wheelAngle, false, view2, proj);
    }

    glutSwapBuffers();
}
