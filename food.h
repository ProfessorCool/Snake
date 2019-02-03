#ifndef FOOD_H
#define FOOD_H

#include <array>
#include <vector>
#include <ctime>

bool isOpenSpace(std::array<unsigned, 2> givenPosition, std::vector <std::array<unsigned, 2>> snakePositions);
std::array<unsigned, 2> generateOpenPosition(std::array<unsigned, 2> gridSize, std::vector <std::array<unsigned, 2>> snakePositions);

struct Food
{
	Food(const std::array<unsigned, 2> &gridSize, const std::vector <std::array<unsigned, 2>> &snakePositions) {
		
		position = generateOpenPosition(gridSize, snakePositions);
	}

	inline std::array<unsigned, 2> returnFoodPosition()
	{
		return position;
	}
	void generateNewPosition(const std::array<unsigned, 2> &gridSize, const std::vector <std::array<unsigned, 2>> &snakePositions)
	{
		position = generateOpenPosition(gridSize, snakePositions);
	}

private:
	std::array<unsigned, 2> position;
};


#endif