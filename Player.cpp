#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(objPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*'));
    // for testing
    // playerPosList->insertTail(objPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2 + 1, '*'));
}


Player::~Player()
{
    // delete any heap members here
    delete mainGameMechsRef;    
}

objPosArrayList* Player::getPlayerPos() const
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
    // PPA3 Finite State Machine logic
    switch (myDir)
    {
    case UP:
        if (playerPosList->getHeadElement().pos->y == 1) {
            playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x, mainGameMechsRef->getBoardSizeY() - 2, '*'));
            playerPosList->removeTail();
        }
        else {
            playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x, playerPosList->getHeadElement().pos->y - 1, '*'));
            playerPosList->removeTail();
        }
        break;
    case DOWN:
        if (playerPosList->getHeadElement().pos->y == mainGameMechsRef->getBoardSizeY() - 2) {
            playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x, 1, '*'));
            playerPosList->removeTail();
        }
        else {
            playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x, playerPosList->getHeadElement().pos->y + 1, '*'));
            playerPosList->removeTail();
        }
        break;
    case LEFT:
        if (playerPosList->getHeadElement().pos->x == 1) {
            playerPosList->insertHead(objPos(mainGameMechsRef->getBoardSizeX() - 2, playerPosList->getHeadElement().pos->y, '*'));
            playerPosList->removeTail();
        }
        else {
            playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x - 1, playerPosList->getHeadElement().pos->y, '*'));
            playerPosList->removeTail();
        }
        break;
    case RIGHT:
        if (playerPosList->getHeadElement().pos->x == mainGameMechsRef->getBoardSizeX() - 2) {
            playerPosList->insertHead(objPos(1, playerPosList->getHeadElement().pos->y, '*'));
            playerPosList->removeTail();
        }
        else {
            playerPosList->insertHead(objPos(playerPosList->getHeadElement().pos->x + 1, playerPosList->getHeadElement().pos->y, '*'));
            playerPosList->removeTail();
        }
        break;
    default:
        break;
    }
}

// More methods to be added