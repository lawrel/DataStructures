# WORD FREQUENCY MAPS


ESTIMATE OF # OF HOURS:  6



## ANALYSIS OF PERFORMANCE:

n = total number of words in the sample text file  
m = number of unique words in the file  
w = width of the sequencing window  
p = average number of words observed to follow a particular word  
l = length of phrase


memory map data structure require:
m*p*w



What is the order notation for performance (running time) of each of
the commands?
| FUNCTION | TIME |
|----------|:----:|
| load | O(n*w*log(m)) |
| print | O(w*log(m)*p) |
|generate most common| O(l*p*log(m)*w)|
|generate random| O(l*w*log(m)*p)|

I assumed any access of a map is O(log(m)), and each window requires w accesses
to get at the integers stored in it. In generate, for each new word, all these
accesses must be made, and the innermost map totaled, so each item in it will be
accessed, adding a p. For print, it is a similar logic, you must access every
integer in the innermost map to print.
For load, each word in the file is read in (O(n)), then each must access the
innermost map and increment, for a total of w accesses, thus, the function
performs n*w accesses, so total runtime is  n*w*log(m).
