#include "parts.h"
#include "draw.h"
#include "globals.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <algorithm>
#include <cmath>

//================================================================================
// 链条 (仅绘制销轴 PIN，链板略去)
//================================================================================
namespace Chain {
    const glm::vec3 C1 = P_B, C2 = P_A;
    const float      L_arc1 = PI * R_CHAINRING;
    const float      L_arc2 = PI * R_SPROCKET;
    float     L_top, L_bot, L_tot;

    void init() {
        glm::vec3 Btop = glm::vec3(C1.x, 0, C1.z + R_CHAINRING);
        glm::vec3 Bbot = glm::vec3(C1.x, 0, C1.z - R_CHAINRING);
        glm::vec3 Atop = glm::vec3(C2.x, 0, C2.z + R_SPROCKET);
        glm::vec3 Abot = glm::vec3(C2.x, 0, C2.z - R_SPROCKET);
        L_top = glm::length(Atop - Btop);
        L_bot = glm::length(Bbot - Abot);
        L_tot = L_arc1 + L_top + L_arc2 + L_bot;
    }

    // sample 一个销轴中心 pos、轴向 dir (单位向量)，u ∈ [0,1]
    void sample(float u, glm::vec3& pos, glm::vec3& dir) {
        float s = u * L_tot;
        glm::vec3 Btop = glm::vec3(C1.x, 0, C1.z + R_CHAINRING);
        glm::vec3 Bbot = glm::vec3(C1.x, 0, C1.z - R_CHAINRING);
        glm::vec3 Atop = glm::vec3(C2.x, 0, C2.z + R_SPROCKET);
        glm::vec3 Abot = glm::vec3(C2.x, 0, C2.z - R_SPROCKET);

        if (s < L_arc1) {
            float th = -PI / 2 + s / R_CHAINRING;
            pos = glm::vec3(C1.x + R_CHAINRING * cosf(th),
                0,
                C1.z + R_CHAINRING * sinf(th));
            dir = glm::normalize(glm::vec3(-sinf(th), 0, cosf(th)));
            return;
        }
        s -= L_arc1;
        if (s < L_top) {
            float t = s / L_top;
            pos = glm::mix(Btop, Atop, t);
            dir = glm::normalize(Atop - Btop);
            return;
        }
        s -= L_top;
        if (s < L_arc2) {
            float th = PI / 2 - s / R_SPROCKET;
            pos = glm::vec3(C2.x + R_SPROCKET * cosf(th),
                0,
                C2.z + R_SPROCKET * sinf(th));
            dir = glm::normalize(glm::vec3(-sinf(th), 0, cosf(th)));
            return;
        }
        s -= L_arc2;
        float t = s / L_bot;
        pos = glm::mix(Abot, Bbot, t);
        dir = glm::normalize(Bbot - Abot);
    }

    void draw(double off, const glm::mat4& view, const glm::mat4& proj) {
        glm::vec3 color = glm::vec3(0.1f, 0.1f, 0.1f); // 黑色
        for (int i = 0; i < LINK_CNT; ++i) {
            float u = fmodf(static_cast<float>(off) + i / float(LINK_CNT), 1.0f);
            glm::vec3 p, d;
            sample(u, p, d);
            glm::vec3 p2 = p + d * LINK_LEN;
            drawCylinder(p, p2, PIN_R, color, view, proj);
        }
    }
}

//================================================================================
// 2) 车架主体 (frame) (红色)
//================================================================================
void drawFrame(const glm::mat4& view, const glm::mat4& proj) {
    glm::vec3 color = glm::vec3(0.9f, 0.12f, 0.12f);

    // 双后叉 (两根小管从后轮轴向中轴/座杆)
    for (int side = -1; side <= 1; side += 2) {
        float y = side * FORK_Y;
        glm::vec3 A = glm::vec3(P_A.x, y, P_A.z);
        glm::vec3 S = P_S;
        glm::vec3 B = P_B;
        drawCylinder(A, S, 0.009f, color, view, proj);
        drawCylinder(A, B, 0.009f, color, view, proj);
    }
    // 主三角：中轴→立管底、中轴→座杆、座杆→立管顶
    drawCylinder(P_B, P_C, 0.011f, color, view, proj);
    drawCylinder(P_S, P_D, 0.010f, color, view, proj);
    drawCylinder(P_B, P_S, 0.013f, color, view, proj);
}

//================================================================================
// 3) 车把 & 前叉 (灰色)
//================================================================================
void drawForkAndHandle(const glm::mat4& view, const glm::mat4& proj) {
    glm::vec3 color = glm::vec3(0.65f, 0.65f, 0.65f);

    // 立管下：P_C → P_FS
    drawCylinder(P_C, P_FS, 0.014f, color, view, proj);
    // 立管上：P_FS → P_D
    drawCylinder(P_FS, P_D, 0.014f, color, view, proj);
    // 把手：P_D → H
    drawCylinder(P_D, H, 0.007f, color, view, proj);

    // 斜叉脚 (左右各一根)：P_FS → 前轮轴左右
    for (int side = -1; side <= 1; side += 2) {
        float y = side * FORK_Y;
        glm::vec3 foot = glm::vec3(P_F.x, y, R_WHEEL);
        drawCylinder(P_FS, foot, 0.007f, color, view, proj);
    }

    // 横把 (L → R)
    glm::vec3 L = glm::vec3(H.x, H.y - 0.14f, H.z);
    glm::vec3 R = glm::vec3(H.x, H.y + 0.14f, H.z);
    drawCylinder(L, R, 0.008f, color, view, proj);

    // 握把胶套 (蓝色)
    float glen = 0.04f, grad = 0.02f;
    glm::vec3 blue = glm::vec3(0, 0, 1);
    for (auto ctr : { L, R }) {
        glm::vec3 p1 = ctr + glm::vec3(0, -glen / 2, 0);
        glm::vec3 p2 = ctr + glm::vec3(0, glen / 2, 0);
        drawCylinder(p1, p2, grad, blue, view, proj);
    }
}

//================================================================================
// 4) 座椅 & 座杆 (座杆圆柱, 座垫球体)
//================================================================================
void drawSeat(const glm::mat4& view, const glm::mat4& proj) {
    glm::vec3 color = glm::vec3(0.25f, 0.25f, 0.25f);
    glm::vec3 top = P_S + glm::vec3(0, 0, 0.06f + seatShift);
    drawCylinder(P_S, top, 0.009f, color, view, proj);

    // 座垫：球体拉伸
    glm::mat4 model(1.0f);
    model = glm::translate(model, top);
    model = glm::scale(model, glm::vec3(1.4f, 0.5f, 0.35f) * 0.05f);
    renderMesh(gVAO_Sphere, gSphIndexCount, model, color, view, proj);
}

//================================================================================
//    精致踏板
//================================================================================
void drawDetailedPedal(const glm::vec3& center, const glm::mat4& baseModel,
    const glm::mat4& view, const glm::mat4& proj) {
    glm::vec3 pedalColor = glm::vec3(0.05f, 0.05f, 0.05f);

    // 主踏板面
    glm::mat4 model = glm::translate(glm::mat4(1.0f), center);
    model = glm::scale(model, glm::vec3(0.02f, 0.07f, 0.005f));
    renderMesh(gVAO_Cube, gCubeIndexCount, model, pedalColor, view, proj);

    // 防滑凸起
    for (int i = -2; i <= 2; ++i) {
        glm::mat4 bumpModel = glm::translate(glm::mat4(1.0f), center + glm::vec3(0, i * 0.015f, 0.003f));
        bumpModel = glm::scale(bumpModel, glm::vec3(0.018f, 0.005f, 0.002f));
        renderMesh(gVAO_Cube, gCubeIndexCount, bumpModel, pedalColor, view, proj);
    }
}

//================================================================================
// 5) 曲柄 (灰色) + 踏板 (蓝色) + 链盘 (带齿链盘)
//================================================================================
void drawCrank(const glm::mat4& view, const glm::mat4& proj) {
    // 中轴 (灰色)
    glm::vec3 gray = glm::vec3(0.65f, 0.65f, 0.65f);
    glm::vec3 p1 = P_B + glm::vec3(0, -0.03f, 0);
    glm::vec3 p2 = P_B + glm::vec3(0, 0.03f, 0);
    drawCylinder(p1, p2, 0.012f, gray, view, proj);

    // 基础变换：让整个踏板体系绕中轴旋转 g_crankAngle
    glm::mat4 baseModel(1.0f);
    baseModel = glm::translate(baseModel, P_B);
    baseModel = glm::rotate(baseModel, glm::radians(static_cast<float>(g_crankAngle)), glm::vec3(0, 1, 0));
    baseModel = glm::translate(baseModel, -P_B);

    // 左右曲柄臂 + 踏板
    glm::vec3 blue = glm::vec3(0, 0, 1);
    for (int i = 0; i < 2; ++i) {
        float sign = (i == 0 ? -1.0f : 1.0f);
        // 曲柄臂
        glm::vec3 elbow = P_B + glm::vec3(0, 0, (i ? -VERT_LEN : VERT_LEN));
        {
            glm::vec3 pa = glm::vec3(baseModel * glm::vec4(P_B, 1.0f));
            glm::vec3 pb = glm::vec3(baseModel * glm::vec4(elbow, 1.0f));
            drawCylinder(pa, pb, 0.006f, gray, view, proj);
        }
        // 踏板轴心
        glm::vec3 pedalCenterLocal = elbow + glm::vec3(OFFSET_X, sign * HORIZ_LEN, 0);
        glm::vec3 pedalCenter = glm::vec3(baseModel * glm::vec4(pedalCenterLocal, 1.0f));
        glm::vec3 elbowTrans = glm::vec3(baseModel * glm::vec4(elbow, 1.0f));
        drawCylinder(elbowTrans, pedalCenter, 0.006f, gray, view, proj);

        drawDetailedPedal(pedalCenter, baseModel, view, proj);
    }

    // 链盘：使用带齿链盘 VAO
    {
        glm::vec3 grayC = glm::vec3(0.65f, 0.65f, 0.65f);
        glm::mat4 model(1.0f);
        model = glm::translate(model, P_B);
        // 先绕 Y 旋转，让链盘跟随曲柄转动
        model = glm::rotate(model, glm::radians(static_cast<float>(g_crankAngle)), glm::vec3(0, 1, 0));
        // 再绕 X 旋转 –90°：将 3D 齿轮面从 XY → XZ 平面
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
        renderMesh(gVAO_Chainring, gCRIndexCount, model, grayC, view, proj);
    }
}

//================================================================================
// 6) 轮组 (统一绘制流程)
//================================================================================
void drawWheel(const glm::vec3& posWheel, float wheelAngle, bool isRear,
    const glm::mat4& view, const glm::mat4& proj)
{
    // 整体模型：先平移到 posWheel，再绕 Y 旋转 wheelAngle
    glm::mat4 model(1.0f);
    model = glm::translate(model, posWheel);
    model = glm::rotate(model, glm::radians(wheelAngle), glm::vec3(0, 1, 0));

    // 轮胎 (黑色 Torus)
    glm::vec3 black = glm::vec3(0.0f, 0.0f, 0.0f);
    {
        glm::mat4 m2 = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
        renderMesh(gVAO_Tire, gTireIndexCount, m2, black, view, proj);
    }
    // 轮圈 (灰色 Torus)
    {
        glm::mat4 m2 = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
        glm::vec3 gray = glm::vec3(0.8f, 0.8f, 0.8f);
        renderMesh(gVAO_Rim, gRimIndexCount, m2, gray, view, proj);
    }
    // 花鼓 (灰色 Cylinder)
    {
        glm::vec3 color = glm::vec3(0.65f, 0.65f, 0.65f);
        glm::mat4 m2 = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
        glm::vec3 p1 = glm::vec3(0, -0.02f, 0);
        glm::vec3 p2 = glm::vec3(0, 0.02f, 0);
        glm::vec3 w_p1 = glm::vec3(m2 * glm::vec4(p1, 1.0f));
        glm::vec3 w_p2 = glm::vec3(m2 * glm::vec4(p2, 1.0f));
        drawCylinder(w_p1, w_p2, 0.01f, color, view, proj);
    }
    // 后飞轮 (带齿飞轮)
    if (isRear) {
        glm::mat4 mg(1.0f);
        mg = glm::translate(mg, posWheel);
        mg = glm::rotate(mg, glm::radians(wheelAngle), glm::vec3(0, 1, 0));
        mg = glm::rotate(mg, glm::radians(-90.0f), glm::vec3(1, 0, 0));
        glm::vec3 dark = glm::vec3(0.1f, 0.1f, 0.1f);
        renderMesh(gVAO_Sprocket, gSRIndexCount, mg, dark, view, proj);
    }
    // 辐条 (32 根 Cylinder)
    {
        glm::vec3 color = glm::vec3(0.65f, 0.65f, 0.65f);
        const int Nsp = 32;
        float hubY[2] = { -0.02f, 0.02f };
        for (int i = 0; i < Nsp; ++i) {
            float a = 2.0f * PI * i / Nsp;
            glm::vec3 rimLocal = glm::vec3((R_WHEEL - 0.03f) * cosf(a),
                0.0f,
                (R_WHEEL - 0.03f) * sinf(a));
            glm::vec3 hubLocal = glm::vec3(0.0f, hubY[i & 1], 0.0f);
            glm::vec3 w_hub = glm::vec3(model * glm::vec4(hubLocal, 1.0f));
            glm::vec3 w_rim = glm::vec3(model * glm::vec4(rimLocal, 1.0f));
            drawCylinder(w_hub, w_rim, 0.0025f, color, view, proj);
        }
    }
}
