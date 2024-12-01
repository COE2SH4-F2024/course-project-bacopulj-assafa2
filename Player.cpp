#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(thisGMRef->getBoardSizeX() / 2, thisGMRef->getBoardSizeY() / 2, '*');
}


Player::~Player()
{
    // delete any heap members here
    delete mainGameMechsRef;    
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
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
    // PPA3 Finite State Machine logic
    switch (myDir)
    {
    case UP:
        if (playerPos.pos->y == 1)
            playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
        else
            playerPos.pos->y--;
        break;
    case DOWN:
        if (playerPos.pos->y == mainGameMechsRef->getBoardSizeY() - 2)
            playerPos.pos->y = 1;
        else
            playerPos.pos->y++;
        break;
    case LEFT:
        if (playerPos.pos->x == 1)
            playerPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
        else
            playerPos.pos->x--;
        break;
    case RIGHT:
        if (playerPos.pos->x == mainGameMechsRef->getBoardSizeX() - 2)
            playerPos.pos->x = 1;
        else
            playerPos.pos->x++;
        break;
    default:
        break;
    }
}

// More methods to be added