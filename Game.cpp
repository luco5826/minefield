
#include "include/Game.h"

Game::Game(const int width, const int height, const int mines)
{
    this->field = new Field(width, height, mines);
    std::cout << "Field created" << std::endl;
    this->field->printField();
}

Game::~Game()
{
    delete this->field;
}
bool Game::isFinished()
{
    return minePressed;
}

void Game::askForInput()
{
    int row, column;
    std::string input = "";
    {
        std::cout << "Insert row: ";
        std::getline(std::cin, input);
        std::stringstream ss(input);
        ss >> row;
    }
    {
        std::cout << "Insert column: ";
        std::getline(std::cin, input);
        std::stringstream ss(input);
        ss >> column;
    }

    minePressed = this->field->selectCell(row, column);
    this->field->printField();
}