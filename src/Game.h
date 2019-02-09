#ifndef GAME_H
#define GAME_H

#include <sstream>
#include <ncurses.h>
#include "Gettext.h"
#include "Field.h"

class Game {
   private:
    Field *field;
    bool minePressed = false;
    bool won = false;

   public:
    Game(const int width, const int height, const int mines);

    ~Game();

    /**
     * Check if the Cell selected by the user was mined 
     */
    bool mineIsPressed();

    /**
     * True if the user has won
     */
    bool userHasWon();

    /**
     * Ask if the user wants to reveal or flag a Cell, and the
     * row-column coordinates of that Cell
     */
    void askForInput();

    /**
     * Check if the user has won the game
     */
    void checkVictory();

    /**
     * Prints the game field to stdout
     */
    void printField();
};

#endif  //GAME_H