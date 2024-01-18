#include <glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include <iostream>
#include "objects/shader.h"
#include "objects/grid.h"
#include "objects/axis.h"

const int WINDOW_LENGTH = 1024;
const int WINDOW_WIDTH = 768;

GLFWwindow* window;

unsigned int modelRenderMode = GL_TRIANGLES;
glm::vec3 cameraPos = glm::vec3(0.0f, 5.0f, 20.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float distance = 20.0f;
float camX = 0;
float camZ = 0;
float camY = 0;

void mouse_callback_horizontal(GLFWwindow* window, double xpos, double ypos);
void mouse_callback_vertical(GLFWwindow* window, double xpos, double ypos);

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = WINDOW_LENGTH/ 2.0f;
float lastY = WINDOW_WIDTH / 2.0f;
float fov = 45.0f;

float angle = 0.0f;
float moveX, moveY = 0.0f;
float scale = 1.0f;



void mouse_callback_vertical(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}


	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront.y += direction.y;
}



void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(void)
{
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(WINDOW_LENGTH, WINDOW_WIDTH, "Assignment 1 - COMP 371", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    unsigned int VBO = 0, VAO = 0;

	Shader *shader = new Shader("src/shaders/shader.vs", "src/shaders/shader.fs");

	Grid *grid = new Grid(100);
	Axis *axis = new Axis(5);

	
	glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)WINDOW_LENGTH / (float)WINDOW_WIDTH, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(cameraPos, cameraFront, cameraUp);

		shader->setMat4("projection", projection);
		shader->setMat4("view", view);
		
		grid->draw(shader);
		axis->draw(shader);
		

		if (angle == 360.0f)
			angle = 0.0f;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	delete grid;
	delete shader;

    glfwTerminate();
    return 0;
}