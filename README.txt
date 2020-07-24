HOMEWORK 7: MINIBLAST


NAME:  Madison Lawrence


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

dbj2 by Dan Bernstein, Prof. Holzbauer Office Hours Tuesday, Piazza

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  10


HASH FUNCTION DESCRIPTION
dbj2 by Dan Bernstein, multiplies hash seed by 33 for each character,
the simplicity of it is said to be optimal for data less than 10 bytes.
I tried a few other popular hash functions, but this one proved fastest.


HASH TABLE IMPLEMENTATION
Vector of custom nodes which hold a string value and a vector of int
positions. The Nodes are default set to have a string of "", so that
they can know if they are blank or not. This way, the vector can keep
being initialized at the full size. I use linear probing to determine
where to put the key if there is a collision.



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the map data structure require (order notation for memory use)?
(L-k)*k*p
The hashtable stores strings of length k for each character(L) in the genome,
except those shorter than length k, hence L-k. Each of these strings has p
position integers associated with it. Assuming no kmers ever repeat, the
worst case memory usage is (L-k)*k*p

What is the order notation for performance (running time) of each of
the commands?
T = size of table (includes blanks)
genome: O(1)
table_size: O(1)
occupancy: O(1)
kmer: Best: O(L-k) Worst: O((L-k)*T+T*2T)

Explanation: In the best case, for each kmer (L-k), the insertion in
to the table takes only O(1), if the hash function returns a blank index.
In the worst case, insert must search the entire table to find a blank,
then resize immediately after. Resizing takes the table size times the new table
size in the worst possible case, though the frequent resizing should prevent this
from ever actually occuring.
query: Best: O(p*q+2p) Worst: O(p*q+T+2p)

Query must first find the kmer in the table, at best O(1), at worst O(T).
Then it must loop through the found positions once to create Match objects,
then once to compare query to the found string, then a third time to print
sucessful matches. 

quit: O(1)

The point of making this as a hash table is that normally, the table will
never run worst case, and almost always run very close to best case if the
hash function is good.

EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.

Comment the regular FindQuery and ParseGenome and uncomment vector
variants to run as a vector which stores kmers in order read in.

Input_small:  Hash: 0.124s Vector: 1.216s
Input_medium: Hash: 0.163s Vector: 0.309s
Input_large:  Hash: 0.174s Vector: 2.934s
Input_larger: Hash: 1.719s Vector: 16 minutes, 49.724 seconds

Creating the table as a vector: O((L-k)*T)
Finding matches to a query: O(T+p*q+2p)
While the order notations look the same as the worst cases above, the
hash table only runs worst case if it is almost at full capacity (which
it likely never will be, since it doubles in size frequently). the vector,
however, MUST ALWAYS search every single node to prove it is truly not there,
there are no blank nodes telling it to stop. In most cases, the Hash table insert
runs 0(1), but in most cases, inserting to the vector will take the full O(T)


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


