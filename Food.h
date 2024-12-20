#ifndef FOOD_H
#define FOOD_H

#include "objPosArrayList.h"
#include "cstdlib"
#include "ctime"

#define BOARD_HEIGHT 15
#define BOARD_LENGTH 30

class Food 
{
private:
    objPosArrayList* foodBucket;

public:
    // Initialize food position
    Food();

    ~Food();

    // Generates food at a random position, avoids player positions though
    void generateFood(const objPosArrayList* blockOff);
    
    objPosArrayList* getFoodPos() const;
};

#endif
