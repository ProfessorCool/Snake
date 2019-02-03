#include "snake.h"

void Snake::move()
{
	std::array<unsigned, 2> currentPos = snakePositions[0];
	std::array<unsigned, 2> nextPos;
	if (!directionBuffer.empty())
	{
		if (directionBuffer[0] == UP)
		{

			++snakePositions[0][1];
			
			if (directionBuffer.size() != 1)
				directionBuffer.pop_front();
		}
		else if (directionBuffer[0] == DOWN)
		{
		
			--snakePositions[0][1];
		
			if (directionBuffer.size() != 1)
				directionBuffer.pop_front();
		}
		else if (directionBuffer[0] == LEFT)
		{
		
			--snakePositions[0][0];
		
			if (directionBuffer.size() != 1)
				directionBuffer.pop_front();
		}
		else if (directionBuffer[0] == RIGHT)
		{
		
			++snakePositions[0][0];

			if (directionBuffer.size() != 1)
				directionBuffer.pop_front();
		}
	}
	for (int count = 1; count != snakePositions.size(); ++count)
	{
		nextPos = snakePositions[count];
		snakePositions[count] = currentPos;
		currentPos = nextPos;
	}

}
bool areDirectionsOpposite(Snake_Movement dir1, Snake_Movement dir2)
{
	if (dir1 == UP && dir2 == DOWN)
		return 1;
	if (dir1 == RIGHT && dir2 == LEFT)
		return 1;
	if (dir1 == DOWN && dir2 == UP)
		return 1;
	if (dir1 == LEFT && dir2 == RIGHT)
		return 1;
	return 0;
}