#include "Player.h"

Player::Player(GameMechs *thisGMRef, Food *foodReference)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    food = foodReference;

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

objPosArrayList *Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

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

void Player::movePlayer()
{
    objPos currentHead = playerPosList->getHeadElement();
    objPos newHead;

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
        return;
    }
    playerPosList->insertHead(newHead);

    if (checkFoodConsumption())
    {
        food->generateFood(playerPosList);
        mainGameMechsRef->incrementScore();
    }
    else
    {
        playerPosList->removeTail();
    }

    if (checkSelfCollision())
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }
}

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
    return false;
}