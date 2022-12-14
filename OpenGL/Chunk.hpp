//
//  Chunk.hpp
//  OpenGL
//
//  Created by Cataldo, David on 12/7/22.
//

#ifndef Chunk_hpp
#define Chunk_hpp

#include <map>
#include <glm/glm.hpp>
#include "Block.hpp"
#include "PerlinNoise.hpp"

struct coordinate
{
    int x;
    int z;
};

class Chunk
{
public:
    
    
    Chunk(int x = 0, int z = 0)
    {
        pos.x = x;
        pos.z = z;
        loaded = false;
    }
    
    ~Chunk() { Unload(); }
    
    void Load(const siv::PerlinNoise& noise);
    void Unload();
    void Render(const Shader& s);
    
    static void RenderChunks(const Shader& s);
    
public:
    static std::map<Chunk*, coordinate> chunks;
    
private:
    Block *blocks[16][32][16];
    coordinate pos;
    bool loaded;
};

#endif /* Chunk_hpp */
