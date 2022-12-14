//
//  Camera.hpp
//  OpenGL
//
//  Created by Cataldo, David on 12/7/22.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Camera
{
public:
    Camera();
    Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

    void keyControl(GLFWwindow* window, GLfloat deltaTime);
    void mouseControl(GLfloat xChange, GLfloat yChange, bool isLeftClicking);

    glm::vec3 getCameraPos() { return position; }
    glm::vec3 GetCameraDirection() { return glm::normalize(front); }

    glm::mat4 calculateViewMatrix();

    ~Camera();

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;

    GLfloat moveSpeed;
    GLfloat turnSpeed;

    void update();
};

#endif /* Camera_hpp */
