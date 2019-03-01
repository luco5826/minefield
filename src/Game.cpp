#include "Game.h"
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

Game::Game(const int width, const int height, const int mines, const bool arrowKeys) : arrowKeys(arrowKeys) {
    // Negative values check
    if (width <= 0 || height <= 0 || mines <= 0) {
        throw std::invalid_argument(_("Width or height or mines number cannot be negative or zero!"));
    }

    // Check if there are enough cells for mines
    if (mines > width * height) {
        throw std::invalid_argument(_("There aren't enough cells for the specified mines number!"));
    }

    this->field = new Field(width, height, mines);

    if (arrowKeys) {
        cursorPos.x = 0;
        cursorPos.y = 0;
        cursorPos.prevX = 0;
        cursorPos.prevY = 0;
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
    cursorPos.prevX = cursorPos.x;
    cursorPos.prevY = cursorPos.y;
    int ch = getch();

    switch (ch) {
        case 'f':
        case 'F':
            this->field->selectCell(cursorPos.y, cursorPos.x, Field::SelectOption::FLAG);
            break;
        case 10:  // Enter key           
            this->minePressed = this->field->selectCell(cursorPos.y, cursorPos.x, Field::SelectOption::REVEAL);
            break;
        case KEY_LEFT:

            cursorPos.x = MAX(0, cursorPos.x - 1);
            onlyCursorMove = true;
            break;
        case KEY_RIGHT:

            cursorPos.x = MIN(this->field->getWidth() - 1, cursorPos.x + 1);
            onlyCursorMove = true;
            break;
        case KEY_UP:

            cursorPos.y = MAX(0, cursorPos.y - 1);
            onlyCursorMove = true;
            break;
        case KEY_DOWN:

            cursorPos.y = MIN(this->field->getHeight() - 1, cursorPos.y + 1);
            onlyCursorMove = true;
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
    if (this->arrowKeys) {
        // If only the Cursor's position needs to be updated, we restore the cell where the cursor
        // was (field->cellStatus()), and re-draw it in the new one
        if (onlyCursorMove) {
            mvprintw(cursorPos.prevY + 2, cursorPos.prevX * 5 + 6, this->field->cellStatus(cursorPos.prevY, cursorPos.prevX));
            mvprintw(cursorPos.y + 2, cursorPos.x * 5 + 6, "[O]");
        } else {
            clear();
            mvprintw(0, 0, this->field->printField(cursorPos.y, cursorPos.x).c_str());
        }
        onlyCursorMove = false;
    } else {
        clear();
        mvprintw(0, 0, this->field->printField().c_str());
    }
}