#include <iostream>
#include <memory>
#include "Cell.h"
#include "Field.h"
#include "Game.h"
#include "Utils.h"

int main() {
    int width = 0, height = 0, mines = 0;
    readFromTerminal(&width, &height, &mines);

    std::shared_ptr<Game> game = std::make_shared<Game>(width, height, mines);

    while (!game->userHasWon() && !game->mineIsPressed()) {
        game->printField();
        game->askForInput();
        game->checkVictory();
    }

    if (game->userHasWon()) {
        std::cout << std::endl;
        std::cout << "YOU WON!!!::GAME FINISHED" << std::endl;
        std::cout << std::endl;
    } else {
        std::cout << std::endl;
        std::cout << "MINE PRESSED::GAME FINISHED" << std::endl;
        std::cout << std::endl;
    }

    return 0;
}