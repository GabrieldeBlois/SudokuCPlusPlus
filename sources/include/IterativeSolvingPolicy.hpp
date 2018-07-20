#pragma once

#include "SudokuSolver.hpp"

class IterativeFastSolverPolicy
{
  public:
    IterativeFastSolverPolicy(Grid &grid, t_SudoPossibilities &sp) : _grid(grid),
                                                                     _possibilities(sp)
    {
    }

  protected:
    // resolves the sudoku in an iterative way instead of recursion
    bool resolve()
    {
        // First: The index of the cell
        // Second: The index of the current number in the _possibilities array
        std::stack<std::pair<uint16_t, uint16_t>> stack;

        uint16_t possibleNbsIndex = 0;

        bool found = false;
        // iterate through all the grid
        for (uint16_t i = 0; i < SUDOKU_FULL_LENGTH;)
        {
                found = false;

            // if there are no multiple choice for this cell,
            // it means that the current number is the right one
            if (!_possibilities[i][0])
            {
                found = true;
                ++i;
                continue;
            }

            // iterate through the different possibilities for this cell
            for (;
                 possibleNbsIndex < SUDOKU_LINE_LENGTH && _possibilities[i][possibleNbsIndex];
                 ++possibleNbsIndex)
            {
                // if a suitable number has been found
                if (_grid.doesANumberFitInThisPlace(_possibilities[i][possibleNbsIndex], i / SUDOKU_LINE_LENGTH, i % SUDOKU_LINE_LENGTH))
                {
                    _grid.placeNumber(_possibilities[i][possibleNbsIndex], i / SUDOKU_LINE_LENGTH, i % SUDOKU_LINE_LENGTH);

                    // remember the position for the backtracking stack simulation
                    stack.push(std::make_pair(i, possibleNbsIndex));
                    possibleNbsIndex = 0;
                    found = true;
                    break;
                }
            }

            // if the suitable number has been found for this cell, we don't wanna backtrack
            if (found)
            {
                ++i;
                continue;
            }

            if (stack.empty())
                return false;

            // if there is no solution for the given context -> backtrack
            _grid.placeNumber(0, i / SUDOKU_LINE_LENGTH, i % SUDOKU_LINE_LENGTH);
            auto last = stack.top();
            i = last.first;
            stack.pop();
            // we don't want to test the last number, let's try the next one
            possibleNbsIndex = last.second + 1;
        }

        return found;
    }

  private:
    Grid &_grid;
    t_SudoPossibilities &_possibilities;
};
