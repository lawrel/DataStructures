# B+ TREE
2017

ESTIMATE OF # OF HOURS:  20

Data can only be stored on the leaf nodes while internal nodes can only store the key values.
Leaf nodes are in singly linked lists

TESTING & DEBUGGING STRATEGY: 

The first thing I did was implement print sideways, and have it print
for all the test cases where I failed asserts. This helped me visualise where
split was putting things. I compile in drmemory, and when I failed, I used 
gdb to backtrace to the line where the crash happened. I try to account for NULL
pointers and leaves everywhere I can, but I was ultimately unsuccessful in 
figuring out how to split the tree properly.
