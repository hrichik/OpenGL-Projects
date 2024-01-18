// COMP 371 Quiz 2
// Summer 2021
// By: Hrichik Sarker (40026502)
//The following code is all mine and my group's, I got the aspects of using the grid and the cube setup from what my group had,
//using it to make the objects visible in the program. In addition, I used the grid, the axis, and the letter movements
//from my group project. Other than that, the texture implementation, skateboard movement, the letters, the camera, the whole setup, was my work.




#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <glm.hpp>

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>
#include "objects/shader.h"
#include "objects/grid.h"
#include "objects/axis.h"
#include "objects/Cube.h" //for the cubes
#include "objects/Wall.h"
#include "../Texture.h" //for texture

#include "stb_image.h"

bool texturesOn = false; //didnt end up using it
 

const int WINDOW_LENGTH = 1024; //windows size
const int WINDOW_WIDTH = 768;

GLFWwindow* window;

unsigned int cubeRenderMode = GL_TRIANGLES; //render mode set for the cubes

//ALL LETTERS NEEDED
unsigned int letter1RenderMode = GL_TRIANGLES;
unsigned int letter2RenderMode = GL_TRIANGLES;
unsigned int letter3RenderMode = GL_TRIANGLES;
unsigned int letter4RenderMode = GL_TRIANGLES;

unsigned int boardRenderMode = GL_TRIANGLES; //board mode render set

glm::vec3 cameraPos = glm::vec3(0.0f, 5.0f, 40.0f); //camera positioning
glm::vec3 cameraFront = glm::vec3(0.0f, 5.0f, -5.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float distance = 40.0f; //distance from center
float camX = 0;
float camZ = 0;
float camY = 0;

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = WINDOW_LENGTH / 2.0f;
float lastY = WINDOW_WIDTH / 2.0f;
float fov = 45.0f;

float angle = 0.0f;

bool cubeModel1 = true; // Press 1 to toogle variable
bool starModel2 = false;
bool thirdModel3 = false;
bool fourthModel4 = false;

//FOR LETTERS, which to move
bool letter1Model1 = false; //toggle letters
bool letter2Model1 = false;
bool letter3Model1 = false;
bool letter4Model1 = false;
bool boardModel1 = false; //toggle board movement
bool boardModel2 = false;
bool boardModelStop = true;

int mCounter = 0;

// Control clockwise & counter-clockwise rotation on X axis
float cubeAngleX = 0.0f;


//FOR THE LETTERS, FOR THEIR ANGLES VALUES ARE SET INTO VARIABLES
float letter1AngleX = 0.0f;
float letter2AngleX = 0.0f;
float letter3AngleX = 0.0f;
float letter4AngleX = 0.0f;
float boardAngleX = 0.0f;

// Control clockwise & counter-clockwise rotation on Y axis
float cubeAngleY = 0.0f;
float starAngleY = 0.0f;
float thirdAngleY = 0.0f;
float fourthAngleY = 0.0f;

//FOR THE LETTERS, FOR THEIR ANGLES VALUES ARE SET INTO VARIABLES
float letter1AngleY = 0.0f;
float letter2AngleY = 0.0f;
float letter3AngleY = 0.0f;
float letter4AngleY = 0.0f;
float boardAngleY = 0.0f;


// Control clockwise & counter-clockwise rotation on Z axis
float cubeAngleZ = 0.0f;
float starAngleZ = 0.0f;
float thirdAngleZ = 0.0f;
float fourthAngleZ = 0.0f;


//FOR THE LETTERS, FOR THEIR ANGLES VALUES ARE SET INTO VARIABLES
float letter1AngleZ = 0.0f;
float letter2AngleZ = 0.0f;
float letter3AngleZ = 0.0f;
float letter4AngleZ = 0.0f;
float boardAngleZ = 0.0f;

float cubeModelScale = 100.0f;



//IN ORDER TO CHANGE THE SIZE / SCALE OF THE OBJECT
float letter1ModelScale = 1.0f;
float letter2ModelScale = 1.0f;
float letter3ModelScale = 1.0f;
float letter4ModelScale = 1.0f;
float boardModelScale = 1.0f;

float cubeModelX = 0.0f, cubeModelY = 0.0f, cubeModelZ = 0.0f;


float letter1ModelX = 0.0f, letter1ModelY = 0.0f, letter1ModelZ = 0.0f;
float letter2ModelX = 0.0f, letter2ModelY = 0.0f, letter2ModelZ = 0.0f;
float letter3ModelX = 0.0f, letter3ModelY = 0.0f, letter3ModelZ = 0.0f;
float letter4ModelX = 0.0f, letter4ModelY = 0.0f, letter4ModelZ = 0.0f;
float boardModelX = 0.0f, boardModelY = 0.0f, boardModelZ = 0.0f;

float moveX, moveY = 0.0f;
float scale = 1.0f;
float rotation = 0.0f;

float depth1;
float depth2;
// Will be used when process the input of the user. Will use mouse movement
// on the x direction to pan
void mouseHorizontal(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	lastX = xPos;

	float sensitivity = 0.1f;
	xOffset *= sensitivity;

	yaw += xOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 directions;
	directions.x = cos(glm::radians(yaw));
	directions.y = cameraFront.y;
	directions.z = sin(glm::radians(yaw));
	cameraFront.x += directions.x;
	cameraFront.z += directions.z;
}

// Will be used when process the input of the user. Will use mouse movement
// on the y direction to tilt
void mouseVertical(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	float sensitivity = 1.0f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront.y += direction.y;
}

// Will use this function when will want to zoom into/out of scene when 
// process the user input
void mouseZoom(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float yOffset = lastY - yPos;
	lastY = yPos;

	float sensitivity = 0.1f;
	yOffset *= sensitivity;

	fov -= yOffset;

	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 90.0f)
		fov = 90.0f;
}

// Following method handles the input for each model
void processUserInput(GLFWwindow* window)
{
	// User can select a model by pressing a key from 1 to 4
	// If user presses 1, look at NUMBER 4

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)  //letter 1
	{
		letter1Model1 = true;
		letter2Model1 = false;
		letter3Model1 = false;
		letter4Model1 = false;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) //letter 2
	{
		letter2Model1 = true;
		letter1Model1 = false;
		letter3Model1 = false;
		letter4Model1 = false;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) //letter 3
	{
		letter3Model1 = true;
		letter1Model1 = false;
		letter2Model1 = false;
		letter4Model1 = false;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) //letter 4
	{
		letter4Model1 = true;
		letter1Model1 = false;
		letter2Model1 = false;
		letter3Model1 = false;
	}

	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) //move skateboard one way
	{
		letter4Model1 = false;
		letter1Model1 = false;
		letter2Model1 = false;
		letter3Model1 = false;
		boardModel1 = true;
		boardModel2 = false;
		boardModelStop = false;
	}

	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)  //move the skateboard the other way
	{
		letter4Model1 = false;
		letter1Model1 = false;
		letter2Model1 = false;
		letter3Model1 = false;
		boardModel1 = true;
		boardModel2 = true;
		boardModelStop = false;

	}

	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) //stop the skateboard
	{
		letter4Model1 = false;
		letter1Model1 = false;
		letter2Model1 = false;
		letter3Model1 = false;
		boardModel1 = true;
		boardModel2 = true;
		boardModelStop = true;

	}


	if (letter1Model1) { //if its first letter
		letter2Model1 = false;
		letter3Model1 = false;
		letter4Model1 = false;
		// d replaced by O-> rotate right 5 degrees
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
			letter1AngleY += 5.0f;
		}
		// a replaced by I -> rotate left 5 degrees
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
			letter1AngleY -= 5.0f;
		}

		// Control the model position & orientation using keyboard input
		// D -> Move right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			letter1ModelX += 1.0f;
		}
		// A -> Move left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			letter1ModelX -= 1.0f;
		}
		// S -> Mode Down
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			letter1ModelY -= 1.0f;
		}
		// W -> Move up
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			letter1ModelY += 1.0f;
		}

		// Move model along z axis
		// Z -> Small move to back
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
			letter1ModelZ -= 1.0f;
		}
		// X -> Continuous move to back
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
			letter1ModelZ -= 2.0f;
		}
		// C -> Small move to front
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
			letter1ModelZ += 1.0f;
		}
		// V -> Continuous move to front
		if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
			letter1ModelZ += 2.0f;
		}

		// Provide functionality for rotating the object around all axes
		// T -> Rotate clockwise on X axis
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
			letter1AngleX += 1.0f;
		}
		// G -> Rotate counter-clockwise on X axis
		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
			letter1AngleX -= 1.0f;
		}
		// H -> Rotate clockwise on Y axis
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
			letter1AngleY += 1.0f;
		}
		// F -> Rotate counter-clockwise on Y axis
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
			letter1AngleY -= 1.0f;
		}
		// Y -> Rotate clockwise on Z axis
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
			letter1AngleZ += 1.0f;
		}
		// R -> Rotate counter-clockwise on Z axis
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		    letter1AngleZ -= 1.0f;
		}

		// User can incrementally size up the model
		// Press 'U' to scale up
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && scale <= 3.0f) {
			// Put limit to scale so the object doesn't get to big & gets shown upside down
			letter1ModelScale += 0.1f;
		}
		// Press 'J' to scale down
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && scale >= 1.0f) {
			// Put limit so object isn't shown too small. It's going to be smallest size for object
			letter1ModelScale -= 0.1f;
		}

		// User can change rendering mode for the models
		// Press P for points
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
			letter1RenderMode = GL_POINTS;
		}
		// Press L for lines
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			letter1RenderMode = GL_LINES;
		}
		// Press T for triangles
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
			letter1RenderMode = GL_TRIANGLES;
		}
	}

	if (letter2Model1) {
		letter1Model1 = false;
		letter3Model1 = false;
		letter4Model1 = false;
		// d replaced by O-> rotate right 5 degrees
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
			letter2AngleY += 5.0f;
		}
		// a replaced by I -> rotate left 5 degrees
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
			letter2AngleY -= 5.0f;
		}

		// Control the model position & orientation using keyboard input
		// D -> Move right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			letter2ModelX += 1.0f;
		}
		// A -> Move left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			letter2ModelX -= 1.0f;
		}
		// S -> Mode Down
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			letter2ModelY -= 1.0f;
		}
		// W -> Move up
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			letter2ModelY += 1.0f;
		}

		// Move model along z axis
		// Z -> Small move to back
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
			letter2ModelZ -= 1.0f;
		}
		// X -> Continuous move to back
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
			letter2ModelZ -= 2.0f;
		}
		// C -> Small move to front
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
			letter2ModelZ += 1.0f;
		}
		// V -> Continuous move to front
		if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
			letter2ModelZ += 2.0f;
		}

		// Provide functionality for rotating the object around all axes
		// T -> Rotate clockwise on X axis
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
			letter2AngleX += 1.0f;
		}
		// G -> Rotate counter-clockwise on X axis
		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
			letter2AngleX -= 1.0f;
		}
		// H -> Rotate clockwise on Y axis
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
			letter2AngleY += 1.0f;
		}
		// F -> Rotate counter-clockwise on Y axis
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
			letter2AngleY -= 1.0f;
		}
		// Y -> Rotate clockwise on Z axis
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
			letter2AngleZ += 1.0f;
		}
		// R -> Rotate counter-clockwise on Z axis
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			letter2AngleZ -= 1.0f;
		}

		// User can incrementally size up the model
		// Press 'U' to scale up
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && scale <= 3.0f) {
			// Put limit to scale so the object doesn't get to big & gets shown upside down
			letter2ModelScale += 0.1f;
		}
		// Press 'J' to scale down
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && scale >= 1.0f) {
			// Put limit so object isn't shown too small. It's going to be smallest size for object
			letter2ModelScale -= 0.1f;
		}

		// User can change rendering mode for the models
		// Press P for points
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
			letter2RenderMode = GL_POINTS;
		}
		// Press L for lines
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			letter2RenderMode = GL_LINES;
		}
		// Press T for triangles
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
			letter2RenderMode = GL_TRIANGLES;
		}
	}

	if (letter3Model1) {
		letter2Model1 = false;
		letter1Model1 = false;
		letter4Model1 = false;
		// d replaced by O-> rotate right 5 degrees
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
			letter3AngleY += 5.0f;
		}
		// a replaced by I -> rotate left 5 degrees
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
			letter3AngleY -= 5.0f;
		}

		// Control the model position & orientation using keyboard input
		// D -> Move right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			letter3ModelX += 1.0f;
		}
		// A -> Move left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			letter3ModelX -= 1.0f;
		}
		// S -> Mode Down
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			letter3ModelY -= 1.0f;
		}
		// W -> Move up
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			letter3ModelY += 1.0f;
		}

		// Move model along z axis
		// Z -> Small move to back
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
			letter3ModelZ -= 1.0f;
		}
		// X -> Continuous move to back
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
			letter3ModelZ -= 2.0f;
		}
		// C -> Small move to front
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
			letter3ModelZ += 1.0f;
		}
		// V -> Continuous move to front
		if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
			letter3ModelZ += 2.0f;
		}

		// Provide functionality for rotating the object around all axes
		// T -> Rotate clockwise on X axis
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
			letter3AngleX += 1.0f;
		}
		// G -> Rotate counter-clockwise on X axis
		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
			letter3AngleX -= 1.0f;
		}
		// H -> Rotate clockwise on Y axis
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
			letter3AngleY += 1.0f;
		}
		// F -> Rotate counter-clockwise on Y axis
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
			letter3AngleY -= 1.0f;
		}
		// Y -> Rotate clockwise on Z axis
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
			letter3AngleZ += 1.0f;
		}
		// R -> Rotate counter-clockwise on Z axis
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			letter3AngleZ -= 1.0f;
		}

		// User can incrementally size up the model
		// Press 'U' to scale up
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && scale <= 3.0f) {
			// Put limit to scale so the object doesn't get to big & gets shown upside down
			letter3ModelScale += 0.1f;
		}
		// Press 'J' to scale down
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && scale >= 1.0f) {
			// Put limit so object isn't shown too small. It's going to be smallest size for object
			letter3ModelScale -= 0.1f;
		}

		// User can change rendering mode for the models
		// Press P for points
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
			letter3RenderMode = GL_POINTS;
		}
		// Press L for lines
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			letter3RenderMode = GL_LINES;
		}
		// Press T for triangles
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
			letter3RenderMode = GL_TRIANGLES;
		}
	}

	if (letter4Model1) {
		letter2Model1 = false;
		letter3Model1 = false;
		letter1Model1 = false;
		// d replaced by O-> rotate right 5 degrees
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
			letter4AngleY += 5.0f;
		}
		// a replaced by I -> rotate left 5 degrees
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
			letter4AngleY -= 5.0f;
		}

		// Control the model position & orientation using keyboard input
		// D -> Move right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			letter4ModelX += 1.0f;
		}
		// A -> Move left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			letter4ModelX -= 1.0f;
		}
		// S -> Mode Down
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			letter4ModelY -= 1.0f;
		}
		// W -> Move up
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			letter4ModelY += 1.0f;
		}

		// Move model along z axis
		// Z -> Small move to back
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
			letter4ModelZ -= 1.0f;
		}
		// X -> Continuous move to back
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
			letter4ModelZ -= 2.0f;
		}
		// C -> Small move to front
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
			letter4ModelZ += 1.0f;
		}
		// V -> Continuous move to front
		if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
			letter4ModelZ += 2.0f;
		}

		// Provide functionality for rotating the object around all axes
		// T -> Rotate clockwise on X axis
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
			letter4AngleX += 1.0f;
		}
		// G -> Rotate counter-clockwise on X axis
		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
			letter4AngleX -= 1.0f;
		}
		// H -> Rotate clockwise on Y axis
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
			letter4AngleY += 1.0f;
		}
		// F -> Rotate counter-clockwise on Y axis
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
			letter4AngleY -= 1.0f;
		}
		// Y -> Rotate clockwise on Z axis
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
			letter4AngleZ += 1.0f;
		}
		// R -> Rotate counter-clockwise on Z axis
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			letter4AngleZ -= 1.0f;
		}

		// User can incrementally size up the model
		// Press 'U' to scale up
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && scale <= 3.0f) {
			// Put limit to scale so the object doesn't get to big & gets shown upside down
			letter4ModelScale += 0.1f;
		}
		// Press 'J' to scale down
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && scale >= 1.0f) {
			// Put limit so object isn't shown too small. It's going to be smallest size for object
			letter4ModelScale -= 0.1f;
		}

		// User can change rendering mode for the models
		// Press P for points
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
			letter4RenderMode = GL_POINTS;
		}
		// Press L for lines
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			letter4RenderMode = GL_LINES;
		}
		// Press T for triangles
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
			letter4RenderMode = GL_TRIANGLES;
		}
	}


	// If user press 'Escape' key, then close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// World orientation changed using arrows
	// Left arrow -> Rx
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		cameraPos = glm::vec3(sin(camX) * distance, cameraPos.y, cos(camZ) * distance);
		camX -= 0.1f;
		camZ -= 0.1f;
		//cameraPos += 1.0f * -glm::normalize(glm::cross(cameraFront, cameraUp));

	}
	// Right arrow -> R-x
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		cameraPos = glm::vec3(sin(camX) * distance, cameraPos.y, cos(camZ) * distance);
		camX += 0.1f;
		camZ += 0.1f;
		//cameraPos += 1.0f * glm::normalize(glm::cross(cameraFront, cameraUp));
	}
	// Up arrow -> Ry
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		//cameraPos = glm::vec3(cameraPos.x, (sin(camY) * distance), cameraPos.z);
		//camY += 0.1f;
		//camZ += 0.1f;
		cameraPos += 1.0f * cameraUp;
	}
	// Down arrow -> R-y
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		//cameraPos = glm::vec3(cameraPos.x, (sin(camY) * distance), cameraPos.z);
		//camY -= 0.1f;
		//camZ -= 0.1f;
		cameraPos += 1.0f * -cameraUp;
	}

	// Pressing B IS CAMERA 1
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		cameraPos = glm::vec3(0.0f, 30.0f, 48.0f);
		cameraFront = glm::vec3(0.0f, 5.0f, -5.0f);
		
	} //PRESSING N IS CAMERA 2
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		cameraPos = glm::vec3(0.0f, 5.0f, 0.0f);
		cameraFront = glm::vec3(0.0f, 5.0f, 5.0f);

	} //PRESSING M IS CAMERA 3
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		
		if (mCounter == 0) {
			cameraPos = glm::vec3(-45.0f, 60.0f, 48.0f);
			cameraFront = glm::vec3(0.0f, 5.0f, -5.0f);
			mCounter += 1;
		}
		else if (mCounter == 1) 
		{
			cameraPos = glm::vec3(45.0f, 60.0f, 48.0f);
			cameraFront = glm::vec3(0.0f, 5.0f, -5.0f);
			mCounter += 1;
		}
		else if (mCounter == 2)
		{
			cameraPos = glm::vec3(45.0f, 60.0f, -48.0f);
			cameraFront = glm::vec3(0.0f, 5.0f, 5.0f);
			mCounter += 1;
		}
		else if (mCounter == 3)
		{
			cameraPos = glm::vec3(-45.0f, 60.0f, -48.0f);
			cameraFront = glm::vec3(0.0f, 5.0f, 5.0f);
			mCounter = 0;
		}
	}

	// User can pan and tilt the camera
	// Right button pressed -> uses mouse movement in x direction to pan
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwSetCursorPosCallback(window, mouseHorizontal);
	}
	// When the user releases the right button, will stop moving in x direction
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);
		glfwSetCursorPosCallback(window, NULL);
	}

	// Pressing the middle button doesn't work, doesn't do anything
	// Middle button pressed -> use mouse movement in y direction to tilt
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwSetCursorPosCallback(window, mouseVertical);
	}

	// User can zoom in and out of the scene using camera perspective
	// While left button pressed -> use mouse movement to move into/out of the scene
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwSetCursorPosCallback(window, mouseZoom);
	}
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);		//setup Viewport size
}



int main(void)
{
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(WINDOW_LENGTH, WINDOW_WIDTH, "COMP371QUIZ2", NULL, NULL);

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
	//set shader for texture and grid
	Shader* shader = new Shader("src/shaders/shader.vs", "src/shaders/shader.fs");
	Shader* textureShader = new Shader("src/shaders/textureShader.vs", "src/shaders/textureShader.fs");
	Shader* gridShader = new Shader("src/shaders/gridShader.vs", "src/shaders/gridShader.fs");


	//set shader pictures
	Texture* wallTexture = new Texture("src/textures/brick.jpg");
	Texture* modelTexture = new Texture("src/textures/6793961.png");
	Texture* floorTexture = new Texture("src/textures/tile.jpg");
	Texture* wall1Texture = new Texture("src/textures/metal.jpg");
	Texture* wall2Texture = new Texture("src/textures/wall2.png");
	Texture* wall3Texture = new Texture("src/textures/wall3.png");

	Grid* grid = new Grid(100);
	Axis* axis = new Axis(5);

	Cube* setWorldCube[] = {
		// Draw WORLD
		new Cube(0,0,0,0.5,0,0.5)

	};
	//CREATE THE LETTERS EACH
	Cube* letter1[] = {
		//NUMBER 4, VERTICAL BY 5
		new Cube(1,0,0,0.54,0.54,0.1), new Cube(1,1,0,0.54,0.54,0.1),new Cube(1,2,0,0.54,0.54,0.1),
		new Cube(1,3,0,0.54,0.54,0.1), new Cube(1,4,0,0.54,0.54,0.1),
		//HORIZONTAL BY 3
		new Cube(0,2,0,0.54,0.54,0.1), new Cube(-1,2,0,0.54,0.54,0.1),
		//VERTICAL BY 3
		new Cube(-1,2,0,0.54,0.54,0.1),new Cube(-1,3,0,0.54,0.54,0.1),new Cube(-1,4,0,0.54,0.54,0.1)

	};

	Cube* letter2[] = {
		//NUMBER 0, VERTICAL BY 5
		new Cube(1,0,0,0,0.8,0.3), new Cube(1,1,0,0,0.8,0.3), new Cube(1,2,0,0,0.8,0.3), new Cube(1,3,0,0,0.8,0.3),
		new Cube(1,4,0,0,0.8,0.3),

		new Cube(0,0,0,0,0.8,0.3), new Cube(-1,0,0,0,0.8,0.3),

		new Cube(-1,1,0,0,0.8,0.3),new Cube(-1,2,0,0,0.8,0.3), new Cube(-1,3,0,0,0.8,0.3),new Cube(-1,4,0,0,0.8,0.3),

		new Cube(0,4,0,0,0.8,0.3), new Cube(-1,4,0,0,0.8,0.3),
	};

	Cube* letter3[] = {

		new Cube(1,0,0,0.9,0.2,0), new Cube(0,0,0,0.9,0.2,0), new Cube(-1,0,0,0.9,0.2,0),


		new Cube(-1,1,0,0.9,0.2,0), new Cube(-1,2,0,0.9,0.2,0),

		new Cube(0,2,0,0.9,0.2,0), new Cube(1,2,0,0.9,0.2,0),

		new Cube(1,3,0,0.9,0.2,0), new Cube(1,4,0,0.9,0.2,0),

		new Cube(0,4,0,0.9,0.2,0), new Cube(-1,4,0,0.9,0.2,0)

	};

	Cube* letter4[] = {

		new Cube(-1,0,0,0.1,0.9,0.4), new Cube(-1,1,0,0.1,0.9,0.4), new Cube(-1,2,0,0.1,0.9,0.4), new Cube(-1,3,0,0.1,0.9,0.4),
		new Cube(-1,4,0,0.1,0.9,0.4),

		new Cube(0,0,0,0.1,0.9,0.4), new Cube(1,0,0,0.1,0.9,0.4),

		new Cube(1,1,0,0.1,0.9,0.4), new Cube(1,2,0,0.1,0.9,0.4),

		new Cube(0,2,0,0.1,0.9,0.4),

		new Cube(0,4,0,0.1,0.9,0.4), new Cube(1,4,0,0.1,0.9,0.4)



	};

	Cube* board[] = {
	    new Cube(-5,1,15,0,0,0), new Cube(-4,1,15,0,0,0),new Cube(-3,1,15,0,0,0),new Cube(-2,1,15,0,0,0),new Cube(-1,1,15,0,0,0),
		new Cube(0,1,15,0,0,0),new Cube(1,1,15,0,0,0),new Cube(2,1,15,0,0,0),new Cube(3,1,15,0,0,0),new Cube(4,1,15,0,0,0),
		new Cube(5,1,15,0,0,0),
	
		new Cube(-5,1,16,0,0,0), new Cube(-4,1,16,0,0,0),new Cube(-3,1,16,0,0,0),new Cube(-2,1,16,0,0,0),new Cube(-1,1,16,0,0,0),
		new Cube(0,1,16,0,0,0),new Cube(1,1,16,0,0,0),new Cube(2,1,16,0,0,0),new Cube(3,1,16,0,0,0),new Cube(4,1,16,0,0,0),
		new Cube(5,1,16,0,0,0),

		new Cube(-5,1,17,0,0,0), new Cube(-4,1,17,0,0,0),new Cube(-3,1,17,0,0,0),new Cube(-2,1,17,0,0,0),new Cube(-1,1,17,0,0,0),
		new Cube(0,1,17,0,0,0),new Cube(1,1,17,0,0,0),new Cube(2,1,17,0,0,0),new Cube(3,1,17,0,0,0),new Cube(4,1,17,0,0,0),
		new Cube(5,1,17,0,0,0),

		new Cube(-3,0,15,1,1,1), new Cube(-3,0,17,1,1,1),new Cube(3,0,15,1,1,1), new Cube(3,0,17,1,1,1)
	};

	glEnable(GL_DEPTH_TEST);
	cubeModel1 = true;
	//Shader shaderProgram("src/shaders/shader.vs", "src/shaders/shader.fs");

	//Texture popCat("wall1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//popCat.texUnit(*shader,"tex0", 0);
	double crntTime;
	double prevTime = glfwGetTime();


	while (!glfwWindowShouldClose(window))
	{
		
		

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//popCat.Bind();
		
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)WINDOW_LENGTH / (float)WINDOW_WIDTH, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(cameraPos, cameraFront, cameraUp);

		shader->setMat4("projection", projection);
		shader->setMat4("view", view);


		gridShader->use();
		gridShader->setMat4("projection", projection);
		gridShader->setMat4("view", view);

		textureShader->use();
		textureShader->setMat4("projection", projection);
		textureShader->setMat4("view", view);
		glActiveTexture(0);
		grid->draw(gridShader, floorTexture);



		axis->draw(shader);

		glm::mat4 modelCube = glm::mat4(1.0f);
		modelCube = glm::translate(modelCube, glm::vec3(cubeModelX-50, cubeModelY, cubeModelZ-50));
		modelCube = glm::rotate(modelCube, glm::radians(cubeAngleX), glm::vec3(1.0f, 0.0, 0.0)); // Rotate on X axis
		modelCube = glm::rotate(modelCube, glm::radians(cubeAngleY), glm::vec3(0.0, 1.0f, 0.0)); // Rotate on Y axis
		modelCube = glm::rotate(modelCube, glm::radians(cubeAngleZ), glm::vec3(0.0, 0.0, 1.0f)); // Rotate on Z axis
		modelCube = glm::scale(modelCube, glm::vec3(cubeModelScale, cubeModelScale, cubeModelScale));

		//glm::mat4 modelWall = glm::mat4(1.0f);
		//modelWall = glm::translate(modelWall, glm::vec3(heartWallX + 30, heartWallY, heartWallZ - 30));
		//modelWall = glm::rotate(modelWall, glm::radians(angle), glm::vec3(0.0, 1.0f, 0.0));
		//modelWall = glm::scale(modelWall, glm::vec3(heartModelScale, heartModelScale, heartModelScale));

		for (int i = 0; i < sizeof(setWorldCube) / sizeof(setWorldCube[0]); i++) {
			setWorldCube[i]->drawTexturedCube(textureShader, cubeRenderMode, modelCube, modelTexture);
		}

		//LETTER 1 AND RENDERING IT
		glm::mat4 letter1Model = glm::mat4(1.0f);
		letter1Model = glm::translate(letter1Model, glm::vec3(letter1ModelX - 15, letter1ModelY+1, letter1ModelZ));
		letter1Model = glm::rotate(letter1Model, glm::radians(letter1AngleX), glm::vec3(1.0f, 0.0, 0.0)); // Rotate on X axis
		letter1Model = glm::rotate(letter1Model, glm::radians(letter1AngleY), glm::vec3(0.0, 1.0f, 0.0)); // Rotate on Y axis
		letter1Model = glm::rotate(letter1Model, glm::radians(letter1AngleZ), glm::vec3(0.0, 0.0, 1.0f)); // Rotate on Z axis
		letter1Model = glm::scale(letter1Model, glm::vec3(letter1ModelScale, letter1ModelScale, letter1ModelScale));

		for (int i = 0; i < sizeof(letter1) / sizeof(letter1[0]); i++) {
			letter1[i]->drawTexturedCube(textureShader, letter1RenderMode, letter1Model, wallTexture);
		}

		//LETTER 2 AND RENDERING IT
		glm::mat4 letter2Model = glm::mat4(1.0f);
		letter2Model = glm::translate(letter2Model, glm::vec3(letter2ModelX - 5, letter2ModelY+1, letter2ModelZ));
		letter2Model = glm::rotate(letter2Model, glm::radians(letter2AngleX), glm::vec3(1.0f, 0.0, 0.0)); // Rotate on X axis
		letter2Model = glm::rotate(letter2Model, glm::radians(letter2AngleY), glm::vec3(0.0, 1.0f, 0.0)); // Rotate on Y axis
		letter2Model = glm::rotate(letter2Model, glm::radians(letter2AngleZ), glm::vec3(0.0, 0.0, 1.0f)); // Rotate on Z axis
		letter2Model = glm::scale(letter2Model, glm::vec3(letter2ModelScale, letter2ModelScale, letter2ModelScale));

		for (int i = 0; i < sizeof(letter2) / sizeof(letter2[2]); i++) {
			letter2[i]->drawTexturedCube(textureShader, letter2RenderMode, letter2Model, wall1Texture);
		}

		//LETTER 3 AND RENDERING IT
		glm::mat4 letter3Model = glm::mat4(1.0f);
		letter3Model = glm::translate(letter3Model, glm::vec3(letter3ModelX + 5, letter3ModelY+1, letter3ModelZ));
		letter3Model = glm::rotate(letter3Model, glm::radians(letter3AngleX), glm::vec3(1.0f, 0.0, 0.0)); // Rotate on X axis
		letter3Model = glm::rotate(letter3Model, glm::radians(letter3AngleY), glm::vec3(0.0, 1.0f, 0.0)); // Rotate on Y axis
		letter3Model = glm::rotate(letter3Model, glm::radians(letter3AngleZ), glm::vec3(0.0, 0.0, 1.0f)); // Rotate on Z axis
		letter3Model = glm::scale(letter3Model, glm::vec3(letter3ModelScale, letter3ModelScale, letter3ModelScale));

		for (int i = 0; i < sizeof(letter3) / sizeof(letter3[0]); i++) {
			letter3[i]->drawTexturedCube(textureShader, letter3RenderMode, letter3Model, wall2Texture);
		}

		//LETTER 4 AND RENDERING IT
		glm::mat4 letter4Model = glm::mat4(1.0f);
		letter4Model = glm::translate(letter4Model, glm::vec3(letter4ModelX + 15, letter4ModelY+1, letter4ModelZ));
		letter4Model = glm::rotate(letter4Model, glm::radians(letter4AngleX), glm::vec3(1.0f, 0.0, 0.0)); // Rotate on X axis
		letter4Model = glm::rotate(letter4Model, glm::radians(letter4AngleY), glm::vec3(0.0, 1.0f, 0.0)); // Rotate on Y axis
		letter4Model = glm::rotate(letter4Model, glm::radians(letter4AngleZ), glm::vec3(0.0, 0.0, 1.0f)); // Rotate on Z axis
		letter4Model = glm::scale(letter4Model, glm::vec3(letter4ModelScale, letter4ModelScale, letter4ModelScale));

		for (int i = 0; i < sizeof(letter4) / sizeof(letter4[0]); i++) {
			letter4[i]->drawTexturedCube(textureShader, letter4RenderMode, letter4Model, wall3Texture);
		}

		//BOARD AND RENDERING IT
		glm::mat4 boardModel = glm::mat4(1.0f);
			
		if (boardModel1) {
			crntTime = glfwGetTime();
			if (crntTime - prevTime >= 1 / 60)
			{

				if (!boardModel2 && !boardModelStop) {
					rotation += 1.0f;
				}
				else if (boardModel2 && !boardModelStop)
				{
					rotation -= 1.0f;
				}
				
				prevTime = crntTime;
			}
			
				boardModel = glm::rotate(boardModel, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
				boardModel = glm::translate(boardModel, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else {
			boardModel = glm::translate(boardModel, glm::vec3(boardModelX, boardModelY + 1, boardModelZ));
			boardModel = glm::rotate(boardModel, glm::radians(boardAngleX), glm::vec3(1.0f, 0.0, 0.0)); // Rotate on X axis
			boardModel = glm::rotate(boardModel, glm::radians(boardAngleY), glm::vec3(0.0, 1.0f, 0.0)); // Rotate on Y axis
			boardModel = glm::rotate(boardModel, glm::radians(boardAngleZ), glm::vec3(0.0, 0.0, 1.0f)); // Rotate on Z axis
			boardModel = glm::scale(boardModel, glm::vec3(boardModelScale, boardModelScale, boardModelScale));

		
		}

	

		for (int i = 0; i < sizeof(board) / sizeof(board[0]); i++) {
			board[i]->draw(shader, boardRenderMode, boardModel);
		}

		processUserInput(window);


		if (angle == 360.0f)
			angle = 0.0f;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//popCat.Delete();
	delete grid;
	delete shader;
	delete textureShader;
	delete gridShader;
	glfwTerminate();
	return 0;
}