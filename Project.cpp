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

GameMechs* mainGameMechs;
Player* player;
Food* food;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while(mainGameMechs->getExitFlagStatus() == false)  
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
}

void GetInput(void)
{
   int hasChar = MacUILib_hasChar();

   if (hasChar) {
        char input = MacUILib_getChar();
        mainGameMechs->setInput(input);
   }
}

void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    for (int i = 0; i < mainGameMechs->getBoardSizeY(); i++) {
        for (int j = 0; j < mainGameMechs->getBoardSizeX(); j++) {
            bool printed = false;
            for (int k = 0; k < player->getPlayerPos()->getSize(); k++) {
                if (i == player->getPlayerPos()->getElement(k).pos->y && j == player->getPlayerPos()->getElement(k).pos->x) {
                    MacUILib_printf("%c", player->getPlayerPos()->getElement(k).symbol);
                    printed = true;
                    break;
                }
            }
            
            if (!printed) {
                if (i == food->getFoodPos().pos->y && j == food->getFoodPos().pos->x) {
                    MacUILib_printf("%c", food->getFoodPos().symbol);
                }
                else if (j == mainGameMechs->getBoardSizeX() - 1) {
                    MacUILib_printf("#\n");
                }
                else if (i == 0 || i == mainGameMechs->getBoardSizeY() - 1 || j == 0) {
                    MacUILib_printf("#");
                } else {
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

    if (mainGameMechs->getLoseFlagStatus()) {
        MacUILib_printf("You lost! Your score was: %d\n", mainGameMechs->getScore());
    }

    MacUILib_uninit();

    delete mainGameMechs;
    delete player;
    delete food;
}
