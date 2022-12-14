//
//  Block.cpp
//  OpenGL
//
//  Created by Cataldo, David on 12/7/22.
//

#include "Block.hpp"

/*
float Block::vertices[24] =
{
    0.0, 0.0, 0.0,
    2.0, 2.0, 0.0,
    2.0, 0.0, 0.0,
    0.0, 2.0, 0.0,
    
    0.0, 0.0, 2.0,
    2.0, 2.0, 2.0,
    2.0, 0.0, 2.0,
    0.0, 2.0, 2.0
};
uint32_t Block::indices[36] =
{
    0, 2, 1,  // negative x
    1, 3, 0,  // left side
    
    5, 6, 4,  // positive x
    4, 7, 5,  // right side
    
    4, 0, 3,    // positive z
    3, 7, 4,     // front
    
    2, 6, 5,  // negative z
    5, 1, 2,  // back
    
    3, 1, 5,  // positive y
    5, 7, 3,   // top
    
    6, 2, 0,  // negative y
    0, 4, 6   // bottom
    
};
 */

float Block::vtop[20] =
{
    0.0, 2.0, 0.0, 0.5, 1.0,
    2.0, 2.0, 0.0, 0.5, 0.0,
    2.0, 2.0, 2.0, 0.0, 0.0,
    0.0, 2.0, 2.0, 0.0, 1.0
};

float Block::vbottom[20] =
{
    2.0, 0.0, 2.0, 1.0, 1.0,
    2.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.5, 0.0,
    0.0, 0.0, 2.0, 0.5, 1.0
};

float Block::vright[20] =
{
    2.0, 2.0, 2.0, 1.0, 1.0,
    2.0, 0.0, 2.0, 1.0, 0.0,
    0.0, 0.0, 2.0, 0.5, 0.0,
    0.0, 2.0, 2.0, 0.5, 1.0
};

float Block::vleft[20] =
{
    0.0, 0.0, 0.0, 1.0, 1.0,
    2.0, 0.0, 0.0, 1.0, 0.0,
    2.0, 2.0, 0.0, 0.5, 0.0,
    0.0, 2.0, 0.0, 0.5, 1.0
};

float Block::vfront[20] =
{
    0.0, 0.0, 2.0, 1.0, 1.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 2.0, 0.0, 0.5, 0.0,
    0.0, 2.0, 2.0, 0.5, 1.0
};

float Block::vback[20] =
{
    2.0, 0.0, 0.0, 1.0, 1.0,
    2.0, 0.0, 2.0, 1.0, 0.0,
    2.0, 2.0, 2.0, 0.5, 0.0,
    2.0, 2.0, 0.0, 0.5, 1.0
};

uint32_t Block::faceInds[6] =
{
    0, 1, 2,
    2, 3, 0
};

Mesh Block::leftMesh;
Mesh Block::rightMesh;
Mesh Block::topMesh;
Mesh Block::bottomMesh;
Mesh Block::frontMesh;
Mesh Block::backMesh;

Texture Block::dirtTex = Texture("dirtMC.png");

glm::vec3 Block::playerPos;
float Block::render_dist;
