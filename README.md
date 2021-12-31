# peg-solver
<h1>Overview</h1>
Solves the popular tabletop "jump all but one" triangular peg game, and outputs all solutions to a text file.

Each hole in the board is notated as such:

```python
0   1   2   3   4
  5   6   7   8
    9   10  11
      12  13
        14        
```

The 15 hole configuration is only solvable if the starting hole is one of the three corners,
this defaults to hole zero. Beginning with hole 4 and 14 produce symmetrical answers.

<h1>Output</h1>

An example solution string:

```html
(2 -> 0) (4 -> 2) (10 -> 1) (1 -> 3) (8 -> 6) (5 -> 7) (3 -> 10) (12 -> 5) (0 -> 9) (13 -> 8) (9 -> 11) (8 -> 13) (14 -> 11) 
```
To solve, move the peg in hole 2 to the empty hole 0, then move the peg in hole 4 to hole 2, and so on, removing all pegs jumped in the process.



