# AIRLINE SEATING


ESTIMATE OF # OF HOURS: 10

### EXPLANATION OF REMOVING PASSENGERS FROM UPGRADE LIST:
I made two 1D vectors of strings, one for businessClass and one for firstClass upgrades. If the passenger could not
get a seat in their preferred class, and was a frequent flier, the passenger ID was added to the vector of the 
class above the one requested. When canceling, the passenger's ID would be replaced with a ".", since we were not
allowed to use .erase(). In the upgrade and print functions, there was an if statement that skipped over any "."s
in the vectors. After going through the entirity of both vectors assigning seats in upgrade, both vectors are cleared.

The srn function is used in both the upgrade and ssr functions to find seats, and returns a boolean so these functions
can print their statements.
The isNotInVector function is used in place of find() which requires iterators.
All comments are put below the function definition, but before the block they describe is executed.
