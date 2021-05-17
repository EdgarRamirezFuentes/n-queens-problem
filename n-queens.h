#ifndef NQUEENS_H
#define NQUEENS_H

#include <iostream>
#include <vector>
#include <string>

// Limits of the chessboard
const unsigned MAX_SIZE = 12;
const unsigned MIN_SIZE = 1;


// Functions prototypes
bool menu(void);
void createNewChessboard(int&);
void showSolutions(void);
void getValidNumber(int&, std::string, std::string);
void clear(void);
void printIntroduction(void);

/**
*   Class used to create a chessboard of size n x n, and find the 
*   possible solutions to the n-queens problem using this chessboard. 
*/
class Chessboard {
    public:
        size_t size;
        Chessboard (int); 
        ~Chessboard(void);
        void getSolutions(void);
    private:
        bool isSolved;
        std::vector< std::vector<std::string> > chessboard;
        std::vector< std::vector< std::vector<std::string> > > solutions;
        std::string queen;
        void buildChessboard(void);
        void findSolutions(int);
        bool canBePlaced(int, int);
        void printSolutions(void);
};


Chessboard *chessboard = new Chessboard(2);

/**
*   Initialize the chessboard to find the possible solutions to the n-queens problem.
*   @param size Integer used to build the chessboard of size n x n
*/
Chessboard::Chessboard(int size) {
    this->size = size;
    this -> queen = "♛";
    this -> isSolved = false;
    buildChessboard();
}

/** 
*   Destroy the current chessboard 
*/
Chessboard::~Chessboard(void) {}

/**
*   Initialize the matrix that will be used as chessboard of size n x n.
*/
void Chessboard::buildChessboard(void) {
    chessboard.resize(size);
    for (auto& row : chessboard) {
        row.resize(size);
        for (auto& slot : row) {
            slot = ' ';
        }
    }
}

/**
*   Check if a queen can be placed successfully in the current
*   chess square by checking that there is no queens on the top of same
*   column, and there are no queen on the top of its left and right diagonals.
*   
*   Example: 
*   (.) -> The current chess square 
*   (*) -> The chess squares that will be checked
*   (-) -> The chess squares that will not be checked
*
*   Chessboards:
*
*    (*) (*) (*)
*    (-) (.) (-)
*    (-) (-) (-)

*    (*) (-) (*) (-)
*    (-) (*) (*) (*)
*    (-) (-) (.) (-)
*    (-) (-) (-) (-)
*
*   @param row Integer that will be helpful to know the row of the current chessboard square
*   @param column Integer that will be helpful to know the column of the current chessboard square
*/
bool Chessboard::canBePlaced(int row, int column){
    // Check if there are no queens on the same column
    for (int i = 0; i < row; i++) {
        if (chessboard[i][column] == queen) { return false; } 
    }
    
    // Check if there are no queens on the left diagonal from top to the current row
    for (int i = 1; column - i >= 0 && row - i >= 0; i++) {
        if (chessboard[row - i][column - i] == queen) return false; // Found a queen
    }
    
    // Check if there are no queens on the right diagonal from top to the current row
    for (int i = 1; row - i >= 0 && column + i < size; i++) {
        if(chessboard[row - i][column + i] == queen) { return false; } // Found a queen
    }
    return true;
}

/**
*   Check if there are possible solutions to this chessboard and print them.
*   If there are no possible solutions, print a message to tell the user that 
*   the n-queens cannot be placed in this chessboard.
*/
void Chessboard::printSolutions(void) {
    if (solutions.size() == 0) {
        std::cout << size << " queens cannot be placed in a chessboard of size " << size 
                << " x " << size << "\n";
        return;
    }

    unsigned int counter = 1;
    int shownSolutions = 0;
    std::cout << "There are " << solutions.size() << " solutions to a chessboard of size " 
            << size << " x " << size << "\n";
    std::cout << "How many solutions you want to be shown (Range: 1 - " << solutions.size() << ")?  ";
    /*
    *   Get the quantity of solutions that the user wants to be shown.
    *   If the user provides an invalid input, such as a letter or a number out of the range, It will
    *   print a message and ask for the quantity until they provide a valid input
    * 
    */
    while(!(std::cin >> shownSolutions) || shownSolutions < 0 || shownSolutions > solutions.size()) {
        std::cout << "Type a valid input\n";
        std::cout << "How many solutions you want to be shown (Range: 0 - " << solutions.size() << ")?  ";
        // Clear the buffer
        std::cin.clear();
        std::cin.ignore();
    }

    for (int i = 0; i < shownSolutions; i++) {
        std::cout << "Solution " << counter << ": \n";
        for (auto& row : solutions[i]) {
            for (auto& column : row) {
                std::cout << "(" << column << ")";
            }
            std::cout << "\n";
        }
        counter++;
    }

    std::cout << "\n";
}

/**
*   Find each possible solution to set n-queens in a chessboard of size nxn.
*   
*   Try to place a queen for each row of the chessboard until it finds a possible
*   solution if it exists.
*
*   @param row An integer that will be helpful to keep track of the current row in which
*   will try place a queen successfully.    
* 
*/
void Chessboard::findSolutions(int row) {
    // All the queens were placed successfully
    if (row == size) {
        // Store the found solution
        solutions.push_back(chessboard);
        return;
    }

    /**  
    *   For each column of the current row will try to place a queen.
    *   If the queen can be placed successfully in the current chess square, It will continue
    *   trying to place the remaining queens in the rows below the current one.
    *   If the queen cannot be placed successfully, It will clean current chess square, and checking
    *   if the queen can be placed in the next columns.
    */
    for(int column = 0 ; column < size; column ++) {
        chessboard[row][column] = queen;
        if(canBePlaced(row, column)) {
            findSolutions(row + 1);
        }
        // Restore the chessboard to its previous
        chessboard[row][column] = ' ';
    }
}

/**
*   Check if the the problem has been solved in order to print the found solutions.
*   If the problem has not been solved, find the possible solutions, and then print the found solutions
*/
void Chessboard::getSolutions() {
    if (!isSolved) {
        findSolutions(0);
        isSolved = true;
    }
    printSolutions();
}

#endif