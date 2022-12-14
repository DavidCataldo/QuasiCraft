//
//  Texture.hpp
//  OpenGL
//
//  Created by Cataldo, David on 12/4/22.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <GLUT/glut.h>

class Texture
{
public:
    Texture(const char* fileLoc = "");

    bool LoadTexture();
    bool LoadTextureA();

    void UseTexture();
    void ClearTexture();

    ~Texture();

private:
    GLuint textureID;
    int width, height, bitDepth;

    const char* fileLocation;
};

#endif /* Texture_hpp */
