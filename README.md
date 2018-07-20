# SudokuCPlusPlus
An implementation of an optimized sudoku solver and generator in c++

One of my first school project in university was to create a sudoku in C. I remember that in the worst case scenario (the sudoku grid named "worstcase.txt") my solver took like more than one second to solve it.
So I wanted to recode a sudoku solver in C++ now (three years later) and see what i've learnt.

This project has no real utility since there are a lot of sudoku solver on the net by now. I just wanted to try to make something faster :D

If you want to optimize it more, feel free !!

# How does it work ?
The solver is reading the STDIN for a sudoku grid to solve.
A grid looks like this:

52.48.7.. 

.1..2.64. 

.47..9... 

9.....4.. 

735...892 

..2.....5 

...8..36. 

.53.6..8. 

..6.34.57 
The . representing the placeholders.

To launch the program, simply run:
"make" in the root directory
"./bin/solver"

Or if you want to use already existing grids in the ressources folder, use:
"./bin/solver < ./ressources/[yourGrid].txt"

# The generator
If you want to generate a sudoku grid, simply put an argument to the program such as:
"./bin/solver x"

I optimized a lot this solver. One of the biggest optimization is the binarization of the numbers in the grid.
