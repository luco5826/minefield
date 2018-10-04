#include "include/Cell.h"

/**
 * 
 * Implementation of Cell.h's functions, see header
 * file for complete explanation
 *  
 */

void Cell::setMine() {
    this->mined = true;
}

bool Cell::isMined() {
    return this->mined;
}

bool Cell::isFlagged() {
    return this->flagged;
}

bool Cell::setFlag(const bool flagged) {
    this->flagged = flagged;
}

bool Cell::isVisible() {
    return this->visible;
}

bool Cell::isRevealed() {
    return this->revealed;
}

void Cell::setRevealed(const bool revealed) {
    this->revealed = revealed;
}

bool Cell::isAnEmptyCell() {
    return this->getNearMines() == 0 && !this->isMined();
}

void Cell::setVisible(const bool visible) {
    this->visible = visible;
}

int Cell::getNearMines() {
    return this->nearMines;
}

void Cell::setNearMines(int num) {
    this->nearMines = num;
}

void Cell::incrementNearMines() {
    this->nearMines++;
}