#include <iostream>
#include <string>
#include <chrono>
#include <array>
#include "SudokuSolver.hpp"
#include "IterativeSolvingPolicy.hpp"
#include "RecursiveSolvingPolicy.hpp"

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

static int ReadLine(Grid &grid, const std::string &line, int lineNb)
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
        grid.placeNumber((c == '.') ? 0 : c - '0', lineNb, lineIncr);
    }
    if (lineIncr != 9)
    {
        ErrorWhileReading("Wrong number of caracters on line", lineNb, lineIncr);
        return false;
    }
    return true;
}

void launchResolution(Grid &grid)
{
    std::cout << "::::::: BEFORE :::::::" << std::endl;
    std::cout << grid << std::endl;
    auto begin = std::chrono::steady_clock::now();
    auto s = SudokuSolver<RecursiveSolverPolicy>(grid);
    // s.DisplayPossibilities();
    auto result = s.resolve();
    auto end= std::chrono::steady_clock::now();
    // display the solving result
    std::cout << ((result) ? "Resolution succeeded" : "Resolution failed") << std::endl;
    
    // avoid to cout float as scientific notation
    std::cout<< std::fixed;

    // cout solving duration
    std::cout << "Resolved in: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / 1000000000.0 << " seconds" << std::endl;
    
    // cout the solved grid
    std::cout << grid;
    std::cout << "- - - - - - - - - - - -" << std::endl;
    grid.clearGrid();
}

int ReadStdin()
{
    Grid grid;
    uint16_t i = 0;
    for (std::string line; std::getline(std::cin, line);)
    {
        // check the number of line read
        if (i > SUDOKU_LINE_LENGTH - 1)
        {
            // if line[0] == '\0', it means that it's an empty line separating two sudokus
            if (!line[0])
            {
                launchResolution(grid);
            }
            else
            {
                ErrorWhileReading("Wrong number of lines in sudoku", i, 0);
            }
            i = 0;
            continue;
        }

        if (ReadLine(grid, line, i++))
            continue;
        // if here, there was an error in this sudoku line, so jump to the next sudoku if there is one;
    }
    // std::cout << grid << std::endl;
    return 0;
}

int main()
{
    //Grid grid;

    return ReadStdin();
}