# MATRIX MULTIPLICATION 
ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  ~10


## ALGORITHM ANALYSIS
 m = the number of rows and n = the
number of columns.  Assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.
| FUNCTION | TIME |
|:--------:|:----:|
| get | O(1) |
| set | O(1) |
| num_rows | O(1) |
| get_column | O(m)|
| operator<< | O(m*n) |
| quarter | O(m*n)|
| operator== | O(m*n) |
| operator!= | O(m*n) |
| swap_rows | O(n) |
| rref | O((m^2)*(n^2)) |
| resize notation | O(m*n) |

The test cases provided are meant to represent every combination of calls that
could be passed in resize, using 3x3 as the before in each.


## TESTING & DEBUGGING STRATEGY: 
While testing any functions that created or deleted heap data, I compiled in
Dr Memory.
I commented out complicated tests and worked function by function, for more complicated
functions, I output a striing to the screen to check what block or line was holding things up, 
if it was not shown by Dr Memory.
