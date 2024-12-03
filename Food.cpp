#include "Food.h"

// Initializes the initial position of the food
Food::Food() 
{
    foodPos.setObjPos(8, 13, 'F'); // Default food position with symbol 'F'
}

Food::~Food() 
{
}

// Generates a new food position, avoiding positions occupied by the player
void Food::generateFood(const objPosArrayList* blockOff) 
{
    int randomX, randomY, x, y;
    bool validPosition = false;
    bool occupied[BOARD_LENGTH][BOARD_HEIGHT]; // Tracks occupied positions on the board

    for (x = 0; x < BOARD_LENGTH; x++) 
    {
        for (y = 0; y < BOARD_HEIGHT; y++) 
        {
            occupied[x][y] = false;
        }
    }
    for (int i = 0; i < blockOff->getSize(); i++) 
    {
        objPos blockOffPos = blockOff->getElement(i);
        occupied[blockOffPos.pos->x][blockOffPos.pos->y] = true;
    }

    srand(time(NULL)); // Seed the random number generator

    while (!validPosition) 
    {
        validPosition = true;


        // Generate a random coordinate within the board's bounaries
        randomX = (rand() % (BOARD_LENGTH - 2)) + 1;
        randomY = (rand() % (BOARD_HEIGHT - 2)) + 1;

        if (occupied[randomX][randomY] == true) 
        {
            validPosition = false;
        }
        else 
        {
            foodPos.setObjPos(randomX, randomY, 'F');
        }
    }
}

// Getter: Returns the current position of the food
objPos Food::getFoodPos() const 
{
    return foodPos;
}
