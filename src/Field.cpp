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
	
    this->addMines(); //Adds randomly placed mines
    this->setupCells(); //Set numbers on near-mines-cells
}

void Field::addMines()
{
    int minesPlaced = 0;

    srand(time(NULL));
    while (minesPlaced != mines)
    {
        //Using Integer division
        int position = rand() % (width * height);       //Es. position = 38 (width 7, height 10)
        int positionY = position / (width);             //    positionY = 38 / 7 = 5 (6th row from the top)
        int positionX = position - (positionY * width); //    positionX = 38 - (5 * 7) = 3 (4th element in the row)
		
        //The order of (y, x) instead of (x, y) is due to a different rappresentation of the field,
        //we need to access row THEN column, so it's Y-position THEN X-position
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
    //the value "nearMines" of near cells
    for (size_t i = 0; i < this->height; i++)
    {
        for (size_t j = 0; j < this->width; j++)
        {
            //Extraction (readability)
            Cell current = *getCell(i, j);
            if (current.isMined())
            {
                //TODO: I need to find a way to clear this mess
                //Version 1.0 -> I used pointers in order to be able to 
                //get a nullptr from getCell() when the index gets out of the field range
                Cell *toBeIncremented = nullptr;

                toBeIncremented = getCell(i, j - 1); //left
                if (toBeIncremented != nullptr)
                    toBeIncremented->incrementNearMines();
                toBeIncremented = getCell(i, j + 1); //right
                if (toBeIncremented != nullptr)
                    toBeIncremented->incrementNearMines();
                toBeIncremented = getCell(i - 1, j - 1); //upper left
                if (toBeIncremented != nullptr)
                    toBeIncremented->incrementNearMines();
                toBeIncremented = getCell(i - 1, j); //upper
                if (toBeIncremented != nullptr)
                    toBeIncremented->incrementNearMines();
                toBeIncremented = getCell(i - 1, j + 1); //upper right
                if (toBeIncremented != nullptr)
                    toBeIncremented->incrementNearMines();
                toBeIncremented = getCell(i + 1, j - 1); //lower left
                if (toBeIncremented != nullptr)
                    toBeIncremented->incrementNearMines();
                toBeIncremented = getCell(i + 1, j); //lower
                if (toBeIncremented != nullptr)
                    toBeIncremented->incrementNearMines();
                toBeIncremented = getCell(i + 1, j + 1); //lower right
                if (toBeIncremented != nullptr)
                    toBeIncremented->incrementNearMines();
            }
        }
    }

}

void Field::updateCells()
{
    //Searches through the field, when it finds a VISIBLE cell, set as Visible
    //also the surrounding cells
    for (size_t i = 0; i < this->height; i++)
    {

        for (size_t j = 0; j < this->width; j++)
        {
            //Extraction (readability)
            Cell current = *getCell(i, j);
            if (current.isVisible() && current.getNearMines() == 0)
            {
                //TODO: I need to find a way to clear this mess
                //Version 1.0 -> I used pointers in order to be able to 
                //get a nullptr from getCell() when the index gets out of the field range
                Cell *toMakeVisible = nullptr;

                toMakeVisible = getCell(i, j - 1); //left
                if (toMakeVisible != nullptr && !toMakeVisible->isMined())
                    toMakeVisible->setVisible(true);

                toMakeVisible = getCell(i, j + 1); //right
                if (toMakeVisible != nullptr && !toMakeVisible->isMined())
                    toMakeVisible->setVisible(true);

                // toMakeVisible = getCell(i - 1, j - 1); //upper left
                // if (toMakeVisible != nullptr && !toMakeVisible->isMined())
                //     toMakeVisible->setVisible(true);

                toMakeVisible = getCell(i - 1, j); //upper
                if (toMakeVisible != nullptr && !toMakeVisible->isMined())
                    toMakeVisible->setVisible(true);

                // toMakeVisible = getCell(i - 1, j + 1); //upper right
                // if (toMakeVisible != nullptr && !toMakeVisible->isMined())
                //     toMakeVisible->setVisible(true);

                // toMakeVisible = getCell(i + 1, j - 1); //lower left
                // if (toMakeVisible != nullptr && !toMakeVisible->isMined())
                //     toMakeVisible->setVisible(true);

                toMakeVisible = getCell(i + 1, j); //lower
                if (toMakeVisible != nullptr && !toMakeVisible->isMined())
                    toMakeVisible->setVisible(true);

                // toMakeVisible = getCell(i + 1, j + 1); //lower right
                // if (toMakeVisible != nullptr && !toMakeVisible->isMined())
                //     toMakeVisible->setVisible(true);
            }
        }
    }
}

bool Field::selectCell(const int row, const int column)
{
    Cell *selected = getCell(row, column);
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

void Field::printField()
{
    for (size_t i = 0; i < this->height; i++)
    {

        for (size_t j = 0; j < this->width; j++)
        {

            Cell current = *getCell(i, j);
            if (current.isVisible())
            {
                if (current.getNearMines() == 0)
                {
                    std::cout << "  +  ";
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
