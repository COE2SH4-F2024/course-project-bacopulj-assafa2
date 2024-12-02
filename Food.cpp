#include "Food.h"


Food::Food() 
{
    foodStorage = new objPosArrayList();
}

Food::~Food() 
{
    delete foodStorage;
}

void Food::generateFood(const objPosArrayList *blockOff) 
{
    int randomX, randomY, x, y;
    bool validPosition = false;
    bool occupied[BOARD_LENGTH][BOARD_HEIGHT];

    srand(time(NULL));

    while (!validPosition) 
    {
        validPosition = true;

        for (x = 0; x < BOARD_LENGTH; x++) 
        {
            for (y = 0; y < BOARD_HEIGHT; y++) 
            {
                occupied[x][y] = false;
            }
        }

        for (x = 0; x < blockOff->getSize(); x++) 
        {
            objPos occupiedPlayer = blockOff->getElement(x);
            occupied[occupiedPlayer.pos->x][occupiedPlayer.pos->y] = true;
        }

        for (x = 0; x < foodStorage->getSize(); x++) 
        {
            objPos occupiedFood = foodStorage->getElement(x);
            occupied[occupiedFood.pos->x][occupiedFood.pos->y] = true;
        }

        randomX = (rand() % (BOARD_LENGTH - 2)) + 1;
        randomY = (rand() % (BOARD_HEIGHT - 2)) + 1;

        if (occupied[randomX][randomY] == true) 
        {
            validPosition = false;
        }
        else 
        {
            objPos newFood = objPos(randomX, randomY, 'F');
            foodStorage->insertHead(newFood);
        }
    }
}

objPosArrayList* Food::getFoodIndex() const 
{
    return foodStorage;
}
