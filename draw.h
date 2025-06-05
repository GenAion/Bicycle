#ifndef DRAW_H
#define DRAW_H

#include <GL/glew.h>
#include <glm/glm.hpp>

// ͨ�û��ƣ��� VAO���ϴ� MVP/ModelView/NormalMatrix/Color/���գ�DrawElements
void renderMesh(GLuint VAO, GLsizei indexCount,
    const glm::mat4& model, const glm::vec3& objectColor,
    const glm::mat4& view, const glm::mat4& proj);

// ����Բ������ p1 �� p2���뾶 r����ɫ objectColor
void drawCylinder(const glm::vec3& p1, const glm::vec3& p2, float r,
    const glm::vec3& objectColor,
    const glm::mat4& view, const glm::mat4& proj);

// �������壺���� center, �뾶 r, ��ɫ objectColor
void drawSphere(const glm::vec3& center, float r,
    const glm::vec3& objectColor,
    const glm::mat4& view, const glm::mat4& proj);

// ���� Torus (��̥/��Ȧ)���ȸ� model ��һ���� X �� -90�� ����ת
void drawTorus(GLuint VAO, GLsizei indexCount,
    const glm::mat4& model, const glm::vec3& objectColor,
    const glm::mat4& view, const glm::mat4& proj);

#endif // DRAW_H
