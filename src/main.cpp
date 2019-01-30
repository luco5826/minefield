#include <ncurses.h>
#include <iostream>
#include <memory>
#include "Cell.h"
#include "Field.h"
#include "Game.h"
#include "Utils.h"

int main() {
    int width = 0, height = 0, mines = 0;
    std::cout << "MINEFIELD" << std::endl;

    readFromTerminal(&width, &height, &mines);

    std::shared_ptr<Game> game = std::make_shared<Game>(width, height, mines);

    {  // Don't know what this block does, initialize ncurses
        initscr();
        cbreak();
        curs_set(FALSE);
        keypad(stdscr, TRUE);
        refresh();       // Refresh the screen
        attron(A_BOLD);  // Set font to BOLD
    }

    while (!game->userHasWon() && !game->mineIsPressed()) {
        game->printField();
        game->askForInput();
        game->checkVictory();
    }

    clear();          // Clear the screen
    attroff(A_BOLD);  // Disable BOLD font
    endwin();         // Close the Window

    if (game->userHasWon()) {
        std::cout << std::endl;
        std::cout << "YOU WON!!!::GAME FINISHED" << std::endl;
        std::cout << std::endl;
    } else {
        std::cout << std::endl;
        std::cout << "MINE PRESSED::GAME FINISHED" << std::endl;
        std::cout << std::endl;
    }
    
    std::cout << "You played MINEFIELD - by Luca Errani" << std::endl;
    std::cout << "Feel free to contribute at https://github.com/luco5826/minefield" << std::endl;

    return 0;
}