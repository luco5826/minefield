#ifndef FIELD_H
#define FIELD_H

#include <time.h>
#include <iostream>
#include <sstream>
#include "Cell.h"

/**
 * 
 * Game Field, contains a cell table and populates it on construction
 *  
 */
class Field {
   private:
    int width;
    int height;
    int mines;
    Cell **field;

    /**
     * Called at the very beginning, adds randomly placed mines
     */
    void addMines();

    /**
     * Called at the very beginning, adds the number in every Cell near to a mine
     */
    void setupCells();

    /**
     * Utility function -- given a mined Cell's location, 
     * increment the value "nearMines" for the surrounding 3x3 grid
     */
    void incrementSurroundingGrid(const int i, const int j);

    /**
     * Utility function -- given a Cell's location, reveals the surrounding 3x3 grid
     * Returns true if a new Cell has been revealed, so that we can repeat the process
     * again until no changes are made
     */
    bool revealSurroundingGrid(const int i, const int j);

    /**
     * Updates which Cells are visible and which aren't
     */
    void updateCells();

   public:
    /**
     * When a Cell is selected by the user, it is either selected to be revealed,
     * or to be flagged as "mined"
     */
    enum SelectOption { REVEAL,
                        FLAG };

    /**
     * Field Constructor, create a matrix WIDTH x HEIGHT and fills
     * it with mines
     */
    Field(const int width, const int height, int mines);

    ~Field();

    /**
	 * Returns true if the selected cell is mined, false otherwise,
     * once called, it updates the table
	 */
    bool selectCell(const int row, const int column, Field::SelectOption option);

    /**
     * Check if the number of unrevealed Cells equals to
     * the number of the total mines in the Field
     */
    bool checkVictory();

    /**
     * Returns the number of mines in this field
     */
    int getMines();

    /**
     * Returns the cell in position y, x (row, column), returns a nullptr
     * if given values are out of range
     */
    Cell *getCell(const int y, const int x);

    /**
     * In order to optimize ncurses prints, we update only the Cells where
     * the cursor passes, so this method is needed in order to re-draw 
     * the previous cell's status when the cursor leaves it.
     * Used in Game->printField();
     */
    const char* cellStatus(const int y, const int x);

    /**
     * Returns the height of the table
     */
    int getHeight();

    /**
     * Returns the width of the table
     */
    int getWidth();

    /**
     * Returns the field with the cursor inside
     */
    std::string printField(int cursorRow, int cursorCol);

    /**
     * Returns the field without the cursor
     */
    std::string printField();
};

#endif  //FIELD_H