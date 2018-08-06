#include <iostream>
#include "include/Field.h"
#include "include/Cell.h"
#include "include/Game.h"
#include "include/Utils.h"

int main()
{
    int width = 0, height = 0, mines = 0;
    readFromTerminal(&width, &height, &mines);
    
    Game *game = new Game(width, height, mines);
    
    while(!game->isFinished()){
        game->askForInput();
        
    }   
    
    std::cout << "MINE PRESSED::GAME FINISHED" << std::endl;
    return 0;
}