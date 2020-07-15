#ifndef TEXT_H
#define TEXT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"



struct Character {
	unsigned int TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	unsigned int Advance;
};

void generateCharacterMap(std::map<char, Character> characters, FT_Face face);
void RenderText(Shader &s, std::string text, float x, float y, float scale, glm::vec3 color, unsigned int& VAO_text, unsigned int& VBO_text, std::map<char, Character>& Characters);

#endif