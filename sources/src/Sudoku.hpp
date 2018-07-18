#pragma once

#include <stack>
#include <utility>
#include "Grid.hpp"
typedef std::array<std::array<uint8_t, SUDOKU_LINE_LENGTH>, SUDOKU_FULL_LENGTH> t_SudoPossibilities;

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
        std::stack<std::pair<uint8_t, uint8_t>> stack;

        uint8_t possibleNbsIndex = 0;

        bool found = false;
        // iterate through all the grid
        for (uint8_t i = 0; i < SUDOKU_FULL_LENGTH;)
        {

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

class RecursiveSolverPolicy
{
  public:
    RecursiveSolverPolicy(Grid &grid, t_SudoPossibilities &sp) : _grid(grid),
                                                                 _possibilities(sp)
    {
    }

    bool algo(uint8_t index)
    {
        for (; index < SUDOKU_FULL_LENGTH && !_possibilities[index][0]; ++index)
            ;
        if (index == SUDOKU_FULL_LENGTH)
            return true;
        for (uint8_t i = 0; i < SUDOKU_LINE_LENGTH; ++i)
        {
            if (_grid.doesANumberFitInThisPlace(_possibilities[index][i], index / SUDOKU_LINE_LENGTH, index % SUDOKU_LINE_LENGTH))
            {
                _grid.placeNumber(_possibilities[index][i], index / SUDOKU_LINE_LENGTH, index % SUDOKU_LINE_LENGTH);
                if (algo(index + 1))
                    return true;
            }
        }
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

template <class SolverPolicy>
class SudokuSolver : private SolverPolicy
{
    // using SolverPolicy::SolverPolicy(Grid &grid, t_SudoPossibilities &sp, t_SudokuPossibilitiesPtr &spPtr);
  public:
    SudokuSolver(Grid &grid) : SolverPolicy(grid, _possibilities), _grid(grid)
    {
        for (uint8_t y = 0, inlineIncr = 0; y < SUDOKU_LINE_LENGTH; ++y)
        {
            for (uint8_t x = 0; x < SUDOKU_LINE_LENGTH; ++x, ++inlineIncr)
            {
                uint8_t matchNb = 0;

                if (grid.thereIsAlreadyANumber(y, x))
                    continue;

                for (uint8_t i = 1; i < SUDOKU_LINE_LENGTH + 1; ++i)
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
                    grid.placeNumber(_possibilities[inlineIncr][matchNb], y, x);
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