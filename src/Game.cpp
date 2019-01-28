
#include "Game.h"

Game::Game(const int width, const int height, const int mines) {
    this->field = new Field(width, height, mines);
    std::cout << "Field created" << std::endl;
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
    std::string input = "";

    //FLAG or REVEAL
    {
        std::cout << "Do you want to FLAG (f) or REVEAL (r) a cell? (default = REVEAL) ";
        std::getline(std::cin, input);
        flag = input[0];
    }

    //ROW
    {
        std::cout << "Insert row (1 - " << this->field->getHeight() << "): ";
        std::getline(std::cin, input);
        std::stringstream ss(input);
        ss >> row;
    }
    //COLUMN
    {
        std::cout << "Insert column(1 - " << this->field->getWidth() << "): ";
        std::getline(std::cin, input);
        std::stringstream ss(input);
        ss >> column;
    }
    this->minePressed = this->field->selectCell(row - 1, column - 1, (flag == 'f') ? Field::SelectOption::FLAG : Field::SelectOption::REVEAL);
}

void Game::checkVictory() {
    this->won = this->field->checkVictory();
}

void Game::printField(){
    this->field->printField();
}