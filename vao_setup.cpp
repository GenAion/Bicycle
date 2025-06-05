#include "vao_setup.h"
#include "mesh.h"

//================================================================================
// 生成并绑定 Cylinder VAO/VBO/EBO
//================================================================================
void setupCylinderVAO()
{
    std::vector<float> positions, normals;
    std::vector<GLuint> indices;
    buildCylinderMesh(SEGMENTS_CYLINDER, 1, positions, normals, indices);

    extern GLuint gVAO_Cylinder, gVBO_CylPos, gVBO_CylNorm, gEBO_Cyl;
    extern GLsizei gCylIndexCount;
    gCylIndexCount = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &gVAO_Cylinder);
    glBindVertexArray(gVAO_Cylinder);

    // 位置 VBO
    glGenBuffers(1, &gVBO_CylPos);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO_CylPos);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float),
        positions.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);  // layout(location=0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // 法线 VBO
    glGenBuffers(1, &gVBO_CylNorm);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO_CylNorm);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float),
        normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);  // layout(location=1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // EBO
    glGenBuffers(1, &gEBO_Cyl);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO_Cyl);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
        indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

//================================================================================
// 生成并绑定 Sphere VAO/VBO/EBO
//================================================================================
void setupSphereVAO()
{
    std::vector<float> positions, normals;
    std::vector<GLuint> indices;
    buildSphereMesh(SEGMENTS_SPHERE, SEGMENTS_SPHERE,
        positions, normals, indices);

    extern GLuint gVAO_Sphere, gVBO_SphPos, gVBO_SphNorm, gEBO_Sph;
    extern GLsizei gSphIndexCount;
    gSphIndexCount = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &gVAO_Sphere);
    glBindVertexArray(gVAO_Sphere);

    // 位置 VBO
    glGenBuffers(1, &gVBO_SphPos);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO_SphPos);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float),
        positions.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // 法线 VBO
    glGenBuffers(1, &gVBO_SphNorm);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO_SphNorm);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float),
        normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // EBO
    glGenBuffers(1, &gEBO_Sph);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO_Sph);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
        indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

//================================================================================
// 生成并绑定 Torus VAO/VBO/EBO
//================================================================================
void setupTorusVAO(float ringRadius, float tubeRadius,
    GLuint& outVAO, GLuint& outVBOpos, GLuint& outVBOnorm,
    GLuint& outEBO, GLsizei& outIndexCount)
{
    std::vector<float> positions, normals;
    std::vector<GLuint> indices;
    buildTorusMesh(ringRadius, tubeRadius,
        SEGMENTS_TORUS_R, SEGMENTS_TORUS_T,
        positions, normals, indices);

    outIndexCount = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &outVAO);
    glBindVertexArray(outVAO);

    // Position VBO
    glGenBuffers(1, &outVBOpos);
    glBindBuffer(GL_ARRAY_BUFFER, outVBOpos);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float),
        positions.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Normal VBO
    glGenBuffers(1, &outVBOnorm);
    glBindBuffer(GL_ARRAY_BUFFER, outVBOnorm);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float),
        normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // EBO
    glGenBuffers(1, &outEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, outEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
        indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

//================================================================================
// 生成并绑定 Cube VAO/VBO/EBO
//================================================================================
void setupCubeVAO()
{
    std::vector<float> positions, normals;
    std::vector<GLuint> indices;
    buildCubeMesh(positions, normals, indices);

    extern GLuint gVAO_Cube, gVBO_CubePos, gVBO_CubeNorm, gEBO_Cube;
    extern GLsizei gCubeIndexCount;
    gCubeIndexCount = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &gVAO_Cube);
    glBindVertexArray(gVAO_Cube);

    // Position VBO
    glGenBuffers(1, &gVBO_CubePos);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO_CubePos);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float),
        positions.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Normal VBO
    glGenBuffers(1, &gVBO_CubeNorm);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO_CubeNorm);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float),
        normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // EBO
    glGenBuffers(1, &gEBO_Cube);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO_Cube);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
        indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

//================================================================================
// 生成并绑定 Gear VAO/VBO/EBO
//================================================================================
void setupGearVAO(int teethCount, float r0, float h, float thickness,
    GLuint& outVAO, GLuint& outVBOpos, GLuint& outVBOnorm,
    GLuint& outEBO, GLsizei& outIndexCount)
{
    std::vector<float> positions, normals;
    std::vector<GLuint> indices;
    buildGearMesh(teethCount, r0, h, thickness, positions, normals, indices);

    outIndexCount = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &outVAO);
    glBindVertexArray(outVAO);

    // Position VBO
    glGenBuffers(1, &outVBOpos);
    glBindBuffer(GL_ARRAY_BUFFER, outVBOpos);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float),
        positions.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Normal VBO
    glGenBuffers(1, &outVBOnorm);
    glBindBuffer(GL_ARRAY_BUFFER, outVBOnorm);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float),
        normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // EBO
    glGenBuffers(1, &outEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, outEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
        indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}
