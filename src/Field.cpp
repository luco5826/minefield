#include "include/Field.h"

Field::Field(const int width = 10, const int height = 10, const int mines = 20)
{

    this->width = width;
    this->height = height;
    this->mines = mines;

    //Building the field (matrix[height][width])
    this->field = new Cell *[height];
    for (size_t i = 0; i < this->height; i++)
    {
        this->field[i] = new Cell[width];
    }

    this->addMines();   //Adds randomly placed mines
    this->setupCells(); //Set numbers on near-mines-cells
}

void Field::addMines()
{
    srand(time(NULL));
    int minesPlaced = 0;

    while (minesPlaced != mines)
    {
        //Using Integer division (it's simpler than it seems)
        int position = rand() % (width * height);       //Eg. position  = 38 (width 7, height 10)
        int positionY = position / (width);             //    positionY = 38 / 7 = 5 (6th row from the top)
        int positionX = position - (positionY * width); //    positionX = 38 - (5 * 7) = 3 (4th element in the row)

        //The order of (y, x) instead of (x, y) is due to a different rappresentation of the field,
        //we need to access row THEN column, so it is Y-position THEN X-position
        if (!getCell(positionY, positionX)->isMined())
        {
            getCell(positionY, positionX)->setMine();
            minesPlaced++;
        }
    }
}

void Field::setupCells()
{
    //Searches through the field, when it finds a MINED cell, increment by one
    //the value "nearMines" of near cells (in the 3x3 surrounding grid)
    for (size_t i = 0; i < this->height; i++)
    {
        for (size_t j = 0; j < this->width; j++)
        {
            //Extraction (readability)
            Cell current = *getCell(i, j);
            if (current.isMined())
            {
                this->incrementSurroundingGrid(i, j);
            }
        }
    }
}

void Field::incrementSurroundingGrid(const int i, const int j)
{
    //Surrounding cells disposition
    //-1 -1 | -1 0 | -1 +1
    // 0 -1 |  0 0 |  0 +1
    //+1 -1 | +1 0 | +1 +1
    for (int a = i - 1; a <= i + 1; a++)
    {
        for (int b = j - 1; b <= j + 1; b++)
        {
            Cell *toBeIncremented = getCell(a, b);
            if (toBeIncremented != nullptr)
                toBeIncremented->incrementNearMines();
        }
    }
}

void Field::updateCells()
{

    for (int i = 0; i < this->height; i++)
    {
        bool restart = false; // See below

        for (int j = 0; j < this->width; j++)
        {
            //Extraction (readability)
            Cell *current = getCell(i, j);
            if (current->isVisible() && current->isAnEmptyCell())
            {

                if (!current->isRevealed())
                {
                    current->setRevealed(true);
                    restart = revealSurroundingGrid(i, j); //See function definition (Field.h)

                    //We start from the first row, but if we reveal a cell which has already been
                    //examinated (e.g. the left one from the current Cell), we loose that "update", so we restart from the beginning
                    if (restart)
                    {
                        i = -1;
                        break;
                    }
                }
            }
        }
    }
}

bool Field::revealSurroundingGrid(const int i, const int j)
{
    bool restart = false;
    //Surrounding cells disposition
    //-1 -1 | -1 0 | -1 +1
    // 0 -1 |  0 0 |  0 +1
    //+1 -1 | +1 0 | +1 +1
    for (int a = i - 1; a <= i + 1; a++)
    {
        for (int b = j - 1; b <= j + 1; b++)
        {
            Cell *toMakeVisible = getCell(a, b);
            if (toMakeVisible != nullptr && !toMakeVisible->isVisible())
            {
                toMakeVisible->setVisible(true);
                restart = true;
            }
        }
    }

    return restart;
}

bool Field::selectCell(const int row, const int column)
{
    Cell *selected = this->getCell(row, column);
    if (selected == nullptr)
        return false;

    if (selected->isMined())
        return true;

    selected->setVisible(true);
    this->updateCells();
    return false;
}

int Field::getMines()
{
    return this->mines;
}

Cell *Field::getCell(int y, int x)
{
    if (y < 0 || x < 0 || y >= height || x >= width)
    {
        return nullptr;
    }

    return &this->field[y][x];
}

int Field::getWidth(){
    return this->width;
}

int Field::getHeight(){
    return this->height;
}

void Field::printField()
{
    std::cout << "     ";
    for (size_t colIndex = 1; colIndex <= this->width; colIndex++)
    {
        if (colIndex < 10)
        {
            std::cout << "  " << colIndex << "  ";
        }
        else
        {
            std::cout << " " << colIndex << "  ";
        }
    }
    std::cout << std::endl << std::endl;
    for (size_t i = 0; i < this->height; i++)
    {
        if (i < 9)
        {
            std::cout << "  " << i + 1 << "  ";
        } else {
            std::cout << " " << i + 1 << "  ";
        }

        for (size_t j = 0; j < this->width; j++)
        {

            Cell current = *getCell(i, j);
            if (current.isVisible())
            {
                if (current.getNearMines() == 0)
                {
                    std::cout << "     ";
                }
                else
                {
                    std::cout << "  " << current.getNearMines() << "  ";
                }
            }
            else
            {
                std::cout << " [ ] ";
            }
        }
        std::cout << std::endl;
    }
}
