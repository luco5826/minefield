#include "include/Utils.h"

void readFromTerminal(int *width, int *height, int *mines) {
    std::string input = "";
    while (true) {
        std::cout << "Width: ";
        std::getline(std::cin, input);
        std::stringstream ss(input);

        if (ss >> (*width))
            break;
    }

    while (true) {
        std::cout << "Height: ";
        std::getline(std::cin, input);
        std::stringstream ss(input);
        if (ss >> (*height))
            break;
    }
    while (true) {
        std::cout << "Mines number: ";
        std::getline(std::cin, input);
        std::stringstream ss(input);
        if (ss >> (*mines))
            break;
    }
}