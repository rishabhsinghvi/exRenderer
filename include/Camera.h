#ifndef CAMERA_H
#define CAMERA_H

#include<glm/glm.hpp>
#include<glm/ext/matrix_transform.hpp>

#include "GLFW/glfw3.h"

class Camera
{
private:
	glm::vec3 position;

	glm::vec3 globalUp;

	// Vectors relative to the camera
	glm::vec3 up;
	glm::vec3 target;
	glm::vec3 right;

	// To calculate mouse movements
	float yaw;
	float pitch;
	
	float cameraSpeed;

public:
	glm::mat4 View; // the view matrix
	
public:
	// think it might be a good idea for user-defined globalUp vector; maybe later
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), float speed = 1.0f);
	

	void updatePosition(unsigned int key, float deltaT);


private:
	void updateCamera();

	inline void updateView()
	{
		View = glm::lookAt(position, position + target, up);
	}



	

};


#endif