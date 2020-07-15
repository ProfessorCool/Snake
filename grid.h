#ifndef GRID_H
#define GRID_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "food.h"
#include "snake.h"
#include "shader.h"


#include <array>
#include <vector>

void drawBackground(Shader shader, glm::vec3 color = glm::vec3(0.2f, 0.3f, 0.3f));
void createTransformationVectors(Shader shader, GLFWwindow* window);

struct Grid
{
	Grid() = default;

	inline void setSnakePositions(std::vector <std::array<unsigned, 2>> inputSnakePos)
	{
		snakePositions = inputSnakePos;
	}
	void getSnakePositions(Snake snake)
	{
		snakePositions = snake.returnSnakePositions();
	}
	void getFoodPosition(Food food)
	{
		foodPosition = food.returnFoodPosition();
	}
	inline std::array<unsigned, 2> returnDimensions()
	{
		return dimensions;
	}
	void createModelTransformationVector();
	void drawSnakes(Shader shader, glm::vec3 color = glm::vec3(0.9, 0.9, 0.0));
	void drawFood(Shader shader, glm::vec3 color = glm::vec3(0.8, 0.3, 0.3));
private:
	std::array<unsigned, 2> dimensions = { 50, 50 };
	std::array<unsigned, 2> foodPosition;
	std::vector <std::array<unsigned, 2>> snakePositions;
	std::vector<glm::vec3> snakeTransformationVector;
};

#endif
