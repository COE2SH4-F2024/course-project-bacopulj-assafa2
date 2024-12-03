#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

//Initializes the array and sets initial size to 0.
objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
}

// Frees the dynamically allocated memory.
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

// Returns the current size of the list.
int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
   for (int i = listSize; i > 0; i--)
		aList[i] = aList[i - 1];

	aList[0] = thisPos; // Insert the new element at the tail.
	listSize++; // Increment the list size
}

void objPosArrayList::insertTail(objPos thisPos)
{
    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    // Shift elements to the left to remove the head element.
    for (int i = 0; i < listSize - 1; i++)
    {
        aList[i] = aList[i + 1];
    }
    listSize--;
}

// Removes the last element from the list and sets it to a default objPos.
void objPosArrayList::removeTail()
{
    aList[listSize - 1] = objPos();
    listSize--;
}

// Returns the first element in the list.

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

//Returns the last element in the list.
objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];  // Return the element at the last index (tail).
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}