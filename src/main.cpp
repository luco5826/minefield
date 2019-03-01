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
    bool mousePointer = false;

    if (argv == 2 && (strcmp(argc[1], "--help") == 0 || strcmp(argc[1], "-h") == 0)) {
        Utils::printHelp();
        return 0;
    }

    if (argv == 2 && (strcmp(argc[1], "--keys") == 0 || strcmp(argc[1], "-k") == 0)) {
        arrowKeys = true;
    }

    if (argv == 2 && (strcmp(argc[1], "--mouse") == 0 || strcmp(argc[1], "-m") == 0)) {
        mousePointer = true;
    }

    if (argv > 2) {
        Utils::printError();
        return 0;
    }

    int width = 0, height = 0, mines = 0;
    std::cout << _("MINEFIELD") << std::endl;

    Utils::readFromTerminal(&width, &height, &mines);

    std::shared_ptr<Game> game;
    try {
        game = std::make_shared<Game>(width, height, mines, arrowKeys, mousePointer);
    } catch (std::invalid_argument& e) {
        std::cout << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << std::endl;
        exit(1);
    }

    {  // Don't know what this block does, initialize ncurses
        initscr();
        cbreak();
        curs_set(FALSE);  // Hides the cursor
        keypad(stdscr, TRUE);
        mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);
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
