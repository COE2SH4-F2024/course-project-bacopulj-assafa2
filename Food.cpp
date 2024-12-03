#include "Food.h"

// Initializes the initial position of the food
Food::Food() 
{
    foodBucket = new objPosArrayList(); // Default food position with symbol 'F'
}

Food::~Food() 
{
    delete foodBucket;
}

// Generates new food positions, avoiding positions occupied by the player
void Food::generateFood(const objPosArrayList* blockOff) 
{
    int x, y;
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

    for (int i = 0; i < 3; i++) 
    {
        if (foodBucket->getSize() == 3) {
            foodBucket->removeTail();
        }

        bool validPosition = false;

        while (!validPosition) 
        {
            validPosition = true;


            // Generate a random coordinate within the board's bounaries
            int randomX = (rand() % (BOARD_LENGTH - 2)) + 1;
            int randomY = (rand() % (BOARD_HEIGHT - 2)) + 1;

            if (occupied[randomX][randomY] == true) 
            {
                validPosition = false;
            }
            else 
            {
                foodBucket->insertHead(objPos(randomX, randomY, 'F'));
                occupied[randomX][randomY] = true;
            }
        }
    }
}

// Getter: Returns the current Array List of the food
objPosArrayList* Food::getFoodPos() const 
{
    return foodBucket;
}
