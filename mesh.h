#ifndef MESH_H
#define MESH_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

// 1) ���� UV ����
void buildSphereMesh(int latitudeBands, int longitudeBands,
    std::vector<float>& outPositions,
    std::vector<float>& outNormals,
    std::vector<GLuint>& outIndices);

// 2) ���ɵ�λԲ�� (�������� z=0, �������� z=1, �뾶=1)
void buildCylinderMesh(int radialSegments, int heightSegments,
    std::vector<float>& outPositions,
    std::vector<float>& outNormals,
    std::vector<GLuint>& outIndices);

// 3) ����Բ�� (������̥/��Ȧ)
void buildTorusMesh(float ringRadius, float tubeRadius,
    int ringSegments, int tubeSegments,
    std::vector<float>& outPositions,
    std::vector<float>& outNormals,
    std::vector<GLuint>& outIndices);

// 4) ���ɵ�λ������ (����̤�����)
void buildCubeMesh(
    std::vector<float>& outPositions,
    std::vector<float>& outNormals,
    std::vector<GLuint>& outIndices);

// 5) ���� 3D ���� (extruded gear)
void buildGearMesh(int teethCount, float r0, float h, float thickness,
    std::vector<float>& outPositions,
    std::vector<float>& outNormals,
    std::vector<GLuint>& outIndices);

#endif // MESH_H
