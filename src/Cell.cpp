#include "include/Cell.h"

void Cell::setMine(){
    this->mined = true;
}

bool Cell::isMined(){
        return this->mined;
}

bool Cell::isVisible(){
        return this->visible;
}

void Cell::setVisible(const bool visible){
        this->visible = visible;
}

int Cell::getNearMines(){
        return this->nearMines;
}

void Cell::setNearMines(int num){
        this->nearMines = num;
}

void Cell::incrementNearMines(){
        this->nearMines++;
}