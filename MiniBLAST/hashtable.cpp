#include <utility>
#include "hashtable.h"
#include <iostream>
#include <string>
using namespace std;

Hashtable::Hashtable() {
	//sets variables to defaults in case nothing is
	//passed in
	max_occupancy = 0.5;
	size = 100;
	curr_occupancy = 0;
	vector<Node> p (size, Node("",0) );
	table = p;
}
unsigned int Hashtable::hashFunc(string s){
	//dbj2 by Dan Bernstein
		unsigned int hash = 5581;
		for (unsigned int i = 0;i<s.size();i++){
			hash=((hash<<5)+hash)+s[i];
		} //for each letter, multiply by 33, add char		
		return hash%size;
}
void Hashtable::setSize(int s) {
	//if given a size, reset the table
	size = s;
	vector<Node> p (size, Node("",0) );
	table = p;
}
void Hashtable::calculateOccupancy() {
	//helper function of O(1). Calculates occupancy to decide
	//if we need to resize the table
	if(float(curr_occupancy)/float(size)>max_occupancy) {
		resize();
	}
}
vector<int> Hashtable::find(const string& k) {
	//this find is specifically for queries, and returns the vector
	//of positions to be analyzed
	unsigned int hashvalue = hashFunc(k);
    Node entry = table[hashvalue];
    if (entry.val == k) {
	    return entry.positions;
	} else {
		//if it is not stored in its hashed index, linearly probe table
		while (!entry.isEmpty()&&hashvalue<table.size()) {
			entry = table[hashvalue];
			if (entry.val == k) {
			return entry.positions; }
			hashvalue++;
		}
		for (unsigned int i=0;i<hashFunc(k);i++) {
			entry = table[i];
			if (entry.val == k) {
			return entry.positions; }
		}
	}
	//if nothing was found, make a blank vector and return it.
	vector<int> s;
    return s;
}
void Hashtable::printTable() {
	//function for debugging, simply prints each item in table
	for (unsigned int i = 0;i<table.size();i++) {
		if(!table[i].isEmpty()) {
			cout<<table[i].val<<endl;
		}
	}
};
void Hashtable::insert(const string& k, int pos) {
	unsigned int hashvalue = hashFunc(k);
	//
	while(!table[hashvalue].isEmpty()&&(table[hashvalue].val!=k)) {
		//using ++ will go out of bounds, using modulo keeps it within
		//the tablesize
		hashvalue = (hashvalue+1)%size;
	}
	if(table[hashvalue].isEmpty()) {
		//if we found a blank node, this counts as a new occupancy
		table[hashvalue].positions.push_back(pos);
		table[hashvalue].val = k;
		curr_occupancy++;
	} else if (table[hashvalue].val==k) {
		table[hashvalue].positions.push_back(pos);
	} else {
		//if nothing was found from hash to end, go through the
		//beginning of the table looking for matches or blanks.
		//this is collision handling as linear probing
		for (unsigned int i=0;i<hashFunc(k);i++) {
			if (table[i].val == k) {
				table[i].positions.push_back(pos);
			} else if (table[i].isEmpty()) {
				table[i].positions.push_back(pos);
				table[i].val = k;
				curr_occupancy++;
			}
		}
	}
	//after each node is inserted, figure out if we need to resize
	calculateOccupancy();
}

void Hashtable::resize() {
	//every time it is called, it doubles the size of the table
	size*=2;
	vector<Node> p (size, Node("",0) );
	//new vector of new size filled with blanks
	for (unsigned int i=0; i<table.size();i++) {
		Node entry = table[i]; //grabs each entry in the table 
		if (!entry.isEmpty()) { //if not blank, copy it to new table
			unsigned int hashvalue = hashFunc(entry.val);
			//entry must be rehashed for new size
			while(!p[hashvalue].isEmpty()) {
				hashvalue =(hashvalue+1)%size;
			} //inserted into blank node
			p[hashvalue].val = entry.val;
			p[hashvalue].positions = entry.positions;
		}
	}
	table = p;	
}
int Match::getMismatches() {
	//compares query string to current and increments mismatch
	//for each letter that doesn't match
	mismatch = 0;
	for (unsigned int i=0; i<query.size(); i++) {
		if (query[i]!=val[i]) {
			mismatch++;
		}
	}
	return mismatch;
}
void Match::printMatch() {
	//prints each match. easier access to variables as member function
	cout<<pos<<" "<<mismatch<<" "<<val<<endl;
}
bool matchsort(const Match& m1, const Match& m2) {
	//on small it appeared outputs were sorted, not actually used
	if(m1.mismatch<m2.mismatch) {
		return true;
	}
	return false;
}
