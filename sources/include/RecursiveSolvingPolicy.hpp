#pragma once

#include "SudokuSolver.hpp"

class RecursiveSolverPolicy
{
  public:
    RecursiveSolverPolicy(Grid &grid, t_SudoPossibilities &sp) : _grid(grid),
                                                                 _possibilities(sp)
    {
    }

    bool algo(uint16_t index)
    {
        // static int incr = 0;
        // incr++;
        for (; index < SUDOKU_FULL_LENGTH && !_possibilities[index][0]; ++index)
            ;
        if (index == SUDOKU_FULL_LENGTH) {
            return true;
        }
        // std::cout << (int)incr << std::endl;
        int x = index % SUDOKU_LINE_LENGTH;
        int y = index / SUDOKU_LINE_LENGTH;
        for (uint16_t i = 0; i < SUDOKU_LINE_LENGTH && _possibilities[index][i]; ++i)
        {
            if (_grid.doesANumberFitInThisPlace(_possibilities[index][i], y, x))
            {
                _grid.placeNumber(_possibilities[index][i], y, x);
                if (algo(index + 1))
                    return true;
            }
        }
        _grid.placeNumber(0, y, x);
        return false;
    }

    bool resolve()
    {
        return algo(0);
    }

  private:
    Grid &_grid;
    t_SudoPossibilities &_possibilities;
};