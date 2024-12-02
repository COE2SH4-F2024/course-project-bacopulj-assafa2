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
    objPosArrayList *foodStorage;

public:
    Food();
    ~Food();

    void generateFood(const objPosArrayList *blockOff);
    objPosArrayList* getFoodIndex() const;
};

#endif
