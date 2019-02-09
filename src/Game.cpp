#include "Game.h"
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

Game::Game(const int width, const int height, const int mines, const bool arrowKeys) : arrowKeys(arrowKeys) {
    this->field = new Field(width, height, mines);
    if (arrowKeys) {
        cursorPos.x = 0;
        cursorPos.y = 0;
    }
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

void Game::userInput() {
    if (this->arrowKeys) {
        this->userInputKeys();
    } else {
        this->userInputCLI();
    }
}

void Game::userInputKeys() {
    int ch = getch();

    switch (ch) {
        case 'f':
        case 'F':
            this->field->selectCell(cursorPos.x, cursorPos.y, Field::SelectOption::FLAG);
            break;
        case 10:  // Enter key
            this->field->selectCell(cursorPos.x, cursorPos.y, Field::SelectOption::REVEAL);
            break;
        case KEY_LEFT:
            cursorPos.y = MAX(0, cursorPos.y - 1);
            break;
        case KEY_RIGHT:
            cursorPos.y = MIN(this->field->getWidth() - 1, cursorPos.y + 1);
            break;
        case KEY_UP:
            cursorPos.x = MAX(0, cursorPos.x - 1);
            break;
        case KEY_DOWN:
            cursorPos.x = MIN(this->field->getHeight() - 1, cursorPos.x + 1);
            break;
        default:
            break;
    }
}

void Game::userInputCLI() {
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

void Game::printField() {
    clear();
    if (this->arrowKeys) {
        mvprintw(0, 0, this->field->printField(cursorPos.x, cursorPos.y).c_str());
    } else {
        mvprintw(0, 0, this->field->printField().c_str());
    }
}