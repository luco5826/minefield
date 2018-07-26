#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include "Cell.h"


/**
 * 
 * Game Field, contains a cell table and populates it on construcition
 *  
 */
class Field
{
  private:
    int width;
    int height;
    int mines;
    Cell **field;

    void addMines();
    void setupCells();
    void updateCells();

  public:
    /*
    Field Constructor, create a table width x height and fill
    it with mines
    */
    Field(const int width, const int height, int mines);

    //
    bool selectCell(const int row, const int column);

    /*
    Returns the number of mines in this field
    */
    int getMines();

    /*
    Returns the cell in position y, x (row, column)
    */
    Cell* getCell(int y, int x);

    /*
    Print the field with "*" where there's a mine
    */
    void printField();
};

#endif //FIELD_H