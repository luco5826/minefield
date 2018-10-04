#include <iostream>
#include "include/Cell.h"
#include "include/Field.h"
#include "include/Game.h"
#include "include/Utils.h"

int main() {
    int width = 0, height = 0, mines = 0;
    readFromTerminal(&width, &height, &mines);

    Game *game = new Game(width, height, mines);

    while (!game->userHasWon() && !game->mineIsPressed()) {
        game->printField();
        game->askForInput();
        game->checkVictory();
    }

    if (game->userHasWon()) {
        std::cout << "YOU WON!!!::GAME FINISHED" << std::endl;
    } else {
        std::cout << "MINE PRESSED::GAME FINISHED" << std::endl;
    }

    delete game;

    return 0;
}