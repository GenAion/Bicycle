#include "mesh.h"
#include "globals.h"
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>

//================================================================================
// 1) 生成 UV 球体
//================================================================================
void buildSphereMesh(int latitudeBands, int longitudeBands,
    std::vector<float>& outPositions,
    std::vector<float>& outNormals,
    std::vector<GLuint>& outIndices)
{
    outPositions.clear();
    outNormals.clear();
    outIndices.clear();

    for (int lat = 0; lat <= latitudeBands; ++lat) {
        float theta = lat * PI / latitudeBands;
        float sinTheta = sinf(theta), cosTheta = cosf(theta);

        for (int lon = 0; lon <= longitudeBands; ++lon) {
            float phi = lon * 2.0f * PI / longitudeBands;
            float sinPhi = sinf(phi), cosPhi = cosf(phi);

            float x = cosPhi * sinTheta;
            float y = cosTheta;
            float z = sinPhi * sinTheta;

            outPositions.push_back(x);
            outPositions.push_back(y);
            outPositions.push_back(z);

            outNormals.push_back(x);
            outNormals.push_back(y);
            outNormals.push_back(z);
        }
    }

    for (int lat = 0; lat < latitudeBands; ++lat) {
        for (int lon = 0; lon < longitudeBands; ++lon) {
            int first = (lat) * (longitudeBands + 1) + lon;
            int second = (lat + 1) * (longitudeBands + 1) + lon;

            outIndices.push_back(first);
            outIndices.push_back(second);
            outIndices.push_back(first + 1);

            outIndices.push_back(second);
            outIndices.push_back(second + 1);
            outIndices.push_back(first + 1);
        }
    }
}

//================================================================================
// 2) 生成单位圆柱 (底面中心 z=0, 顶面中心 z=1, 半径=1)
//================================================================================
void buildCylinderMesh(int radialSegments, int heightSegments,
    std::vector<float>& outPositions,
    std::vector<float>& outNormals,
    std::vector<GLuint>& outIndices)
{
    outPositions.clear();
    outNormals.clear();
    outIndices.clear();

    // 侧面
    for (int y = 0; y <= heightSegments; ++y) {
        float v = float(y) / heightSegments;
        float z = v;  // [0,1]
        for (int i = 0; i <= radialSegments; ++i) {
            float u = float(i) / radialSegments;
            float theta = u * 2.0f * PI;
            float x = cosf(theta);
            float yy = sinf(theta);

            outPositions.push_back(x);
            outPositions.push_back(yy);
            outPositions.push_back(z);

            outNormals.push_back(x);
            outNormals.push_back(yy);
            outNormals.push_back(0.0f);
        }
    }
    for (int y = 0; y < heightSegments; ++y) {
        for (int i = 0; i < radialSegments; ++i) {
            int a = (y) * (radialSegments + 1) + i;
            int b = (y + 1) * (radialSegments + 1) + i;

            outIndices.push_back(a);
            outIndices.push_back(b);
            outIndices.push_back(a + 1);

            outIndices.push_back(b);
            outIndices.push_back(b + 1);
            outIndices.push_back(a + 1);
        }
    }
    // 底面 (z=0)
    int baseIndex = outPositions.size() / 3;
    outPositions.push_back(0.0f);
    outPositions.push_back(0.0f);
    outPositions.push_back(0.0f);
    outNormals.push_back(0.0f);
    outNormals.push_back(0.0f);
    outNormals.push_back(-1.0f);
    for (int i = 0; i < radialSegments; ++i) {
        int curr = i;
        int next = (i + 1) % radialSegments;
        outIndices.push_back(baseIndex);
        outIndices.push_back(curr);
        outIndices.push_back(next);
    }
    // 顶面 (z=1)
    int topIndex = outPositions.size() / 3;
    outPositions.push_back(0.0f);
    outPositions.push_back(0.0f);
    outPositions.push_back(1.0f);
    outNormals.push_back(0.0f);
    outNormals.push_back(0.0f);
    outNormals.push_back(1.0f);
    int ringStart = (heightSegments) * (radialSegments + 1);
    for (int i = 0; i < radialSegments; ++i) {
        int curr = ringStart + i;
        int next = ringStart + ((i + 1) % radialSegments);
        outIndices.push_back(topIndex);
        outIndices.push_back(next);
        outIndices.push_back(curr);
    }
}

//================================================================================
// 3) 生成圆环 (用于轮胎/轮圈)
//================================================================================
void buildTorusMesh(float ringRadius, float tubeRadius,
    int ringSegments, int tubeSegments,
    std::vector<float>& outPositions,
    std::vector<float>& outNormals,
    std::vector<GLuint>& outIndices)
{
    outPositions.clear();
    outNormals.clear();
    outIndices.clear();

    for (int i = 0; i <= ringSegments; ++i) {
        float u = float(i) / ringSegments * 2.0f * PI;
        float cosU = cosf(u), sinU = sinf(u);
        for (int j = 0; j <= tubeSegments; ++j) {
            float v = float(j) / tubeSegments * 2.0f * PI;
            float cosV = cosf(v), sinV = sinf(v);

            float x = (ringRadius + tubeRadius * cosV) * cosU;
            float y = (ringRadius + tubeRadius * cosV) * sinU;
            float z = tubeRadius * sinV;

            outPositions.push_back(x);
            outPositions.push_back(y);
            outPositions.push_back(z);

            // 先把点映射到主圆心，再算法线
            glm::vec3 center = glm::vec3(ringRadius * cosU, ringRadius * sinU, 0.0f);
            glm::vec3 pos = glm::vec3(x, y, z);
            glm::vec3 normal = glm::normalize(pos - center);

            outNormals.push_back(normal.x);
            outNormals.push_back(normal.y);
            outNormals.push_back(normal.z);
        }
    }

    for (int i = 0; i < ringSegments; ++i) {
        for (int j = 0; j < tubeSegments; ++j) {
            int first = i * (tubeSegments + 1) + j;
            int second = (i + 1) * (tubeSegments + 1) + j;

            outIndices.push_back(first);
            outIndices.push_back(second);
            outIndices.push_back(first + 1);

            outIndices.push_back(second);
            outIndices.push_back(second + 1);
            outIndices.push_back(first + 1);
        }
    }
}

//================================================================================
// 4) 生成单位立方体 (用于踏板盒子)
//================================================================================
void buildCubeMesh(
    std::vector<float>& outPositions,
    std::vector<float>& outNormals,
    std::vector<GLuint>& outIndices)
{
    outPositions.clear();
    outNormals.clear();
    outIndices.clear();

    // +X 面 (右)
    outPositions.insert(outPositions.end(), {
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f
        });
    for (int i = 0; i < 4; i++) outNormals.insert(outNormals.end(), { 1, 0, 0 });

    // -X 面 (左)
    outPositions.insert(outPositions.end(), {
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f
        });
    for (int i = 0; i < 4; i++) outNormals.insert(outNormals.end(), { -1, 0, 0 });

    // +Y 面 (前)
    outPositions.insert(outPositions.end(), {
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f
        });
    for (int i = 0; i < 4; i++) outNormals.insert(outNormals.end(), { 0, 1, 0 });

    // -Y 面 (后)
    outPositions.insert(outPositions.end(), {
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f
        });
    for (int i = 0; i < 4; i++) outNormals.insert(outNormals.end(), { 0, -1, 0 });

    // +Z 面 (上)
    outPositions.insert(outPositions.end(), {
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f
        });
    for (int i = 0; i < 4; i++) outNormals.insert(outNormals.end(), { 0, 0, 1 });

    // -Z 面 (下)
    outPositions.insert(outPositions.end(), {
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f
        });
    for (int i = 0; i < 4; i++) outNormals.insert(outNormals.end(), { 0, 0, -1 });

    // 6 个面，每面两个三角形 (共 36 个索引)
    for (int i = 0; i < 6; ++i) {
        int base = i * 4;
        outIndices.push_back(base + 0);
        outIndices.push_back(base + 1);
        outIndices.push_back(base + 2);

        outIndices.push_back(base + 0);
        outIndices.push_back(base + 2);
        outIndices.push_back(base + 3);
    }
}

//================================================================================
// 5) 生成 3D 齿轮 (extruded gear)
//================================================================================
void buildGearMesh(int teethCount, float r0, float h, float thickness,
    std::vector<float>& outPositions,
    std::vector<float>& outNormals,
    std::vector<GLuint>& outIndices)
{
    outPositions.clear();
    outNormals.clear();
    outIndices.clear();

    // 1) 先在 XY 平面生成 2D 轮廓：
    int verts2D = teethCount * 2;
    std::vector<glm::vec3> contour2D(verts2D);
    for (int i = 0; i < verts2D; ++i) {
        float angle = float(i) * PI / teethCount;
        float radius = (i % 2 == 0 ? (r0 + h) : r0);
        contour2D[i] = glm::vec3(radius * cosf(angle),
            radius * sinf(angle),
            0.0f);
    }

    // 2) 在 2D 轮廓上生成正面 z=+halfTh 和背面 z=-halfTh
    float halfTh = thickness * 0.5f;
    for (int i = 0; i < verts2D; ++i) {
        // 正面 (z = +halfTh)
        outPositions.push_back(contour2D[i].x);
        outPositions.push_back(contour2D[i].y);
        outPositions.push_back(+halfTh);
        // 法线 (正面朝 +Z)
        outNormals.push_back(0.0f);
        outNormals.push_back(0.0f);
        outNormals.push_back(1.0f);
    }
    for (int i = 0; i < verts2D; ++i) {
        // 背面 (z = -halfTh)
        outPositions.push_back(contour2D[i].x);
        outPositions.push_back(contour2D[i].y);
        outPositions.push_back(-halfTh);
        // 法线 (背面朝 -Z)
        outNormals.push_back(0.0f);
        outNormals.push_back(0.0f);
        outNormals.push_back(-1.0f);
    }

    // 3) 正面三角扇
    for (int i = 1; i < verts2D - 1; ++i) {
        outIndices.push_back(0);
        outIndices.push_back(i);
        outIndices.push_back(i + 1);
    }
    // 背面三角扇 (反向)
    int offsetB = verts2D;
    for (int i = 1; i < verts2D - 1; ++i) {
        outIndices.push_back(offsetB + 0);
        outIndices.push_back(offsetB + i + 1);
        outIndices.push_back(offsetB + i);
    }

    // 4) 侧面 extrude (每个边 i->i+1)
    for (int i = 0; i < verts2D; ++i) {
        int inext = (i + 1) % verts2D;
        int idxA = i;
        int idxB = inext;
        int idxC = offsetB + inext;
        int idxD = offsetB + i;

        // 三角形 1: A, B, D
        outIndices.push_back(idxA);
        outIndices.push_back(idxB);
        outIndices.push_back(idxD);
        // 三角形 2: B, C, D
        outIndices.push_back(idxB);
        outIndices.push_back(idxC);
        outIndices.push_back(idxD);

        // 计算侧面法线 (由边 AB 与 z 轴交叉产生)
        glm::vec3 Apos = glm::vec3(outPositions[3 * idxA + 0],
            outPositions[3 * idxA + 1],
            outPositions[3 * idxA + 2]);
        glm::vec3 Bpos = glm::vec3(outPositions[3 * idxB + 0],
            outPositions[3 * idxB + 1],
            outPositions[3 * idxB + 2]);
        glm::vec3 edge = Bpos - Apos;
        glm::vec3 normalSide = glm::normalize(glm::cross(edge, glm::vec3(0, 0, 1)));
        // 将侧面四个顶点的法线都设置为 normalSide
        for (int idxVert : { idxA, idxB, idxC, idxD }) {
            outNormals[3 * idxVert + 0] = normalSide.x;
            outNormals[3 * idxVert + 1] = normalSide.y;
            outNormals[3 * idxVert + 2] = normalSide.z;
        }
    }
}
