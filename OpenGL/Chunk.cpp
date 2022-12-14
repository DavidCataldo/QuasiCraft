//
//  Chunk.cpp
//  OpenGL
//
//  Created by Cataldo, David on 12/7/22.
//

#include "Chunk.hpp"
#include <iostream>

std::map<Chunk*, coordinate> Chunk::chunks;

void Chunk::Load(const siv::PerlinNoise& noise)
{
    if(!loaded)
    {
        for(int x = 0; x < 16; x++)
        {
            for(int z = 0; z < 16; z++)
            {
                double n = noise.normalizedOctave2D_01(((x+16*pos.x)) * 8, (z+(16*pos.z)) * 8, 3) + noise.noise2D_01(((x+16*pos.x) * 0.01), (z+(16*pos.z)) * 0.01) + noise.normalizedOctave2D_01(((x+16*pos.x)) * 0.01, (z+(16*pos.z)) * 0.01, 7) + (noise.normalizedOctave2D_01(((x+16*pos.x)) * 100, (z+(16*pos.z)) * 100, 20)) * 5;
                int height = (int) (n * 4);
                
                for(int y = 0; y < height; y++)
                {
                    blocks[x][y][z] = new Block(glm::vec3(x+(16*pos.x),y,z+(16*pos.z)));
                }
                for(int y = height; y < 32; y++)
                {
                    blocks[x][y][z] = nullptr;
                }
            }
        }
        
        chunks[this] = pos;
    }
    
    loaded = true;
}

void Chunk::Unload()
{
    if(loaded)
    {
        for(int x = 0; x < 16; x++)
            for(int y = 0; y < 32; y++)
                for(int z = 0; z < 16; z++)
                    blocks[x][y][z] = nullptr;
        
        chunks.erase(this);
    }
    
    loaded = false;
}

void Chunk::Render(const Shader& s)
{
    bool surBlocks[6] = { false, false, false, false, false, false };
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 32; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                if(blocks[x][y][z])
                {
                    for(int i = 0; i < 6; i++)
                        surBlocks[i] = false;
                    
                    if(y != 0)
                        surBlocks[3] = true;
                    if(y < 32 && blocks[x][y+1][z])
                        surBlocks[2] = true;
                   // if(y < 7)
                    {
                       // for(int i = 0; i < 6; i++)
                        //    surBlocks[i] = true;
                    }
                    if(x > 0 && blocks[x-1][y][z])
                        surBlocks[4] = true;
                    if(x < 15 && blocks[x+1][y][z])
                        surBlocks[5] = true;
                    if(z > 0 && blocks[x][y][z-1])
                        surBlocks[0] = true;
                    if(z < 15 && blocks[x][y][z+1])
                        surBlocks[1] = true;
                        
                    blocks[x][y][z]->Render(s, surBlocks);
                }
            }
        }
    }
}

void Chunk::RenderChunks(const Shader& s)
{
    for(const auto& [chunk, position] : chunks)
    {
        chunk->Render(s);
    }
}


