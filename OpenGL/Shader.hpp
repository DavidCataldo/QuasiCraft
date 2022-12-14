//
//  Shader.hpp
//  OpenGL
//
//  Created by Cataldo, David on 12/4/22.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdint.h>
#include <glm/glm.hpp>
#include <string>
#include <GLUT/glut.h>


class Shader
{
public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

    void Bind() const;
    void Unbind() const;

    void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;
    void UploadUniformIntArray(const std::string& name, const std::vector<int>& array) const;
        
private:
    uint32_t m_RendererID;
    mutable bool m_Bound = false;
};


#endif /* Shader_hpp */
