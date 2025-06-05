#ifndef MESH_H
#define MESH_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

// 1) 生成 UV 球体
void buildSphereMesh(int latitudeBands, int longitudeBands,
    std::vector<float>& outPositions,
    std::vector<float>& outNormals,
    std::vector<GLuint>& outIndices);

// 2) 生成单位圆柱 (底面中心 z=0, 顶面中心 z=1, 半径=1)
void buildCylinderMesh(int radialSegments, int heightSegments,
    std::vector<float>& outPositions,
    std::vector<float>& outNormals,
    std::vector<GLuint>& outIndices);

// 3) 生成圆环 (用于轮胎/轮圈)
void buildTorusMesh(float ringRadius, float tubeRadius,
    int ringSegments, int tubeSegments,
    std::vector<float>& outPositions,
    std::vector<float>& outNormals,
    std::vector<GLuint>& outIndices);

// 4) 生成单位立方体 (用于踏板盒子)
void buildCubeMesh(
    std::vector<float>& outPositions,
    std::vector<float>& outNormals,
    std::vector<GLuint>& outIndices);

// 5) 生成 3D 齿轮 (extruded gear)
void buildGearMesh(int teethCount, float r0, float h, float thickness,
    std::vector<float>& outPositions,
    std::vector<float>& outNormals,
    std::vector<GLuint>& outIndices);

#endif // MESH_H
