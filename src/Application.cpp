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

//#include "json.hpp"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>


static void processMouseInput(GLFWwindow* window, double newX, double newY);
static void processScrollInput(GLFWwindow* window, double xOffset, double yOffset);

// Globals

const unsigned int SCREEN_WIDTH = 1920;
const unsigned int SCREEN_HEIGHT = 1080;

float mousePosX = static_cast<float>(SCREEN_WIDTH) / 2.0f;
float mousePosY = static_cast<float>(SCREEN_HEIGHT) / 2.0f;
	
Camera camera(glm::vec3(11.0f, 15.0f, 11.0f), 20.0f);


int main()
{



	auto window = exRenderer::init(SCREEN_WIDTH, SCREEN_HEIGHT);
	glfwSetCursorPosCallback(window, processMouseInput);
	glfwSetScrollCallback(window, processScrollInput);

	float curTime = 0.0f;

	Model model("models/tex_test/Lamborghini_Aventador.obj");

	Shader modelShader("shaders/model_loader.vert", "shaders/model_loader.frag");
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		float newTime = static_cast<float>(glfwGetTime());
		float deltaT = newTime - curTime;
		curTime = newTime;

		exRenderer::processUserInput(window, camera, deltaT);

		glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
		//glClearColor(0.30588f, 0.68627f, 0.84313f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDepthFunc(GL_LESS);

		auto projectionMatrix = glm::perspective(glm::radians(camera.getFov()), static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), 0.1f, 1000.0f);
		auto viewMatrix = camera.View;
		auto modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25f));
		auto normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
		

		modelShader.bind();
		modelShader.setUniformMatrix4("projMatrix", projectionMatrix);
		modelShader.setUniformMatrix4("viewMatrix", viewMatrix);
		modelShader.setUniformMatrix4("modelMatrix", modelMatrix);
		modelShader.setUniformMatrix3("normalMatrix", normalMatrix);
		

		modelShader.setUniformFloat("light.lightColor", { 1.0f, 1.0f, 1.0f });
		modelShader.setUniformFloat("light.lightPos", { 0.0f, 100.0f, 15.0f });

		modelShader.setUniformFloat("modelColor", {1.0f, 0.0f, 0.0f });
		
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
