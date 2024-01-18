#pragma once

#ifndef GRID_H
#define GRID_H

#include <glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "shader.h"
#include "../../Texture.h"

class Grid
{
public:
	unsigned int ID;

	Grid(int size);
	~Grid();
	void draw(Shader* shader);
	void draw(Shader* shader, Texture* texture);
protected:
	int size;
	unsigned int VAO, VBO;
};
#endif