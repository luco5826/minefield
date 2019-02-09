
#include "Game.h"

Game::Game(const int width, const int height, const int mines) {
    this->field = new Field(width, height, mines);
}

Game::~Game() {
    delete this->field;
}
bool Game::mineIsPressed() {
    return minePressed;
}

bool Game::userHasWon() {
    return this->won;
}

void Game::askForInput() {
    char flag;
    int row, column;
    
    //FLAG or REVEAL
    {
        char input;
        mvprintw(LINES - 3, 0, _("Do you want to FLAG (f) or REVEAL (r) a cell? (default = REVEAL): "));
        input = getch();
        flag = input;
    }

    //ROW
    {
        char input[4];
        mvprintw(LINES - 2, 0, _("Insert row (1 - %d): "), this->field->getHeight());
        getnstr(input, 3);
        std::stringstream ss(input);
        ss >> row;
    }
    //COLUMN
    {
        char input[4];
        mvprintw(LINES - 1, 0, _("Insert column(1 - %d): "), this->field->getWidth());
        getnstr(input, 3);
        std::stringstream ss(input);
        ss >> column;
    }
    this->minePressed = this->field->selectCell(row - 1, column - 1, (flag == 'f') ? Field::SelectOption::FLAG : Field::SelectOption::REVEAL);
}

void Game::checkVictory() {
    this->won = this->field->checkVictory();
}

void Game::printField(){
    refresh();
    clear();
    mvprintw(0, 0, this->field->printField().c_str());
    
}