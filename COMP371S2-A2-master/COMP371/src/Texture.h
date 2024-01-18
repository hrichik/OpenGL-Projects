#pragma once


#include <glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include "stb_image.h"


class Texture
{
public:
    Texture(std::string texturePath);
    ~Texture();
    GLuint getTextureId();
    GLuint getDepth();
protected:
    GLuint textureId;
    int height, width, depth;
};