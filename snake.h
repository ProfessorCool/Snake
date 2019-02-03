#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <array>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "food.h"


enum Snake_Movement {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum Gamestate {
	PLAYING,
	GAMEOVER
};

bool areDirectionsOpposite(Snake_Movement dir1, Snake_Movement dir2);

struct Snake
{
	Snake(std::array<unsigned, 2> gridSize) : gridDimensions(gridSize) {
		unsigned x = rand() % gridSize[0];
		unsigned y = rand() % gridSize[1];
		std::array<unsigned, 2> startingPosition = { x, y };
		snakePositions.push_back(startingPosition);
	}

	inline std::vector <std::array<unsigned, 2>> returnSnakePositions()
	{
		return snakePositions;
	}
	void processKeyboard(Snake_Movement direction)
	{
		if (directionBuffer.size() == 0 || (directionBuffer.size() < 2 && (directionBuffer.empty() || direction != directionBuffer[0]) && (length == 1 || !areDirectionsOpposite(directionBuffer[0], direction))))
		{
			directionBuffer.push_back(direction);
		}
	}
	bool isCollidingWithSelf()
	{
		for (auto iter = snakePositions.begin() + 1; iter != snakePositions.end(); ++iter)
			if (snakePositions[0] == *iter && !noFoodEaten)
				return 1;
		return 0;
	}
	void checkIfLose(Gamestate &gamestate)
	{
		if (snakePositions[0][0] >= gridDimensions[0])
			gamestate = GAMEOVER;
		else if (snakePositions[0][1] >= gridDimensions[1])
			gamestate = GAMEOVER;
		if (isCollidingWithSelf())
			gamestate = GAMEOVER;
	}
	void checkIfEatFood(Food &food)
	{
		if (snakePositions[0] == food.returnFoodPosition())
		{
			length += 4;
			noFoodEaten = 0;
			std::array<unsigned, 2> endOfTailCoords = *--snakePositions.end();
			while (snakePositions.size() < length)
				snakePositions.push_back(endOfTailCoords);
			food.generateNewPosition(gridDimensions, snakePositions);
		}
	}
	void move();
private:
	std::vector <std::array<unsigned, 2>> snakePositions;
	std::array<unsigned, 2> gridDimensions;
	unsigned int length = 1;
	std::deque<Snake_Movement> directionBuffer;
	Snake_Movement currentDirection;
	bool noFoodEaten = 1;
};


#endif