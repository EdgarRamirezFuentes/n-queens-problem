#include "n-queens.h"
#include <iomanip>

int main(void) {
    printIntroduction();
    while(menu()){
        clear();
        printIntroduction();
    }
    std::cout << "Bye :D" << std::endl;
    return EXIT_SUCCESS;
}

void printIntroduction(void) {
    std::cout << std::setw(50) <<"N-Queens problem" << std::endl;
    std::cout << std::endl << "Functionality:" << std::endl;
    std::cout << "This program get all the possible solutions to a current chessboard of size n x n if they exist" << std::endl;
    std::cout << "The program is not going to get the solutions of chessboards of size bigger than 12 x 12" << std::endl;
    std::cout << "The program can show all the possible solutions or a specific quantity of solutions of the current chessboard" << std::endl;
    std::cout << "The program allows you to check all the possible solutions of different chessboards" << std::endl;
    std::cout << "There is a message that shows the current chessboard that will be solved" << std::endl;

    std::cout << std::endl << "I hope you enjoy using this program to compare your solutions to this problem" << std::endl;

    std::cout << std::endl << "Author: Edgar A. Ramírez Fuentes" << std::endl;
    std::cout << std::endl << "Current chessboard: " << chessboard->size << " x " << chessboard->size << std::endl;
}

bool menu(void) {
    int option = 0;
    int newSize = 0;
    int returnToMenu = 0;
    std::cout << "1.- Change the size of the current chessboard" << std::endl;
    std::cout << "2.- Show the solutions" << std::endl;
    std::cout << "3.- Exit" << std::endl;

    // Get a valid input
    while(option < 1 || option > 3) {
        getValidNumber(option, "option", "Select an option: ");
    }

    switch (option)
    {
        case 1:
            clear();
            std::cout << std::setw(50) <<"Change the size of the current chessboard" << std::endl;
            getValidNumber(newSize, "size", "What is the new size of the current chessboard? ");
            createNewChessboard(newSize);
            std::cout << "Size updated successfully" << std::endl;
            break;
        case 2:
            clear();
            chessboard->getSolutions();
            break;
        case 3:
            return 0;
            break;
        
        default:
            std::cout << "An error ocurred" << std::endl;
            return EXIT_FAILURE;
    }
    std::cout << std::endl << "What is next? " << std::endl;
    std::cout << "1.- Go to menu" << std::endl;
    std::cout << "2.- Exit" << std::endl; 
    getValidNumber(returnToMenu, "option", "Type your decision ");
    return (returnToMenu == 1 ? true : false);
}

/**
 *  
*   Get a valid whole number and assigns it to the variable number
*  
*   @param number Integer that will get number input by user
*   @param field string that will be useful to ask for the wanted data
*   @param message string that will be displayed each time we ask for a number
*/
void getValidNumber(int& number, std::string field, std::string message) {
    std::cout << message;
    while(!(std::cin >> number)) {
        std::cout << "Type a valid " << field << std::endl;
        std::cin.clear();
        std::cin.ignore();
        std::cout << message;
    }
}

/* 
*   Clear the console using ANSI
*/ 
void clear(void)
{
    std::cout << "\x1B[2J\x1B[H";
}

/**
 *   Create a new Chessboard object with the new size, and delete the old chessboard to avoid
 *   memory leaks.
 *
 *   @param newSize Integer that will be used to initialize the new chessboard
*/
void createNewChessboard(int& newSize) {
    if (newSize < MIN_SIZE || newSize > MAX_SIZE) { return; }
    delete chessboard;
    chessboard = new Chessboard(newSize);
}
