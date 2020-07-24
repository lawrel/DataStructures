# RADIO SONG GROUPS

ESTIMATE OF # OF HOURS:  12



## ALGORITHM ANALYSIS:
s = the number of songs in the library,  
g = the number of song groups, a = the average number of songs by the same 
artist, and l = the average length of song groups.

AddSongToLibrary O(s*s) 

GroupExists O(g)

AddToGroup O(l)

MakeGroup O(1)

PrintGroupRewind O(l*l)

PrintLongestGroupRewind O(l*l)

RemoveGroup O(l*g)

DeleteAllSongGroups O(l*g)

RemoveFromGroup O(l*g)

PrintGroupMarathon O(l*l)



## TESTING & DEBUGGING STRATEGY: 

The most commonly ignored test case was an empty group, through most tests. I wrote
a few sample inputs of my own to test these cases, as well as a bunch for RemoveGroup
and CombineGroups which had no provided cases. I used gdb to track some of the values of
pointers, but mostly wrote my own inputs to test each function case by case and compiled
directly in Dr. Memory.
