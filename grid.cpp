#include "grid.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Grid::createModelTransformationVector()
{
	std::vector<glm::vec3> transformationVector;
	for (const auto &coords : snakePositions)
	{
		float x = static_cast<float>(coords[0]);
		float y = static_cast<float>(coords[1]);
		glm::vec3 positions(x / static_cast<float>(dimensions[0]), y / static_cast<float>(dimensions[1]), 0.0f);
		transformationVector.push_back(positions);
	}
	snakeTransformationVector = transformationVector;
}
void Grid::drawSnakes(Shader shader, glm::vec3 color)
{
	for (const auto &coords : snakeTransformationVector)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, coords);
		model = glm::scale(model, glm::vec3(1.0f / 50, 1.0f / 50, 1.0f / 50));

		shader.setMat4("model", model);
		shader.setVec3("ourColor", color);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
void drawBackground(Shader shader, glm::vec3 color)
{
	//render background for snake
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::scale(model, glm::vec3(1.0f / 0.9f, 1.0f / 0.9f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.05f, -0.05f, -1.0f));
	shader.setMat4("model", model);
	shader.setVec3("ourColor", color);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}
void createTransformationVectors(Shader shader, GLFWwindow* window)
{
	int scrWidth, scrHeight;
	glfwGetWindowSize(window, &scrWidth, &scrHeight);

	// create transformations
	glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(0.0f, static_cast<float>(scrWidth) / static_cast<float>(scrHeight), 0.0f, 1.0f, 0.1f, 100.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	// pass transformation matrices to the shader
	shader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shader.setMat4("view", view);
}
void Grid::drawFood(Shader shader, glm::vec3 color)
{
	float x = static_cast<float>(foodPosition[0]);
	float y = static_cast<float>(foodPosition[1]);
	glm::vec3 positions(x / static_cast<float>(dimensions[0]), y / static_cast<float>(dimensions[1]), 0.0f);
	
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, positions);
	model = glm::scale(model, glm::vec3(1.0f / 50, 1.0f / 50, 1.0f / 50));

	shader.setMat4("model", model);
	shader.setVec3("ourColor", color);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}