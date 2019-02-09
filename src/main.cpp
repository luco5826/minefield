#include <ncurses.h>
#include <string.h>
#include <iostream>
#include <memory>

#include "Game.h"
#include "Gettext.h"
#include "Utils.hpp"

int main(int argv, char* argc[]) {
    setlocale(LC_ALL, "");
    bindtextdomain("minefield", "./locale");
    textdomain("minefield");

    bool arrowKeys = false;

    if (argv == 2 && (strcmp(argc[1], "--help") == 0 || strcmp(argc[1], "-h") == 0)){
        Utils::printHelp();
        return 0;
    }

    if (argv == 2 && (strcmp(argc[1], "--keys") == 0 || strcmp(argc[1], "-k") == 0)){
        arrowKeys = true;
    }

    if (argv > 2){
        Utils::printError();
        return 0;
    }

    int width = 0, height = 0, mines = 0;
    std::cout << _("MINEFIELD") << std::endl;

    Utils::readFromTerminal(&width, &height, &mines);

    std::shared_ptr<Game> game = std::make_shared<Game>(width, height, mines, arrowKeys);

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
        game->userInput();
        game->checkVictory();
    }

    clear();          // Clear the screen
    attroff(A_BOLD);  // Disable BOLD font
    endwin();         // Close the Window

    if (game->userHasWon()) {
        std::cout << std::endl;
        std::cout << _("YOU WON!!!::GAME FINISHED") << std::endl;
        std::cout << std::endl;
    } else {
        std::cout << std::endl;
        std::cout << _("MINE PRESSED::GAME FINISHED") << std::endl;
        std::cout << std::endl;
    }
    
    std::cout << _("You played MINEFIELD - by Luca Errani") << std::endl;
    std::cout << _("Feel free to contribute at https://github.com/luco5826/minefield") << std::endl;

    return 0;
}
