#include "Cube.h"

Cube::Cube(int x, int y, int z) : x(x), y(y), z(z), VAO(0), VBO(0)
{
	float vertices[] = {
		// Position			Color		//texture
		0.0f, 0.0f, 0.0f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,  0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 1.0f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f,	1.0f,  0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,  0.5f, 0.5f, 1.0f,1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 0.0f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,  0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 1.0f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 1.0f,  0.75f, 0.75f, 1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,  0.75f, 0.75f, 1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,  0.75f, 0.75f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,  0.75f, 0.75f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,  0.75f, 0.75f, 1.0f,0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,  0.75f, 0.75f, 1.0f, 0.0f, 0.0f,

		1.0f, 1.0f, 1.0f,  0.75f, 0.75f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,  0.75f, 0.75f, 1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,  0.75f, 0.75f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,  0.75f, 0.75f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,  0.75f, 0.75f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  0.75f, 0.75f, 1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,  0.75f, 0.75f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,  0.75f, 0.75f, 1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,  0.75f, 0.75f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  0.75f, 0.75f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,  0.75f, 0.75f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,  0.75f, 0.75f, 1.0f, 0.0f, 0.0f

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
Cube::Cube(int x, int y, int z, float r, float g, float b) : x(x), y(y), z(z), VAO(0), VBO(0)
{
	float vertices[] = {
		// Position			Color     texture coordinate
		0.0f, 0.0f, 0.0f,  r,g,b, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,  r,g,b, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,  r,g,b, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f,  r,g,b, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, r,g,b, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,  r,g,b, 0.0f, 0.0f,

		0.0f, 0.0f, 1.0f,  r,g,b, 0.0f, 0.0f,
		1.0f, 0.0f,	1.0f,  r,g,b, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,  r,g,b, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  r,g,b, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,  r,g,b ,1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,  r,g,b, 0.0f, 0.0f,

		0.0f, 0.0f, 0.0f, r,g,b, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,  r,g,b, 1.0f, 0.0f,
		1.0f, 0.0f, 1.0f, r,g,b, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, r,g,b, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, r,g,b, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f, r,g,b, 0.0f, 0.0f,

		0.0f, 1.0f, 1.0f,  0.75f, 0.75f, 1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,  0.75f, 0.75f, 1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,  0.75f, 0.75f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,  0.75f, 0.75f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,  0.75f, 0.75f, 1.0f,0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,  0.75f, 0.75f, 1.0f, 0.0f, 0.0f,

		1.0f, 1.0f, 1.0f,  0.75f, 0.75f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,  0.75f, 0.75f, 1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,  0.75f, 0.75f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,  0.75f, 0.75f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,  0.75f, 0.75f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  0.75f, 0.75f, 1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,  0.75f, 0.75f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,  0.75f, 0.75f, 1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,  0.75f, 0.75f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  0.75f, 0.75f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,  0.75f, 0.75f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,  0.75f, 0.75f, 1.0f, 0.0f, 0.0f

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
Cube::~Cube()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Cube::draw(Shader* shader, unsigned int modelRenderMode, glm::mat4 matrix) {
	shader->use();
	glBindVertexArray(VAO);

	matrix = glm::translate(matrix, glm::vec3(x, y, z));
	shader->setMat4("model", matrix);

	glDrawArrays(modelRenderMode, 0, 36);
}
void Cube::drawTexturedCube(Shader* shader, unsigned int modelRenderMode, glm::mat4 matrix, Texture* atexture) {
	glBindTexture(GL_TEXTURE_2D, atexture->getTextureId());
	//GLuint tex0Uni = glGetUniformLocation(shader->ID, "tex0");
	//glUniform1f(tex0Uni, 1.0f);
	this->draw(shader, modelRenderMode, matrix);

	glBindTexture(GL_TEXTURE_2D, 0);
}
void Cube::setZ(float zVal) {
	z = zVal;

}