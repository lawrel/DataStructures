

# GENOME MINIBLAST


ESTIMATE OF # OF HOURS SPENT: 10

### HASH FUNCTION DESCRIPTION 
dbj2 by Dan Bernstein, multiplies hash seed by 33 for each character, the simplicity of it is said to be optimal for data less than 10 bytes. I tried a few other popular hash functions, but this one proved fastest.

### HASH TABLE IMPLEMENTATION 
Vector of custom nodes which hold a string value and a vector of int positions. The Nodes are default set to have a string of "", so that they can know if they are blank or not. This way, the vector can keep being initialized at the full size. I use linear probing to determine where to put the key if there is a collision.

## ANALYSIS OF PERFORMANCE:

L = length of the genome sequence q - query length p - number of different locations where key is found k - key size (k-mer size)

How much memory will the map data structure require (order notation for memory use)? (L-k)kp The hashtable stores strings of length k for each character(L) in the genome, except those shorter than length k, hence L-k. Each of these strings has p position integers associated with it. Assuming no kmers ever repeat, the worst case memory usage is (L-k)kp

What is the order notation for performance (running time) of each of the commands? T = size of table (includes blanks) 
| FUNCTION | TIME (BEST) | TIME (WORST) |
|----------|:-----------:|:------------:|
| genome | O(1) | O(1) |
|table_size| O(1) | O(1) |
|occupancy| O(1) | O(1) |
| kmer |  O(L-k) | O((L-k)T+T2T) |
| query | O(pq+2p) | O(pq+T+2p) |
| quit | O(1) | O(1) |

In the best case, for each kmer (L-k), the insertion in to the table takes only O(1), if the hash function returns a blank index. In the worst case, insert must search the entire table to find a blank, then resize immediately after. Resizing takes the table size times the new table size in the worst possible case, though the frequent resizing should prevent this from ever actually occuring.

Query must first find the kmer in the table, at best O(1), at worst O(T). Then it must loop through the found positions once to create Match objects, then once to compare query to the found string, then a third time to print sucessful matches.

The point of making this as a hash table is that normally, the table will never run worst case, and almost always run very close to best case if the hash function is good.

## VECTOR VS. HASHTABLE ANALYSIS

Comment the regular FindQuery and ParseGenome and uncomment vector variants to run as a vector which stores kmers in order read in.

| GENOME      | HASH TIME | VECTOR TIME |
|-------------|:---------:|:-----------:|
| Input_small | 0.124s    | 1.216s      |
|Input_medium | 0.163s    | 0.309s      | 
| Input_large | 0.174s    | 2.934s      |
|Input_larger | 1.719s    | 1009.724s   |

Creating the table as a vector: O((L-k)T) Finding matches to a query: O(T+pq+2p) While the order notations look the same as the worst cases above, the hash table only runs worst case if it is almost at full capacity (which it likely never will be, since it doubles in size frequently). the vector, however, MUST ALWAYS search every single node to prove it is truly not there, there are no blank nodes telling it to stop. In most cases, the Hash table insert runs 0(1), but in most cases, inserting to the vector will take the full O(T)
