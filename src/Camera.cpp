#include "Camera.h"
#include<cmath>


#ifdef DEBUG
#include<iostream>
#endif

Camera::Camera(glm::vec3 pos, float speed, float fov_) :position(pos), cameraSpeed(speed), globalUp(glm::vec3(0.0f, 1.0f, 0.0f)), yaw(90.0f), pitch(0.0f), cameraSensitivity(0.05), fov(fov_)
{
	updateCamera();
#ifdef DEBUG
	std::cout << "Position is now: (" << position.x << ", " << position.y << ", " << position.z << ")"<<std::endl;
#endif
}

void Camera::updateAngles(float x, float y)
{
	yaw += x * cameraSensitivity;
	pitch -= y * cameraSensitivity;
	
	if (pitch >= 90.0f)
		pitch = 90.0f;
	else if (pitch <= -90.0f)
		pitch = -90.0f;

	updateCamera();
}

void Camera::updateFov(float yOffset)
{
	fov -= yOffset;
}

void Camera::updateCamera()
{
	glm::vec3 uTarget = glm::vec3(::cos(glm::radians(yaw))*::cos(glm::radians(pitch)), ::sin(glm::radians(pitch)), ::sin(glm::radians(yaw))*::cos(glm::radians(pitch)));
	
	target = glm::normalize(uTarget);
	right = glm::normalize(glm::cross(target, globalUp));
	up = glm::normalize(glm::cross(right, target));
	
	updateView();
}


void Camera::updatePosition(unsigned int key, float deltaT)
{
	if (key == GLFW_KEY_W)
	{
		position += target * cameraSpeed * deltaT;
	}
	else if (key == GLFW_KEY_A)
	{
		position -= right * cameraSpeed * deltaT;
	}
	else if (key == GLFW_KEY_S)
	{
		position -= target * cameraSpeed * deltaT;
	}
	else if (key == GLFW_KEY_D)
	{
		position += right * cameraSpeed * deltaT;
	}
	updateView();
#ifdef DEBUG
	std::cout << "Position is now: (" << position.x << ", " << position.y << ", " << position.z << ")"<<std::endl;
#endif
}



