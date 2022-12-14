//
//  Mesh.hpp
//  OpenGL
//
//  Created by Cataldo, David on 12/4/22.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <GLUT/glut.h>

class Mesh
{
public:
    Mesh();

    void CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
    void RenderMesh();
    void ClearMesh();

    inline GLfloat* GetVerts() { return verts; }
    inline unsigned int* GetIndices() { return indices; }
    inline unsigned int GetNumOfVerts() { return numOfVerts; }
    inline unsigned int GetNumOfInds() { return numOfIndices; }

    ~Mesh();

private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
    GLfloat* verts;
    unsigned int* indices;
    unsigned int numOfVerts;
    unsigned int numOfIndices;
};

#endif /* Mesh_hpp */
