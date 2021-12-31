# peg-solver
Solves the popular tabletop "jump all but one" triangular peg game, and outputs all solutions to a text file.

Each hole in the board is notated as such:

0 1 2 3 4\
5 6 7  8\
9 10 11\
12 13\
14

The 15 hole configuration is only solvable if the starting hole is one of the three corners,
this defaults to hole zero. Beginning with hole 4 and 14 produce symmetrical answers.

