#ifndef DRAW_H
#define DRAW_H

#include <GL/glew.h>
#include <glm/glm.hpp>

// 通用绘制：绑定 VAO，上传 MVP/ModelView/NormalMatrix/Color/光照，DrawElements
void renderMesh(GLuint VAO, GLsizei indexCount,
    const glm::mat4& model, const glm::vec3& objectColor,
    const glm::mat4& view, const glm::mat4& proj);

// 绘制圆柱：从 p1 到 p2，半径 r，颜色 objectColor
void drawCylinder(const glm::vec3& p1, const glm::vec3& p2, float r,
    const glm::vec3& objectColor,
    const glm::mat4& view, const glm::mat4& proj);

// 绘制球体：中心 center, 半径 r, 颜色 objectColor
void drawSphere(const glm::vec3& center, float r,
    const glm::vec3& objectColor,
    const glm::mat4& view, const glm::mat4& proj);

// 绘制 Torus (轮胎/轮圈)：先给 model 加一个绕 X 轴 -90° 的旋转
void drawTorus(GLuint VAO, GLsizei indexCount,
    const glm::mat4& model, const glm::vec3& objectColor,
    const glm::mat4& view, const glm::mat4& proj);

#endif // DRAW_H
