#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <sstream>
#include <exception>
#include "Field.h"
#include "Gettext.h"

class Game {
   private:
    Field *field;
    bool arrowKeys = false;
    bool minePressed = false;
    bool won = false;

    struct  {
        int x, y;
    } cursorPos;

   public:
    Game(const int width, const int height, const int mines, const bool arrowKeys);

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
     * Starts the user Input question
     */
    void userInput();

    /**
     * Handles the arrow keys and the Cell's selection with ncurses
     */
    void userInputKeys();

    /**
     * Asks Row, Column coordinates for user's selection
     */
    void userInputCLI();

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