# INVERSE WORD SEARCH
ESTIMATE OF # OF HOURS:  12


## ALGORITHM ANALYSIS:

b = # of blankspaces, w = width of grid, h = height of grid  
r = required words, f = forbidden words, s = # of solutions

| TASK | TIME |
|:----:|:----:|
|creation of initial grids| O(w*h*r^8)  |
|rejection of forbidden words:| O(s*w*h*8r*f) | 
|filling blanks: |O(s*w*h*26^b)  |
|clearing duplicates| O(s^2*w*h)  |


## TEST CASE SUMMARY:
| TEST CASE | TIME |
|-----------|:----:|
|puzzle1 |0.045s|
|puzzle1 one sol| 0.063s  |
|puzzle2 |0.063s|  
|puzzle3| 0.092s  |
|puzzle4 |0.052s  |
|puzzle5| 0.053s|
|puzzle6 |0.105s|
|puzzle7| 0.702s|
|puzzle8| 3.155s|
|puzzle9| 0.091s|
|puzzle10| 0.048s|
|puzzle11| 0.433s | 
|puzzle12| 0.036s  |

Puzzle 9 is a case where one word is too long to be inserted  
Puzzle 10 is a test case with short enough words but no possible solutions  
Puzzle 11 is a case with 2496 solutions. It is meant to test performance when handling a large list of solutions.  
Puzzle 12 tests what happens when a grid of size 0 is passed in.  
