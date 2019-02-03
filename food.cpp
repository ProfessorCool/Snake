#include "food.h"

bool isOpenSpace(std::array<unsigned, 2> givenPosition, std::vector <std::array<unsigned, 2>> snakePositions)
{
	for (const auto &checkedPosition : snakePositions)
	{
		if (givenPosition == checkedPosition)
			return 0;
	}
	return 1;
}
std::array<unsigned, 2> generateOpenPosition(std::array<unsigned, 2> gridSize, std::vector <std::array<unsigned, 2>> snakePositions)
{
	unsigned x = rand() % gridSize[0];
	unsigned y = rand() % gridSize[1];
	std::array<unsigned, 2> startingPosition = { x, y };
	while (!isOpenSpace(startingPosition, snakePositions))
	{
		x = rand() % gridSize[0];
		y = rand() % gridSize[1];
		startingPosition = { x, y };
	}
	return startingPosition;
}