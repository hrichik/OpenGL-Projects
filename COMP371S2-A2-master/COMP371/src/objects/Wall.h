#pragma once

#ifndef WALL_H
#define WALL_H

#include <glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "shader.h"
#include "../../Texture.h"

class Wall {
public:
	unsigned int ID;

	Wall(int x, int y, int z);
	~Wall();
	void drawWall(Shader* shader, unsigned int modelRenderMode, glm::mat4 matrix);
	void drawTexturedWall(Shader* shader, unsigned int modelRenderMode, glm::mat4 matrix, Texture* texture);

protected:
	int x, y, z;
	unsigned int VAO, VBO;

};
#endif