#include "Utils.h"



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