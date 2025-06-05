# 3D Bicycle (Gears & Chain Animated)

A C++/OpenGL project that renders and animates a 3D bicycle with realistic gears, chain, and frame. Written using FreeGLUT, GLEW, and GLM. The chainring (front gear) and rear sprocket are modeled with 32 triangular-prism “teeth,” and the entire bicycle is fully rigged: wheels, crank, chain, handlebars, fork, frame, seat, and pedals.

<p align="center">
  <img src="https://raw.githubusercontent.com/your-username/3D-Bicycle/main/demo.gif" alt="Bicycle Demo" width="600">
</p>

---

## Table of Contents

- [Features](#features)  
- [Screenshots](#screenshots)  
- [Prerequisites](#prerequisites)  
- [Building & Running](#building--running)  
- [Project Structure](#project-structure)  
- [Controls](#controls)  
- [Code Overview](#code-overview)  
- [License](#license)  

---

## Features

- **Animated Chain & Gears**  
  - Chainring (front gear) with 32 triangular-prism teeth  
  - Rear sprocket (rear gear) also with 32 triangular-prism teeth  
  - Chain represented by individual pin cylinders that traverse two circular arcs + connecting straights  
  - Crank turns drives both chain and wheels in sync  

- **Full Bicycle Components**  
  - Detailed frame (tubes, seat tube, top tube, down tube, rear stays, chain stays)  
  - Seat + seatpost  
  - Fork, handlebars, grips  
  - Wheels with tire (torus), rim (torus), hub, and 32 spokes (cylinders)  
  - Pedals with anti-slip bumps (small cubes) and crank arms  

- **User Interaction**  
  - Left-click to start/stop animation  
  - Mouse drag to rotate camera  
  - Keyboard ↑/↓ ( `W`/`S` ) to raise/lower seat  
  - Keyboard ←/→ ( `A`/`D` ) to steer handlebars ±45°  
  - Smooth Phong‐lighting (ambient + diffuse + Blinn‐Phong specular)  

- **Modular Code Organization**  
  - Mesh generation in `mesh.*`  
  - VAO/VBO/EBO setup in `vao_setup.*`  
  - Global constants & variables in `globals.*`  
  - Shader compilation in `shaders.*`  
  - Draw utilities in `draw.*`  
  - Bicycle‐part rendering in `parts.*`  
  - GLUT callbacks & main loop in `callbacks.*` and `main.cpp`  

---

## Screenshots

<p align="center">
  <img src="https://raw.githubusercontent.com/your-username/3D-Bicycle/main/screenshot1.png" alt="Bicycle Side View" width="600">
</p>
<p align="center">
  <img src="https://raw.githubusercontent.com/your-username/3D-Bicycle/main/screenshot2.png" alt="Close‐up Chain & Gears" width="600">
</p>

---

## Prerequisites

Before building, ensure you have the following installed on your system:

- **C++ Compiler** (e.g. `g++` on Linux/Mac, or MSVC on Windows)  
- **FreeGLUT** (≥ 3.x)  
- **GLEW** (≥ 2.x)  
- **GLM** (header‐only, ≥ 0.9.9)  
- **OpenGL Development Libraries**  

On Ubuntu/Debian, you can install dependencies via:

```bash
sudo apt update
sudo apt install build-essential libglfw3-dev libglew-dev libglm-dev freeglut3-dev
On macOS (using Homebrew):

bash
复制
编辑
brew install glew glm freeglut
On Windows, you can download precompiled binaries and set up include/lib paths in your Visual Studio project.

Building & Running
Clone this repository

bash
复制
编辑
git clone https://github.com/your-username/3D-Bicycle.git
cd 3D-Bicycle
Compile

Linux/macOS (using pkg-config)

bash
复制
编辑
g++ -std=c++11 \
  globals.cpp \
  mesh.cpp \
  vao_setup.cpp \
  shaders.cpp \
  callbacks.cpp \
  draw.cpp \
  parts.cpp \
  main.cpp \
  -o BicycleApp \
  $(pkg-config --cflags --libs glew freeglut glm)
Linux/macOS (manual linking)

bash
复制
编辑
g++ -std=c++11 \
  globals.cpp \
  mesh.cpp \
  vao_setup.cpp \
  shaders.cpp \
  callbacks.cpp \
  draw.cpp \
  parts.cpp \
  main.cpp \
  -o BicycleApp \
  -lGLEW -lGLU -lGL -lglut
Windows (Visual Studio)

Create a new Win32 Console project.

Add all .cpp/.h files to the project.

Configure Additional Include Directories to point to FreeGLUT, GLEW, and GLM headers.

Configure Additional Library Directories to point to your FreeGLUT/GLEW libs.

Link against glew32s.lib, freeglut.lib, opengl32.lib.

Define GLEW_STATIC in Preprocessor Definitions.

Run

bash
复制
编辑
./BicycleApp
Project Structure
text
复制
编辑
3D-Bicycle/
├── mesh.h
├── mesh.cpp
├── vao_setup.h
├── vao_setup.cpp
├── globals.h
├── globals.cpp
├── shaders.h
├── shaders.cpp
├── callbacks.h
├── callbacks.cpp
├── draw.h
├── draw.cpp
├── parts.h
├── parts.cpp
├── main.cpp
└── README.md
mesh.*
Implements functions to generate vertex positions, normals, and index lists for:

Sphere (buildSphereMesh)

Cylinder (buildCylinderMesh)

Torus (buildTorusMesh)

Cube (buildCubeMesh)

Extruded 2D gear (buildGearMesh) (not used for chainring/sprocket here)

Triangular Prism (buildTriPrismMesh) – used for chainring and sprocket teeth

vao_setup.*
Creates & populates VAO/VBO/EBO for each mesh:

Cylinder, Sphere, Cube, Torus, Gear (unused), Triangular Prism

globals.*
Defines constants (e.g. wheel radius, chain parameters, segment counts)
Declares/initializes global variables (angles, camera, shader program, VAO handles, bike key points)

shaders.*
Contains a simple Phong‐lighting vertex & fragment shader in GLSL
Compiles & links them into gShaderProgram

callbacks.*
display() – main render function: sets up camera, projection, and calls all draw routines in correct order

reshape(), mouseButton(), mouseMotion(), keyboard() – handle window/camera/scene interactions

tick() – GLUT timer callback: updates crank angle, chain offset, wheel rotation, and schedules the next tick

draw.*
renderMesh() – binds a VAO, uploads uniforms (MVP, ModelView, NormalMatrix, light & material), and renders via glDrawElements

Utility drawing functions for primitive shapes (cylinder, sphere, torus)

parts.*
High‐level routines to draw each bicycle component:

Chain::draw() – draws chain by sampling chain pins along two circular arcs + straight sections

drawFrame() – draws tubes of the bicycle frame

drawForkAndHandle() – draws front fork, handlebar, and grips

drawSeat() – draws seatpost (cylinder) and seat cushion (scaled sphere)

drawDetailedPedal() – draws pedal + anti‐slip bumps (cubes)

drawCrank() – draws crank axle, crank arms, pedals, and chainring:

Centers a cylinder (scaled to R_CHAINRING × R_CHAINRING × thickness)

Places 32 triangular‐prism “teeth” evenly around the circumference

drawWheel() – draws tire (torus), rim (torus), hub (cylinder), sprocket (cylinder + triangular‐prism teeth), and spokes (cylinders)

main.cpp
Initializes GLUT, GLEW, OpenGL settings (depth test, lighting)

Calls Chain::init() to compute chain length

Compiles shaders (initShaders())

Sets up VAOs for all meshes (setupCylinderVAO(), setupSphereVAO(), etc.)

Registers callbacks (display, reshape, mouseButton, mouseMotion, keyboard, tick)

Enters glutMainLoop()

Controls
Left‐click anywhere in the window to toggle animation (play/pause).

Mouse drag (left‐button + drag) to rotate the camera around the bicycle.

Keyboard

A / a: Turn handlebars left (steer angle –5°, down to –45°)

D / d: Turn handlebars right (steer angle +5°, up to +45°)

W / w: Raise seatpost (up by 0.01, up to +0.12)

S / s: Lower seatpost (down by 0.01, down to 0)

