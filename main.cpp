#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "grid.h"
#include "snake.h"

#include <iostream>
#include <vector>

#include "text.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Snake &snake);

// settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

constexpr unsigned int TICKRATE = 15;
constexpr float SECONDSPERTICK = 1.0f / static_cast<float>(TICKRATE);

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader ourShader("shaders/flatcolor.vs", "shaders/flatcolor.frs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		0.05f, 0.05f, 0.0f,
		0.95f, 0.05f, 0.0f,
		0.95f,  0.95f, 0.0f,
		0.95f,  0.95f, 0.0f,
		0.05f,  0.95f, 0.0f,
		0.05f, 0.05f, 0.0f,
	};
	// world space positions of our cubes 
/*	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(1.0f / 50,  0.0f,  0.0f),
		glm::vec3(2.0f / 50,  0.0f,  0.0f),
		glm::vec3(0.0f,  1.0f / 50,  0.0f),
		glm::vec3(1.0f / 50,  1.0f / 50,  0.0f),
		glm::vec3(2.0f / 50,  1.0f / 50,  0.0f),
		glm::vec3(0.0f,  2.0f / 50,  0.0f),
		glm::vec3(1.0f / 50,  2.0f / 50,  0.0f),
		glm::vec3(2.0f / 50,  2.0f / 50,  0.0f),
		glm::vec3(0.0f / 50,  49.0f / 50,  0.0f),
		glm::vec3(49.0f / 50,  49.0f / 50,  0.0f),
		glm::vec3(49.0f / 50,  0.0f / 50,  0.0f)
	}; 
	std::vector<glm::vec3> cubePositions = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(1.0f / 50,  0.0f,  0.0f),
		glm::vec3(2.0f / 50,  0.0f,  0.0f),
		glm::vec3(0.0f,  1.0f / 50,  0.0f),
		glm::vec3(1.0f / 50,  1.0f / 50,  0.0f),
		glm::vec3(2.0f / 50,  1.0f / 50,  0.0f),
		glm::vec3(0.0f,  2.0f / 50,  0.0f),
		glm::vec3(1.0f / 50,  2.0f / 50,  0.0f),
		glm::vec3(2.0f / 50,  2.0f / 50,  0.0f),
		glm::vec3(0.0f / 50,  49.0f / 50,  0.0f),
		glm::vec3(49.0f / 50,  49.0f / 50,  0.0f),
		glm::vec3(49.0f / 50,  0.0f / 50,  0.0f)
	}; 
	std::vector <std::array<unsigned, 2>> snakePos = {
		{ 0, 0},
		{ 49, 0 },
		{ 49, 49 },
		{ 0, 49 }
	}; */
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float timePassed = 0.0f;
	
	srand(time(NULL));
	

	//Now initialize the font for the game
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return -1;
	}
	FT_Face face;
	if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return -1;
	}
	FT_Set_Pixel_Sizes(face, 0, 48);
	std::map<char, Character> Characters;
	generateCharacterMap(Characters, face);

	//Now unload FreeType resources
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	//Create the text shader
	Shader textShader("shaders/text.vs", "shaders/text.frs");

	//enable blending for text
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	unsigned int VAO_text, VBO_text;
	glGenVertexArrays(1, &VAO_text);
	glGenBuffers(1, &VBO_text);
	glBindVertexArray(VAO_text);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_text);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		Gamestate currentState = PLAYING;
		Grid grid;
		Snake snake(grid.returnDimensions());
		Food food(grid.returnDimensions(), snake.returnSnakePositions());


		// render loop
		// -----------
		while (currentState == PLAYING && !glfwWindowShouldClose(window))
		{
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			timePassed += deltaTime;

			processInput(window, snake);

			while (timePassed >= SECONDSPERTICK)	//Fixed time steps approach
			{

				snake.move();
				snake.checkIfLose(currentState);
				snake.checkIfEatFood(food);
				timePassed -= SECONDSPERTICK;
			}







			// render
			// ------
			glClearColor(0.4f, 0.7f, 0.7f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!




			// activate shader
			ourShader.use();

			createTransformationVectors(ourShader, window);

			// render boxes
			glBindVertexArray(VAO);
			grid.getSnakePositions(snake);
			grid.createModelTransformationVector();
			grid.drawSnakes(ourShader);
			grid.getFoodPosition(food);
			grid.drawFood(ourShader);
			drawBackground(ourShader);

			//render text
			createTransformationVectors(textShader, window);
			glBindVertexArray(VAO_text);
			RenderText(textShader, "Sample Text", 25.0f, 25.0f, 1.0f, glm::vec3(0.2, 0.5f, 0.5f), VAO_text, VBO_text, Characters);


			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, Snake &snake)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		snake.processKeyboard(UP);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		snake.processKeyboard(DOWN);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		snake.processKeyboard(LEFT);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		snake.processKeyboard(RIGHT);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}