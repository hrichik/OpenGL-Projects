#include "Wall.h"
Wall::Wall(int x, int y, int z) : x(x), y(y), z(z), VAO(0), VBO(0)
{
	float vertices[] = {
		// Position			Color (Gray)
		0.0f, 0.0f, 0.0f,  0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,  0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,  0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f,  0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f,  0.5f, 0.5f, 0.5f,  0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,  0.5f, 0.5f, 0.5f, 0.0f, 0.0f,

		0.0f, 0.0f, 1.0f,  0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		1.0f, 0.0f,	1.0f,  0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,  0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,  0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,  0.5f, 0.5f, 0.5f, 0.0f, 0.0f,

		0.0f, 0.0f, 0.0f,  0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,  0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		1.0f, 0.0f, 1.0f,  0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,  0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,  0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,  0.5f, 0.5f, 0.5f, 0.0f, 0.0f,

		0.0f, 1.0f, 1.0f,  0.75f, 0.75f, 0.75f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,  0.75f, 0.75f, 0.75f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,  0.75f, 0.75f, 0.75f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,  0.75f, 0.75f, 0.75f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,  0.75f, 0.75f, 0.75f,  0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,  0.75f, 0.75f, 0.75f, 0.0f, 0.0f,

		1.0f, 1.0f, 1.0f,  0.75f, 0.75f, 0.75f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,  0.75f, 0.75f, 0.75f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,  0.75f, 0.75f, 0.75f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,  0.75f, 0.75f, 0.75f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,  0.75f, 0.75f, 0.75f,  0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  0.75f, 0.75f, 0.75f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,  0.75f, 0.75f, 0.75f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,  0.75f, 0.75f, 0.75f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,  0.75f, 0.75f, 0.75f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  0.75f, 0.75f, 0.75f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,  0.75f, 0.75f, 0.75f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,  0.75f, 0.75f, 0.75f, 0.0f, 0.0f

	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Wall::~Wall()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Wall::drawWall(Shader* shader, unsigned int modelRenderMode, glm::mat4 matrix) {
	shader->use();
	glBindVertexArray(VAO);

	matrix = glm::translate(matrix, glm::vec3(x, y, z));
	shader->setMat4("model", matrix);

	glDrawArrays(modelRenderMode, 0, 36);
}

void Wall::drawTexturedWall(Shader* shader, unsigned int modelRenderMode, glm::mat4 matrix, Texture* wallTexture) {
	glBindTexture(GL_TEXTURE_2D, wallTexture->getTextureId());
	//GLuint tex0Uni = glGetUniformLocation(shader->ID, "tex0");
	//glUniform1f(tex0Uni, 1.0f);
	this->drawWall(shader, modelRenderMode, matrix);

	glBindTexture(GL_TEXTURE_2D, 0);

}