#include "Food.h"


Food::Food() 
{
    foodPos.setObjPos(8, 13, 'F');
}

Food::~Food() 
{
}

void Food::generateFood(const objPosArrayList* blockOff) 
{
    int randomX, randomY, x, y;
    bool validPosition = false;
    bool occupied[BOARD_LENGTH][BOARD_HEIGHT];
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

    srand(time(NULL));

    while (!validPosition) 
    {
        validPosition = true;

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

objPos Food::getFoodPos() const 
{
    return foodPos;
}
