#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000
#define WIDTH 30
#define HEIGHT 15

// Declare pointers to the main game components
GameMechs *mainGameMechs;
Player *player;
Food *food;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while (mainGameMechs->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    mainGameMechs = new GameMechs(WIDTH, HEIGHT);
    food = new Food();
    player = new Player(mainGameMechs, food);
    food->generateFood(player->getPlayerPos());
}

void GetInput(void)
{
    int hasChar = MacUILib_hasChar();

    if (hasChar)
    {
        char input = MacUILib_getChar();
        mainGameMechs->setInput(input);
    }
}

// Update game logic, including player movement and direction changes
void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();
}

// Draw the game screen: player, food, and board
void DrawScreen(void)
{
    MacUILib_clearScreen();
    for (int i = 0; i < mainGameMechs->getBoardSizeY(); i++)
    {
        for (int j = 0; j < mainGameMechs->getBoardSizeX(); j++)
        {
            bool printed = false;

            // Check if the current position matches the player's position and draw the player
            for (int k = 0; k < player->getPlayerPos()->getSize(); k++)
            {
                if (i == player->getPlayerPos()->getElement(k).pos->y && j == player->getPlayerPos()->getElement(k).pos->x)
                {
                    MacUILib_printf("%c", player->getPlayerPos()->getElement(k).symbol);
                    printed = true;
                    break;
                }
            }

            // If the player wasn't drawn, check if the current position matches the food's position and draw the food
            if (!printed) {
                for (int k = 0; k < food->getFoodPos()->getSize(); k++)
                {
                    if (i == food->getFoodPos()->getElement(k).pos->y && j == food->getFoodPos()->getElement(k).pos->x)
                    {
                        MacUILib_printf("%c", food->getFoodPos()->getElement(k).symbol);
                        printed = true;
                        break;
                    }
                }
            }

            // If the player or food wasn't drawn check for walls
            if (!printed)
            {
                if (j == mainGameMechs->getBoardSizeX() - 1)
                {
                    MacUILib_printf("#\n");
                }
                else if (i == 0 || i == mainGameMechs->getBoardSizeY() - 1 || j == 0)
                {
                    MacUILib_printf("#");
                }
                else
                {
                    MacUILib_printf(" ");
                }
            }
        }
    }
    MacUILib_printf("Score: %d\n", mainGameMechs->getScore());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();

    // If the player lost, display a message

    if (mainGameMechs->getLoseFlagStatus())
    {
        MacUILib_printf("You lost! Your score was: %d\n", mainGameMechs->getScore());
    }

    MacUILib_uninit();

    // Delete dynamically allocated memory
    delete mainGameMechs;
    delete player;
    delete food;
}
