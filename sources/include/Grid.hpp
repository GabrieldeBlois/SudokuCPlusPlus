#pragma once

#include <iostream>

#define SUDOKU_LINE_LENGTH (9)
#define SUDOKU_BLOCK_LENGTH (SUDOKU_LINE_LENGTH / 3)
#define SUDOKU_FULL_LENGTH (SUDOKU_LINE_LENGTH * SUDOKU_LINE_LENGTH)
#define SUDOKU_FIND_SQUARE(y, x) (y / SUDOKU_BLOCK_LENGTH * SUDOKU_BLOCK_LENGTH + x / SUDOKU_BLOCK_LENGTH)

typedef std::array<std::array<uint16_t, SUDOKU_LINE_LENGTH>, SUDOKU_LINE_LENGTH> t_SudokuGrid;

class Grid
{
  public:
    Grid()
    {
    }

    ~Grid()
    {
    }

    // Returns the grid
    const t_SudokuGrid &getGrid() const
    {
        return _grid;
    }

    bool thereIsAlreadyANumber(uint16_t y, uint16_t x)
    {
        return _grid[y][x];
    }

    void clearGrid() {
        
        for(size_t i = 0; i < SUDOKU_LINE_LENGTH; i++)
        {
            
            
            for(size_t j = 0; j < SUDOKU_LINE_LENGTH; j++)
            {
                placeNumber(0, i, j);
            }
        }

        /*std::cout << "CLEAR checking: " << std::endl;

        std::cout << "cols: ";
        for(size_t i = 0; i < SUDOKU_LINE_LENGTH; i++)
        {
            std::cout << _cols[i] << ", ";
        }
        std::cout << std::endl;
        
        std::cout << "lines: ";
        for(size_t i = 0; i < SUDOKU_LINE_LENGTH; i++)
        {
            std::cout << _lines[i] << ", ";
        }
        std::cout << std::endl;

        std::cout << "lines: ";
        for(size_t i = 0; i < SUDOKU_LINE_LENGTH; i++)
        {
            std::cout << _lines[i] << ", ";
        }
        std::cout << std::endl;*/
    }

    // Removes a number in the grid by placing another one at the given (x, y) position
    // If you just want to remove a number, just call this function with number = 0;
    void placeNumber(uint16_t number, uint16_t y, uint16_t x)
    {
        unsigned int oldNumber = _grid[y][x];

        // if the olNumber in the grid != 0, removes it
        if (oldNumber != 0)
        {

            oldNumber = (1 << (oldNumber - 1));
            _squares[SUDOKU_FIND_SQUARE(y, x)] ^= oldNumber;
            _lines[y] ^= oldNumber;
            _cols[x] ^= oldNumber;
        }

        // put the number in the grid
        _grid[y][x] = number;
        // std::cout << " y = " << (int)y << ", x = " << (int)x << " = " << (int)_grid[y][x] << std::endl;

        // if the number was zero, the above expression have just putted it
        if (number == 0)
            return;

        // get the binary form of number
        unsigned int bNumber = 1 << (number - 1);

        // place the new number
        _squares[SUDOKU_FIND_SQUARE(y, x)] |= bNumber;
        _lines[y] |= bNumber;
        _cols[x] |= bNumber;
    }

    void printAllSuitableNumberForAPos(uint16_t n, uint16_t y, uint16_t x) const
    {
        // std::cout << "All suitable number for pos: y = " << (int)y << ", x = " << (int)x << ", are: ";
        for (uint16_t i = 0; i < SUDOKU_LINE_LENGTH; i++)
        {
            if (doesANumberFitInThisPlace(n, y, x))
                std::cout << (int)i << ", ";
        }
        std::cout << std::endl;
    }

    // Determine if a Number fits according to columns, lines and squares
    bool doesANumberFitInThisPlace(uint16_t number, uint16_t y, uint16_t x) const
    {
        // get the binary form from the number
        unsigned int bNumber = 1 << ((int)number - 1);
        // return true if the number is NOT in squares OR cols OR lines
        // tip: an boolean evaluation on any type is considered true if the value is NOT zero
        return !(_squares[SUDOKU_FIND_SQUARE(y, x)] & bNumber ||
                 _lines[y] & bNumber ||
                 _cols[x] & bNumber);
    }

    bool doesANumberFitInThisColumn(uint16_t number, uint16_t x) const
    {
        // get the binary form from the number
        unsigned int bNumber = 1 << (number - 1);
        return !(_cols[x] & bNumber);
    }

    bool doesANumberFitInThisLine(uint16_t number, uint16_t y) const
    {
        // get the binary form from the number
        unsigned int bNumber = 1 << (number - 1);
        return !(_lines[y] & bNumber);
    }

    bool doesANumberFitInThisSquare(uint16_t number, uint16_t y, uint16_t x) const
    {
        // get the binary form from the number
        unsigned int bNumber = 1 << (number - 1);
        return !(_squares[SUDOKU_FIND_SQUARE(y, x)] & bNumber);
    }

  private:
    typedef unsigned int _t_BFlags;
    typedef std::array<_t_BFlags, SUDOKU_LINE_LENGTH> _t_GridLineColsSquareBFlags;

    // all the squares from the top left one to the right bottom
    _t_GridLineColsSquareBFlags _squares{};

    // all the lines from top to bottom
    _t_GridLineColsSquareBFlags _lines{};

    // all the columns from top to bottom
    _t_GridLineColsSquareBFlags _cols{};

    t_SudokuGrid _grid{};
};

std::ostream &operator<<(std::ostream &os, const Grid &grid)
{
    /*for (auto l : grid.getGrid())
    {
        for (auto c : l)
        {
            os << ((char)((c == 0) ? '.' : (int)c + '0')) << " ";
        }
        os << std::endl;
    }*/

    for (size_t i = 0; i < SUDOKU_LINE_LENGTH; ++i)
    {

        if (i % SUDOKU_BLOCK_LENGTH == 0)
        {
            for (size_t j = 0; j < SUDOKU_LINE_LENGTH *2 + 4; ++j)
            {
                os << "_";
            }
            os << std::endl;
        }
        for (size_t j = 0; j < SUDOKU_LINE_LENGTH; ++j)
        {
            if (j % SUDOKU_BLOCK_LENGTH == 0)
                os << "|";
            os << ((char)((grid.getGrid()[i][j] == 0) ? '.' : (int)grid.getGrid()[i][j] + '0')) << " ";
        }
        os << "|" << std::endl;
    }
        for (size_t j = 0; j < (SUDOKU_LINE_LENGTH << 1) + 4; ++j)
            {
                os << "_";
            }
            os << std::endl;

    return os;
}