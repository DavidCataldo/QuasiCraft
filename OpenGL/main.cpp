//
//  main.cpp
//  OpenGL
//
//  Created by Cataldo, David on 12/2/22.
//
#define GL_SILENCE_DEPRECATION

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "PerlinNoise.hpp"

#include "Texture.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Chunk.hpp"
#include "Camera.hpp"
#include "MyWindow.hpp"

GLuint VBO, VAO, shader;
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
glm::mat4 proj;
Camera camera;
MyWindow window;

float RENDER_DIST = 300.0;
int chunk_dist = 3;

int main(void)
{
    const siv::PerlinNoise::seed_type seed = 12309423;
    const siv::PerlinNoise perlin {seed};
    
    
    window = MyWindow(800,600);
    window.Initialise();

    // Initialize the library
    
    std::string vertexShader = R"(
                #version 330 core
                
                layout(location = 0) in vec3 a_Position;
                layout(location = 1) in vec2 texCoords;
            
                out vec2 texPos;
                out float depth;
            
                uniform mat4 view;
                uniform mat4 proj;
                uniform mat4 model;

            
                void main()
                {
                    texPos = texCoords;
                    depth = (model * vec4(a_Position*0.5f, 1.0)).y;
                    gl_Position = proj * view * model * vec4(a_Position*0.5f, 1.0);
                }
            )";

    std::string fragmentShader = R"(
                #version 330 core
                
                layout(location = 0) out vec4 color;
            
                in vec2 texPos;
                in float depth;
            
                uniform sampler2D tex;
            
                void main()
                {
                    if(depth <= 12)
                    {
                        color = (texture(tex, texPos)/2);
                    }
                    else
                    {
                        color = (texture(tex, texPos)/2) * (depth - 12) / 5;
                    }
                }
            )";
    
    Shader shader(vertexShader, fragmentShader);
    
    
    

    
    Block::Init(RENDER_DIST);
        
    glm::mat4 model = glm::mat4(1.0f);
    
    proj = glm::perspective(glm::radians(45.0f), (GLfloat)window.getBufferWidth() / window.getBufferHeight(), 0.1f, RENDER_DIST);
    shader.UploadUniformMat4("proj", proj);
    camera = Camera(glm::vec3(0.0f, 35.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);
    shader.UploadUniformMat4("model", model);
    
    
    Chunk chunks[chunk_dist][chunk_dist];
    
     

    for(int x = 0; x < chunk_dist; x++)
    {
        for(int z = 0; z < chunk_dist; z++)
        {
            chunks[x][z] = Chunk(x,z);
            chunks[x][z].Load(perlin);
        }
    }
    
    int playerCX = 0;
    int playerCZ = 0;
    int diffX = 16;
    int diffZ;
    // Loop until the user closes the window
    while (!window.getShouldClose())
    {
        // Render here

        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;
        
        glfwPollEvents();
        
        camera.mouseControl(window.getXChange() , window.getYChange(), window.getMouseLeftClicking());
        camera.keyControl(window.getGLFWWindow(), deltaTime);
        
        if(camera.getCameraPos().x < 0)
            diffX = 16;
        else
            diffX = 0;
        
        if(camera.getCameraPos().z < 0)
            diffZ = 16;
        else
            diffZ = 0;
        
        if(((int) (camera.getCameraPos().x - diffX)) / 16 != playerCX || ((int) (camera.getCameraPos().z - diffZ))/ 16 != playerCZ)
        {
            playerCX = ((int) (camera.getCameraPos().x - diffX)) / 16;
            playerCZ = ((int) (camera.getCameraPos().z - diffZ)) / 16;
            
            for(int x = 0; x < chunk_dist; x++)
            {
                for(int z = 0; z < chunk_dist; z++)
                {
                    chunks[x][z] = Chunk(playerCX + (x - chunk_dist/2), playerCZ + (z - chunk_dist/2));
                    chunks[x][z].Load(perlin);
                }
            }
        }
        
        
        // Clear window
        glClearColor(0.7f, 0.7f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Block::playerPos = camera.getCameraPos();
        
        shader.Bind();
        
        
        shader.UploadUniformMat4("view", camera.calculateViewMatrix());
        
        Chunk::RenderChunks(shader);
        glUseProgram(0);

        window.swapBuffers();
    }

    return 0;
}

