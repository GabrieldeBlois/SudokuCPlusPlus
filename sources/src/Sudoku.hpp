#pragma once

#include "Grid.hpp"
typedef std::array<uint8_t, SUDOKU_FULL_LENGTH> t_SudokuPossibilitiesPtr;

typedef std::array<std::array<uint8_t, SUDOKU_LINE_LENGTH>, SUDOKU_FULL_LENGTH> t_SudoPossibilities;

class IterativeFastSolverPolicy
{
  public:
    IterativeFastSolverPolicy(Grid &grid, t_SudoPossibilities &sp, t_SudokuPossibilitiesPtr &spPtr) : _grid(grid),
                                                                                         _possibilities(sp),
                                                                                         _possibilitiesPtr(spPtr)
    {
    }

  protected:
  private:
    Grid &_grid;
    t_SudoPossibilities &_possibilities;
    t_SudokuPossibilitiesPtr &_possibilitiesPtr;

};

template <class SolverPolicy>
class SudokuSolver : private SolverPolicy
{
    // using SolverPolicy::SolverPolicy(Grid &grid, t_SudoPossibilities &sp, t_SudokuPossibilitiesPtr &spPtr);
    public: 
    SudokuSolver(Grid &grid) : SolverPolicy::SolverPolicy(grid, _possibilities, _possibilitiesPtr), _grid(grid)
    {
        for (uint8_t y = 0, inlineIncr = 0; y < SUDOKU_LINE_LENGTH; ++y)
        {
            for (uint8_t x = 0; x < SUDOKU_LINE_LENGTH; ++x, ++inlineIncr)
            {
                // all ptr back to zero;
                _possibilitiesPtr[inlineIncr] = 0;

                uint8_t matchNb = 0;

                for (uint8_t i = 0; i < SUDOKU_LINE_LENGTH; ++i)
                {
                    if (grid.doesANumberFitInThisPlace(i, y, x))
                    {
                        _possibilities[inlineIncr][matchNb++] = i;
                    }
                }

                // If there is only one matching number:
                // place it in the grid and do not display it as a possibility
                if (matchNb == 1)
                {
                    --matchNb;
                    grid.placeNumber(_possibilities[inlineIncr][matchNb], y, x);
                }
                _possibilities[inlineIncr][matchNb] = 0;
            }
        }
    }

  private:
    static t_SudoPossibilities _possibilities;
    t_SudokuPossibilitiesPtr _possibilitiesPtr {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    };

    Grid &_grid;
};