#ifndef VAO_SETUP_H
#define VAO_SETUP_H

#include "globals.h"

// 生成并绑定 Cylinder VAO/VBO/EBO
void setupCylinderVAO();

// 生成并绑定 Sphere VAO/VBO/EBO
void setupSphereVAO();

// 生成并绑定 Torus VAO/VBO/EBO
void setupTorusVAO(float ringRadius, float tubeRadius,
    GLuint& outVAO, GLuint& outVBOpos, GLuint& outVBOnorm,
    GLuint& outEBO, GLsizei& outIndexCount);

// 生成并绑定 Cube VAO/VBO/EBO
void setupCubeVAO();

// 生成并绑定 Gear VAO/VBO/EBO
void setupGearVAO(int teethCount, float r0, float h, float thickness,
    GLuint& outVAO, GLuint& outVBOpos, GLuint& outVBOnorm,
    GLuint& outEBO, GLsizei& outIndexCount);

#endif // VAO_SETUP_H
