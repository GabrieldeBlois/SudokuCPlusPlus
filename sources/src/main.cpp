#include <iostream>
#include <string>
#include <array>
#include "Sudoku.hpp"

static void ErrorWhileReading(const std::string &error, int line, int caracter)
{
    std::cerr
        << "Error: "
        << error
        << " at position: "
        << line
        << ":"
        << caracter
        << std::endl;
}

int ReadLine(Grid &grid, const std::string &line, int lineNb)
{
    int lineIncr = 0;
    for (; line[lineIncr] && lineIncr < SUDOKU_LINE_LENGTH; ++lineIncr)
    {
        char c = line[lineIncr];
        if ((c < '0' || c > '9') && c != '.')
        {
            ErrorWhileReading("The caracter is not numerical nor 0 (.)", lineNb, lineIncr);
            return false;
        }
        // fill the grid with the read numbers
        //grid[lineNb][lineIncr] = (c == '.') ? 0 : c - '0';
        grid.placeNumber((c == '.') ? 0 : c - '0', lineNb, lineIncr);
    }
    if (lineIncr != 9)
    {
        ErrorWhileReading("Wrong number of caracters on line", lineNb, lineIncr);
        return false;
    }
    return true;
}

int ReadStdin()
{
    Grid grid;
    uint8_t i = 0;

    for (std::string line; std::getline(std::cin, line);)
    {
        // check the number of line read
        if (i > SUDOKU_LINE_LENGTH - 1)
        {
            // if line[0] == '\0', it means that it's an empty line separating two sudokus
            if (!line[0])
            {
                std::cout << grid << std::endl;
                auto s = SudokuSolver<RecursiveSolverPolicy>(grid);
                s.DisplayPossibilities();
                std::cout << s.resolve() << std::endl;
                std::cout << grid << std::endl;
            }
            else {
                ErrorWhileReading("Wrong number of lines in sudoku", i, 0);
            }
            i = 0;
            continue;
        }

        if (ReadLine(grid, line, i++))
            continue;

        // if here, there was an error in this sudoku line, so jump to the next sudoku if there is one;
    }
    std::cout << grid << std::endl;
    return 0;
}

int main(int ac, char **av)
{
    //Grid grid;

    return ReadStdin();
}