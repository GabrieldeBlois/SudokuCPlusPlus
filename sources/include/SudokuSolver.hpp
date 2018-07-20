#pragma once

#include <stack>
#include <utility>
#include "Grid.hpp"

typedef std::array<std::array<uint16_t, SUDOKU_LINE_LENGTH>, SUDOKU_FULL_LENGTH> t_SudoPossibilities;



template <class SolverPolicy>
class SudokuSolver : private SolverPolicy
{
    // using SolverPolicy::SolverPolicy(Grid &grid, t_SudoPossibilities &sp, t_SudokuPossibilitiesPtr &spPtr);
  public:
    SudokuSolver(Grid &grid) : SolverPolicy(grid, _possibilities), _grid(grid)
    {
        for (uint16_t y = 0, inlineIncr = 0; y < SUDOKU_LINE_LENGTH; ++y)
        {
            for (uint16_t x = 0; x < SUDOKU_LINE_LENGTH; ++x, ++inlineIncr)
            {
                uint16_t matchNb = 0;

                if (grid.thereIsAlreadyANumber(y, x))
                    continue;

                for (uint16_t i = 1; i < SUDOKU_LINE_LENGTH + 1; ++i)
                {
                    if (grid.doesANumberFitInThisPlace(i, y, x))
                    {
                        //std::cout << " possibilities[" << ((int)inlineIncr) << "]["<< ((int)matchNb) << "] = " << ((int)i) << std::endl;
                        _possibilities[inlineIncr][matchNb] = i;
                        matchNb++;
                    }
                }

                // If there is only one matching number:
                // place it in the grid and do not display it as a possibility
                if (matchNb == 1)
                {
                    grid.placeNumber(_possibilities[inlineIncr][matchNb - 1], y, x);
                    _possibilities[inlineIncr][0] = 0;
                }
            }
        }
    }

    void DisplayPossibilities()
    {
        for (auto l : _possibilities)
        {
            for (auto c : l)
            {
                std::cout << ((int)c) << " ";
            }
            std::cout << std::endl;
        }
    }

    bool resolve()
    {
        return SolverPolicy::resolve();
    }

  private:
    t_SudoPossibilities _possibilities{};

    Grid &_grid;
};