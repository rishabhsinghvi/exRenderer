#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include<memory>

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "TextureCube.h"
#include "exRenderer.h"
#include "Model.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>


static void processMouseInput(GLFWwindow* window, double newX, double newY);
static void processScrollInput(GLFWwindow* window, double xOffset, double yOffset);

// Globals

const unsigned int SCREEN_WIDTH = 1000;
const unsigned int SCREEN_HEIGHT = 800;

float mousePosX = static_cast<float>(SCREEN_WIDTH) / 2.0f;
float mousePosY = static_cast<float>(SCREEN_HEIGHT) / 2.0f;
	
Camera camera(glm::vec3(0.0f, 0.0f, 30.0f), 20.0f);


int main()
{
	auto window = exRenderer::init(SCREEN_WIDTH, SCREEN_HEIGHT);
	glfwSetCursorPosCallback(window, processMouseInput);
	glfwSetScrollCallback(window, processScrollInput);

	float curTime = 0.0f;



	Model model("models/Flashlight.obj");
	Shader modelShader("shaders/model_loader.vert", "shaders/model_loader.frag");

	while (!glfwWindowShouldClose(window))
	{
		float newTime = static_cast<float>(glfwGetTime());
		float deltaT = newTime - curTime;
		curTime = newTime;

		exRenderer::processUserInput(window, camera, deltaT);


		glClearColor(0.30588f, 0.68627f, 0.84313f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		auto projectionMatrix = glm::perspective(glm::radians(camera.getFov()), static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), 0.00001f, 1000.0f);
		auto viewMatrix = camera.View;

		modelShader.bind();
		modelShader.setUniformMatrix4("projMatrix", projectionMatrix);
		modelShader.setUniformMatrix4("viewMatrix", viewMatrix);

		modelShader.setUniformFloat("lightPos", { 5.0f, 2.0f, 10.0f }, 3);
		modelShader.setUniformFloat("modelColor", { 1.0f,0.0f, 1.0f }, 3);
		modelShader.setUniformFloat("lightColor", { 1.0f, 1.0f, 1.0f }, 3);

		model.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}


void processMouseInput(GLFWwindow * window, double newX, double newY)
{

	{
		float xOffset = static_cast<float>(newX) - mousePosX;
		float yOffset = static_cast<float>(newY) - mousePosY;

		mousePosX = static_cast<float>(newX);
		mousePosY = static_cast<float>(newY);

		camera.updateAngles(xOffset, yOffset);
	}

}

void processScrollInput(GLFWwindow * window, double xOffset, double yOffset)
{
	camera.updateFov(static_cast<float>(yOffset));
}
