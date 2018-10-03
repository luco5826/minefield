#ifndef GAME_H
#define GAME_H

#include <sstream>
#include "Field.h"

class Game {
   private:
    Field *field;
    bool minePressed = false;

   public:
    Game(const int width, const int height, const int mines);

    ~Game();
    bool isFinished();
    void askForInput();
};

#endif  //GAME_H