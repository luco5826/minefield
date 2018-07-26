#ifndef CELL_H
#define CELL_H

/**
 * Abstraction of a cell
 *  
 */
class Cell{
private:
    bool mined = false;
    bool visible = false;
    int nearMines = 0;

public:
    /*
    Insert a mine in this Cell
    */
    void setMine();

    /*
    True if this Cell has a mine, false otherwise
    */
    bool isMined();
    
    /*
    True if this Cell has been set to Visible, false otherwise
    */
    bool isVisible();

    /*
    Set the property "visible" of this Cell 
    */
    void setVisible(const bool visible);

    /*
    Returns the number of surrounding cells that contain 
    a mine (which is the number displayed in-game)
    */
    int getNearMines();

    /*
    Set the number of surrounding cells that contain a mine
    */
    void setNearMines(int num);

    /*
    Increment by one the amount of near mines
    */
    void incrementNearMines();
};

#endif //CELL_H