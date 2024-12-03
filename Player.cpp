#include "Player.h"

Player::Player(GameMechs *thisGMRef, Food *foodReference)
{
    mainGameMechsRef = thisGMRef; // initialize reference to the main Game mechs object
    myDir = STOP; // player direction starts idle
    food = foodReference; // initializes reference to the food object

    // more actions to be included
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(objPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*'));
}

Player::~Player()
{
    // delete any heap members here
    delete mainGameMechsRef;
    delete playerPosList;
    delete food;
}

// Getter for the player's position list
objPosArrayList *Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

// Updates the player's direction based on input
void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();
    if (input != 0) // if not null character
    {
        switch (input)
        {
        case 27: // exit
            mainGameMechsRef->setExitTrue();
            break;
        case 87:
        case 119:
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
            {
                myDir = UP;
            }
            break;
        case 83:
        case 115:
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
            {
                myDir = DOWN;
            }
            break;
        case 65:
        case 97:
            if (myDir == UP || myDir == DOWN || myDir == STOP)
            {
                myDir = LEFT;
            }
            break;
        case 68:
        case 100:
            if (myDir == UP || myDir == DOWN || myDir == STOP)
            {
                myDir = RIGHT;
            }
            break;
        default:
            break;
        }
        input = 0;
    }
}

// Moves the player based on their current direction
void Player::movePlayer()
{
    objPos currentHead = playerPosList->getHeadElement();
    objPos newHead;

    // Update the head position based on direction and handle wrap-around logic from past PPA's

    switch (myDir)
    {
    case UP:
        newHead = objPos(currentHead.pos->x,
                         (currentHead.pos->y == 1) ? mainGameMechsRef->getBoardSizeY() - 2 : currentHead.pos->y - 1,
                         '*');
        break;
    case DOWN:
        newHead = objPos(currentHead.pos->x,
                         (currentHead.pos->y == mainGameMechsRef->getBoardSizeY() - 2) ? 1 : currentHead.pos->y + 1,
                         '*');
        break;
    case LEFT:
        newHead = objPos((currentHead.pos->x == 1) ? mainGameMechsRef->getBoardSizeX() - 2 : currentHead.pos->x - 1,
                         currentHead.pos->y,
                         '*');
        break;
    case RIGHT:
        newHead = objPos((currentHead.pos->x == mainGameMechsRef->getBoardSizeX() - 2) ? 1 : currentHead.pos->x + 1,
                         currentHead.pos->y,
                         '*');
        break;
    default:
        return; // If direction is STOP or invalid, do nothing
    }
    playerPosList->insertHead(newHead); // Insert the new head at the front of the player position list

    // Check player has eaten food, generate new food and increment the score if they did

    if (checkFoodConsumption())
    {
        food->generateFood(playerPosList);
        mainGameMechsRef->incrementScore();
    }
    else
    {
        playerPosList->removeTail(); 
    }

    // Check if the player collides with itself
    if (checkSelfCollision())
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }
}

// Checks if the player head position matches the food position
// i.e. did they even eat/consume anything?
bool Player::checkFoodConsumption()
{
    return playerPosList->getHeadElement().pos->x == food->getFoodPos().pos->x && playerPosList->getHeadElement().pos->y == food->getFoodPos().pos->y;
}

bool Player::checkSelfCollision()
{
    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        if (playerPosList->getElement(i).pos->x == playerPosList->getHeadElement().pos->x && playerPosList->getElement(i).pos->y == playerPosList->getHeadElement().pos->y)
        {
            return true;
        }
    }
    return false; // no collision
}