#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Editor/linalg.h"

#include <vector>

enum Camera_Movement {

    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SENSITIVITY = 0.2f;
const float ZOOM = 60.0f;
const float ROLL = 0.0f;




class Camera
{
public:

    bool CameraMode = false;

    float SPEED = 10.0f;

    glm::vec3 Position;

    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float yfov, near_clip, far_clip;
    linalg::aliases::float3 position;
    float pitch, yaw;
    float roll;

   

    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    float Roll;

    glm::mat4 projection;

    Camera(glm::vec3 position = glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float roll = ROLL) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        Roll = roll;  // Добавляем roll
        updateCameraVectors();
    }

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float roll) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        Roll = roll;  // Добавляем roll
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)

    {
        if (!CameraMode)
        {
            float velocity = MovementSpeed * deltaTime;
            if (direction == FORWARD)
                Position += Front * velocity;
            if (direction == BACKWARD)
                Position -= Front * velocity;
            if (direction == LEFT)
                Position -= Right * velocity;
            if (direction == RIGHT)
                Position += Right * velocity;
        }

        else
        
        {
            float velocity = MovementSpeed * deltaTime;
            if (direction == FORWARD)
            {
                glm::vec3 forward = Front;
                forward.y = 0.0f; // Устанавливаем Y-компонент в 0
                forward = glm::normalize(forward);
                Position += forward * velocity;
            }
            if (direction == BACKWARD)
            {
                glm::vec3 backward = -Front;
                backward.y = 0.0f; // Устанавливаем Y-компонент в 0
                backward = glm::normalize(backward);
                Position += backward * velocity;
            }
            if (direction == LEFT)
                Position -= Right * velocity;
            if (direction == RIGHT)
                Position += Right * velocity;

        }

       
    }
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)

    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;
        Yaw += xoffset;
        Pitch += yoffset;
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }
        updateCameraVectors();
    }

    void ProcessMouseScroll(float yoffset)
    {
        if (Zoom >= 1.0f && Zoom <= 45.0f)
            Zoom -= yoffset;
        if (Zoom <= 1.0f)
            Zoom = 1.0f;
        if (Zoom >= 45.0f)
            Zoom = 45.0f;
    }


    void SetSpeed(float speed) {
        SPEED = speed;
    }

    float GetSpeed() const {
        return SPEED;
    }

    void SetPosition(glm::vec3 newPosition) {
        Position = newPosition;
        updateCameraVectors();
    }

    void SetPosition(float x, float y, float z) {
        Position = glm::vec3(x, y, z);
        updateCameraVectors();
    }

    void SetRotation(float Roll)
    {
        Roll = roll;
       
        updateCameraVectors();
    }


    void updateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));

        glm::mat4 rollMatrix = glm::mat4(1.0f);
        rollMatrix = glm::rotate(rollMatrix, glm::radians(Roll), Front);
        Right = glm::mat3(rollMatrix) * Right;
        Up = glm::mat3(rollMatrix) * Up;
    }


  

private:

};
#endif