#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <sstream>
#include "Gettext.h"

namespace Utils {

void printHelp() {
    std::cout << _("Usage: ./minefield [options]") << std::endl;
    std::cout << std::endl;
    std::cout << _("OPTIONS") << std::endl;
    std::cout << _("--help,  -h        Shows usage and exits") << std::endl;
    std::cout << _("--keys,  -k        Play Minefield moving around the field with your arrow keys") << std::endl;
    std::cout << _("--mouse, -m        Play Minefield clicking on the cells like a normal GUI") << std::endl;
    std::cout << _("--input, -i        [DEFAULT] Play Minefield by writing each time the ROW,COLUMN coordinate of the cell") << std::endl;
    std::cout << std::endl;
}

void printError() {
    std::cout << _("Unknown options") << std::endl;
    std::cout << _("See ./minefield --help for further informations") << std::endl;
}

void readFromTerminal(int *width, int *height, int *mines) {
    std::string input = "";
    while (true) {
        std::cout << _("Width: ");
        std::getline(std::cin, input);
        std::stringstream ss(input);

        if (ss >> (*width))
            break;
    }

    while (true) {
        std::cout << _("Height: ");
        std::getline(std::cin, input);
        std::stringstream ss(input);
        if (ss >> (*height))
            break;
    }
    while (true) {
        std::cout << _("Mines number: ");
        std::getline(std::cin, input);
        std::stringstream ss(input);
        if (ss >> (*mines))
            break;
    }
}

}  // namespace Utils
#endif  //UTILS_H