#pragma once

#ifndef CUBE_H
#define CUBE_H

#include <glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "shader.h"
#include "../../Texture.h"

class Cube
{
public:
	unsigned int ID;

	Cube(int x, int y, int z);
	Cube(int x, int y, int z, float r, float g, float b);
	~Cube();
	void draw(Shader* shader, unsigned int modelRenderMode, glm::mat4 matrix);
	void drawTexturedCube(Shader* shader, unsigned int modelRenderMode, glm::mat4 matrix, Texture* texture);
	void setZ(float z);
protected:
	int x, y, z;
	unsigned int VAO, VBO;
};
#endif