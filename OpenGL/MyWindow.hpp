//
//  MyWindow.hpp
//  OpenGL
//
//  Created by Cataldo, David on 12/9/22.
//

#ifndef MyWindow_hpp
#define MyWindow_hpp

#include <iostream>
#include <GL/glew.h>

#include <GLFW/glfw3.h>

class MyWindow
{
public:
    MyWindow();

    MyWindow(GLint windowWidth, GLint windowHeight);

    int Initialise();

    GLint getBufferWidth() { return bufferWidth; }
    GLint getBufferHeight() { return bufferHeight; }

    GLint getWidth() { return width; }
    GLint getHeight() { return height; }

    void UpdateSize();

    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

    bool* getsKeys() { return keys; }

    bool getMouseLeftClicking() { return glfwGetMouseButton(mainWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS; }
    GLfloat getMouseX() { return lastX; }
    GLfloat getMouseY() { return lastY; }

    GLfloat getXChange();
    GLfloat getYChange();

    GLFWwindow* getGLFWWindow() { return mainWindow; }

    void swapBuffers() { glfwSwapBuffers(mainWindow); }

    ~MyWindow();

private:
    GLFWwindow* mainWindow;

    GLint width, height;
    GLint bufferWidth, bufferHeight;

    bool keys[1024];

    GLfloat lastX;
    GLfloat lastY;
    GLfloat xChange;
    GLfloat yChange;
    bool mouseFirstMoved;

    void createCallbacks();
    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

#endif /* MyWindow_hpp */
