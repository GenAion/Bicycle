#include "draw.h"
#include "globals.h"
#include "shaders.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//================================================================================
// 通用绘制：绑定 VAO，上传 MVP/ModelView/NormalMatrix/Color/光照，DrawElements
//================================================================================
void renderMesh(GLuint VAO, GLsizei indexCount,
    const glm::mat4& model, const glm::vec3& objectColor,
    const glm::mat4& view, const glm::mat4& proj)
{
    // 计算 ModelView 和 MVP 矩阵
    glm::mat4 mv = view * model;
    glm::mat4 mvp = proj * mv;
    glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3(mv)));

    // 使用 shader program
    glUseProgram(gShaderProgram);
    GLint locMVP = glGetUniformLocation(gShaderProgram, "uMVP");
    GLint locMV = glGetUniformLocation(gShaderProgram, "uModelView");
    GLint locNM = glGetUniformLocation(gShaderProgram, "uNormalMatrix");
    GLint locObjColor = glGetUniformLocation(gShaderProgram, "uObjectColor");
    GLint locLightPos = glGetUniformLocation(gShaderProgram, "uLightPos");
    GLint locViewPos = glGetUniformLocation(gShaderProgram, "uViewPos");
    GLint locLightCol = glGetUniformLocation(gShaderProgram, "uLightColor");

    glUniformMatrix4fv(locMVP, 1, GL_FALSE, glm::value_ptr(mvp));
    glUniformMatrix4fv(locMV, 1, GL_FALSE, glm::value_ptr(mv));
    glUniformMatrix3fv(locNM, 1, GL_FALSE, glm::value_ptr(normalMat));
    glUniform3fv(locObjColor, 1, glm::value_ptr(objectColor));
    glUniform3fv(locLightPos, 1, glm::value_ptr(lightPos));
    glUniform3fv(locViewPos, 1, glm::value_ptr(viewPos));
    glUniform3fv(locLightCol, 1, glm::value_ptr(lightColor));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glUseProgram(0);
}

//================================================================================
// 绘制圆柱：从 p1 到 p2，半径 r，颜色 objectColor
//================================================================================
void drawCylinder(const glm::vec3& p1, const glm::vec3& p2, float r,
    const glm::vec3& objectColor,
    const glm::mat4& view, const glm::mat4& proj)
{
    glm::vec3 d = p2 - p1;
    float length = glm::length(d);
    if (length < 1e-6f) return;
    glm::vec3 dir = glm::normalize(d);

    // 构造 Model 矩阵：
    //  1) 平移到 p1
    //  2) 绕某轴把 z 轴(0,0,1) 旋转到 dir
    //  3) 缩放：x,y 缩到 r，z 缩到 length
    glm::mat4 model(1.0f);
    model = glm::translate(model, p1);
    glm::vec3 up = glm::vec3(0, 0, 1);
    float cosA = glm::clamp(glm::dot(up, dir), -1.0f, 1.0f);
    float angle = acosf(cosA);
    glm::vec3 axis = glm::cross(up, dir);
    if (glm::length(axis) > 1e-6f) {
        model = glm::rotate(model, angle, axis);
    }
    model = glm::scale(model, glm::vec3(r, r, length));

    renderMesh(gVAO_Cylinder, gCylIndexCount, model, objectColor, view, proj);
}

//================================================================================
// 绘制球体：中心 center, 半径 r, 颜色 objectColor
//================================================================================
void drawSphere(const glm::vec3& center, float r,
    const glm::vec3& objectColor,
    const glm::mat4& view, const glm::mat4& proj)
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, center);
    model = glm::scale(model, glm::vec3(r));
    renderMesh(gVAO_Sphere, gSphIndexCount, model, objectColor, view, proj);
}

//================================================================================
// 绘制 Torus (轮胎/轮圈)：先给 model 加一个绕 X 轴 -90° 的旋转
//================================================================================
void drawTorus(GLuint VAO, GLsizei indexCount,
    const glm::mat4& model, const glm::vec3& objectColor,
    const glm::mat4& view, const glm::mat4& proj)
{
    glm::mat4 rot = glm::rotate(glm::mat4(1.0f),
        glm::radians(-90.0f),
        glm::vec3(1, 0, 0));
    glm::mat4 M = model * rot;
    renderMesh(VAO, indexCount, M, objectColor, view, proj);
}
