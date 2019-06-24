#ifndef EXRENDERER_H
#define EXRENDERER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Camera.h"

#include<iostream>

namespace exRenderer
{
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	GLFWwindow* init(unsigned int SCRWIDTH, unsigned int SCRHEIGHT);
	
	void processUserInput(GLFWwindow *window, Camera& camera, float deltaT);

}

#endif