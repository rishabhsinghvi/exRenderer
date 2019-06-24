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


const unsigned int SCREEN_WIDTH = 1000;
const unsigned int SCREEN_HEIGHT = 800;

int main()
{
	Camera camera;
	auto window = exRenderer::init(SCREEN_WIDTH, SCREEN_HEIGHT);
	float curTime = 0.0f;

	// build and compile our shader program
	Shader shader("shaders/test.vert", "shaders/test.frag");

	
	float vertices[] = {
		// position           // text coord
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};


	VertexArray va;

	VertexBuffer VBO(vertices, sizeof(vertices));
	IndexBuffer EBO(indices, 6);

	Layout layoutVertices(3, GL_FLOAT, GL_FALSE);
	Layout layoutTexture(2, GL_FLOAT, GL_FALSE);

	va.bindBuffer(VBO, { layoutVertices, layoutTexture });

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	va.unbind();

	Texture tex("textures/test.jpg");

	shader.setUniformInt("texture1", { 0 }, 1);
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// create perspective projection matrix
	//glm::mat4 projectionMatrix = glm::perspective(45.0f, static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), -100.0f, 100.0f);
	glm::mat4 projectionMatrix = glm::ortho(-2.0f, 2.0f, -1.0f, 1.0f, -1.0f, 100.0f);

	while (!glfwWindowShouldClose(window))
	{
		float newTime = static_cast<float>(glfwGetTime());
		float deltaT = newTime - curTime;
		curTime = newTime;

		exRenderer::processUserInput(window, camera, deltaT);

		glClearColor(0.30588f, 0.68627f, 0.84313f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.bind();
		shader.setUniformMatrix4("projMatrix", projectionMatrix);
		shader.setUniformMatrix4("viewMatrix", camera.View);

		va.bind();

		glDrawElements(GL_TRIANGLES, EBO.getCount(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

