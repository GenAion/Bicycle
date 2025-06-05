#ifndef VAO_SETUP_H
#define VAO_SETUP_H

#include "globals.h"

// ���ɲ��� Cylinder VAO/VBO/EBO
void setupCylinderVAO();

// ���ɲ��� Sphere VAO/VBO/EBO
void setupSphereVAO();

// ���ɲ��� Torus VAO/VBO/EBO
void setupTorusVAO(float ringRadius, float tubeRadius,
    GLuint& outVAO, GLuint& outVBOpos, GLuint& outVBOnorm,
    GLuint& outEBO, GLsizei& outIndexCount);

// ���ɲ��� Cube VAO/VBO/EBO
void setupCubeVAO();

// ���ɲ��� Gear VAO/VBO/EBO
void setupGearVAO(int teethCount, float r0, float h, float thickness,
    GLuint& outVAO, GLuint& outVBOpos, GLuint& outVBOnorm,
    GLuint& outEBO, GLsizei& outIndexCount);

#endif // VAO_SETUP_H
