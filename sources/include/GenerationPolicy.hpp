#pragma once

#include <random>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "SudokuSolver.hpp"
#include "RecursiveSolvingPolicy.hpp"

class GenerationPolicy
{
  public:
    GenerationPolicy(Grid &grid, t_SudoPossibilities &sp) : _grid(grid),
                                                            _possibilities(sp)
    {
    }

  protected:
    bool resolve()
    {
        createRandomPossibleSudoku(0);

        randomlyEraseNumbersUntilPossible();

        return true;
    }

    void randomlyEraseNumbersUntilPossible()
    {
        std::vector<int> alreadyUsed(SUDOKU_FULL_LENGTH);

        int randomIndex;
        for (size_t i = 0; i < SUDOKU_FULL_LENGTH; i++)
        {
            randomIndex = getRandomIndexBasedOnAlreadyUsedNumbers(alreadyUsed);
            Grid newGrid = _grid; // TODO default CTOR

            newGrid.placeNumber(0,
                                randomIndex / SUDOKU_LINE_LENGTH,
                                randomIndex % SUDOKU_LINE_LENGTH);

            SudokuSolver<RecursiveSolvingPolicy> newSolver(newGrid);

            if (newSolver.resolve()) {
                _grid.placeNumber(0,
                                randomIndex / SUDOKU_LINE_LENGTH,
                                randomIndex % SUDOKU_LINE_LENGTH);
            }
        }
    }

  private:
    int getRandomIndexBasedOnAlreadyUsedNumbers(std::vector<int> &aUsedNbs)
    {
        std::vector<int> allPossible(SUDOKU_FULL_LENGTH);

        for (size_t i = 0; i < SUDOKU_FULL_LENGTH; i++)
        {
            allPossible.push_back(i);
        }

        std::vector<int> result(SUDOKU_FULL_LENGTH);

        auto it = std::set_difference(allPossible.begin(),
                                      allPossible.end(),
                                      aUsedNbs.begin(),
                                      aUsedNbs.end(),
                                      result.begin());
        result.resize(it - result.begin());

        std::random_device rd; // non-deterministic generator
        std::mt19937 gen(rd());

        return (result.at(gen() % result.size()));
    }

    bool createRandomPossibleSudoku(int index)
    {
        if (index == SUDOKU_FULL_LENGTH)
        {
            return true;
        }
        // std::cout << (int)incr << std::endl;
        int x = index % SUDOKU_LINE_LENGTH;
        int y = index / SUDOKU_LINE_LENGTH;

        unsigned int bAlreadyUsed = 0;

        std::random_device rd;  // non-deterministic generator
        std::mt19937 gen(rd()); // to seed mersenne twister.
                                // replace the call to rd() with a
                                // constant value to get repeatable
                                // results.
        for (uint16_t i = 0; bAlreadyUsed != 0x1FF; ++i)
        {

            int diceRoll;
            unsigned int bDiceRoll;

            do
            {
                // diceRoll = distribution(generator);
                diceRoll = (gen() % 9) + 1;
                bDiceRoll = (1 << (diceRoll - 1));
            }
            // while bDiceRoll IS IN bAlreadyUsed
            while (bDiceRoll & bAlreadyUsed);
            // std::cout << _grid << std::endl;

            // put the new try in already used numbers
            bAlreadyUsed |= (1 << (diceRoll - 1));
            if (_grid.doesANumberFitInThisPlace(diceRoll, y, x))
            {
                _grid.placeNumber(diceRoll, y, x);
                if (createRandomPossibleSudoku(index + 1))
                    return true;
            }
        }
        _grid.placeNumber(0, y, x);
        return false;
    }

    Grid &_grid;
    t_SudoPossibilities &_possibilities;
};