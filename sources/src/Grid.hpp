#pragma once

#include <iostream>

#define SUDOKU_LINE_LENGTH (9)
#define SUDOKU_BLOCK_LENGTH (SUDOKU_LINE_LENGTH / 3)
#define SUDOKU_FULL_LENGTH (SUDOKU_LINE_LENGTH * SUDOKU_LINE_LENGTH)
#define SUDOKU_FIND_SQUARE(y, x) (y * SUDOKU_BLOCK_LENGTH + x % SUDOKU_BLOCK_LENGTH)

typedef std::array<std::array<uint8_t, SUDOKU_LINE_LENGTH>, SUDOKU_LINE_LENGTH> t_SudokuGrid;

class Grid
{
  public:
    Grid()
    {
    }

    ~Grid() {

    }

    // Returns the grid
    const t_SudokuGrid &getGrid() const
    {
        return _grid;
    }

    bool thereIsAlreadyANumber(uint8_t y, uint8_t x) {
        return _grid[y][x];
    }

    // Removes a number in the grid by placing another one at the given (x, y) position
    // If you just want to remove a number, just call this function with number = 0;
    void placeNumber(uint8_t number, uint8_t y, uint8_t x)
    {
        unsigned int oldNumber = _grid[y][x];

        // if the olNumber in the grid != 0, removes it
        if (oldNumber != 0)
        {
            oldNumber = ~(1 << (oldNumber - 1));
            _squares[SUDOKU_FIND_SQUARE(y, x)] &= oldNumber;
            _lines[y] &= oldNumber;
            _cols[x] &= oldNumber;
        }

        // put the number in the grid
        _grid[y][x] = number;

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

    // Determine if a Number fits according to columns, lines and squares
    bool doesANumberFitInThisPlace(uint8_t number, uint8_t y, uint8_t x) const
    {
        // get the binary form from the number
        unsigned int bNumber = 1 << (number - 1);
        // return true if the number is NOT in squares OR cols OR lines
        // tip: an boolean evaluation on any type is considered true if the value is NOT zero
        return !(_squares[SUDOKU_FIND_SQUARE(y, x)] & bNumber ||
                 _lines[y] & bNumber ||
                 _cols[x] & bNumber);
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

    t_SudokuGrid _grid;
};

std::ostream &operator<<(std::ostream &os, const Grid &grid)
{
    for (auto l : grid.getGrid())
    {
        for (auto c : l)
        {
            os << ((char)((c == 0) ? '.' : c + '0'));
        }
        os << std::endl;
    }
    return os;
}