//
//  Block.hpp
//  OpenGL
//
//  Created by Cataldo, David on 12/7/22.
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

class Block
{
public:
    static void Init(float render, glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0))
    {
        render_dist = render;
        playerPos = pos;
        
        dirtTex.LoadTexture();
        
        leftMesh.CreateMesh(vleft, faceInds, 20, 6);
        rightMesh.CreateMesh(vright, faceInds, 20, 6);
        topMesh.CreateMesh(vtop, faceInds, 20, 6);
        bottomMesh.CreateMesh(vbottom, faceInds, 20, 6);
        frontMesh.CreateMesh(vfront, faceInds, 20, 6);
        backMesh.CreateMesh(vback, faceInds, 20, 6);

        dirtTex.UseTexture();
    }
    
    Block()
        : position(glm::vec3(0.0f))
    {
        modelmat = glm::mat4(1.0f);
    }
    Block(glm::vec3 pos)
        : position(pos)
    {
        modelmat = glm::translate(glm::mat4(1.0f), pos);
    }
    
    const void Render(const Shader& s, bool surBlocks[6])
    {
        
        if(inRenderDist())
        {
            s.UploadUniformMat4("model", modelmat);
            
            glm::vec3 dir = playerPos - position;
            
            if(!surBlocks[0] && dir.z < 0)
                Block::leftMesh.RenderMesh();
            if(!surBlocks[1] && dir.z > 0)
                Block::rightMesh.RenderMesh();
            if(!surBlocks[2] && dir.y > 0)
                Block::topMesh.RenderMesh();
            if(!surBlocks[3] && dir.y < 0)
                Block::bottomMesh.RenderMesh();
            if(!surBlocks[4] && dir.x < 0)
                Block::frontMesh.RenderMesh();
            if(!surBlocks[5] && dir.x > 0)
                Block::backMesh.RenderMesh();
        }
        

    }
    
    
private:
    glm::mat4 modelmat;
    glm::vec3 position;
    
    bool inRenderDist()
    {
        return (glm::distance(position, playerPos) < render_dist);
    }
    
    
public:
    static float vtop[20];
    static float vbottom[20];
    static float vright[20];
    static float vleft[20];
    static float vfront[20];
    static float vback[20];
    
    static uint32_t faceInds[6];
    
    static Mesh leftMesh;
    static Mesh rightMesh;
    static Mesh topMesh;
    static Mesh bottomMesh;
    static Mesh frontMesh;
    static Mesh backMesh;
    
    static Texture dirtTex;
    
    static float render_dist;
    static glm::vec3 playerPos;
};

#endif /* Block_hpp */
