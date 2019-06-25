#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "exRenderer.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>


static void processMouseInput(GLFWwindow* window, double newX, double newY);
static void processScrollInput(GLFWwindow* window, double xOffset, double yOffset);

const unsigned int SCREEN_WIDTH = 1000;
const unsigned int SCREEN_HEIGHT = 800;

float mousePosX = static_cast<float>(SCREEN_WIDTH) / 2.0f;
float mousePosY = static_cast<float>(SCREEN_HEIGHT) / 2.0f;

Camera camera;

int main()
{
	auto window = exRenderer::init(SCREEN_WIDTH, SCREEN_HEIGHT);
	glfwSetCursorPosCallback(window, processMouseInput);

	float curTime = 0.0f;


	// build and compile our shader program
	Shader shader("shaders/test.vert", "shaders/test.frag");

	
	/*float vertices[] = {
		// position        //texture  
		0.5f,  0.5f, 5.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 5.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 5.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 5.0f, 0.0f, 1.0f
	};*/

	/*unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};*/

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};


	

	VertexArray va;

	VertexBuffer VBO(vertices, sizeof(vertices), 36);
	//IndexBuffer EBO(indices, 6);

	Layout layoutVertices(3, GL_FLOAT, GL_FALSE);
	Layout layoutTexture(2, GL_FLOAT, GL_FALSE);

	//va.bindBuffer(VBO, { layoutVertices });
	va.bindBuffer(VBO, { layoutVertices, layoutTexture });

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	VBO.unbind();

	va.unbind();

	Texture tex("textures/test.jpg");

	shader.setUniformInt("texture1", { 0 }, 1);
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// create perspective projection matrix

	// for some reason, depth testing doesn't work when near plane is set to 0. So set it to 0.00001
	
	//glm::mat4 projectionMatrix = glm::ortho(-2.0f, 2.0f, -1.0f, 1.0f, -1.0f, 100.0f);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		float newTime = static_cast<float>(glfwGetTime());
		float deltaT = newTime - curTime;
		curTime = newTime;

		exRenderer::processUserInput(window, camera, deltaT);

		glm::mat4 projectionMatrix = glm::perspective(camera.getFov(), static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), 0.00001f, 1000.0f);

		//glClearColor(0.30588f, 0.68627f, 0.84313f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.bind();
		shader.setUniformMatrix4("projMatrix", projectionMatrix);
		shader.setUniformMatrix4("viewMatrix", camera.View);

		va.bind();

//		glDrawElements(GL_TRIANGLES, EBO.getCount(), GL_UNSIGNED_INT, 0);

		VBO.draw();

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
	camera.updateFov(yOffset);
}
