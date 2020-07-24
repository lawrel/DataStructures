#ifndef __hashtable_h_
#define __hashtable_h_
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;
class Node {
	//class to store each kmer and its positions
	public:
	Node() {val="";}
	//so the node knows if it is empty
	bool isEmpty() {if(val==""){return true;} return false;}
	Node(string v, int pos) {
		val = v; positions.push_back(pos); }
	bool operator==(const string& value) {
		if(this->val==value) {return true;} return false;
	}
	string val;
	vector<int> positions;
};
class Hashtable {
	//all comments on functions in the hashtable.cpp file
	public:
	Hashtable();
	void setKmer(int k) {kmer=k;};
	void setOccupancy(float o) {max_occupancy=o;};
	void setSize(int s);
	
	void calculateOccupancy();
	vector<int> find(const string& k);
	void insert(const string& k, int pos);
	void resize();
	unsigned int hashFunc(string s);
	void printTable();
	
	private:
	int size;
	int kmer;
	float max_occupancy;
	int curr_occupancy;
	vector<Node> table;
};
class Match {
	//class to store data for each match that is found
	public:
	Match(string s, int p, string q) {
		pos = p; val = s; query = q;
	}
	int getMismatches();
	void printMatch();
	int pos;
	int mismatch;
	string val;
	string query;
};
bool matchsort(const Match& m1, const Match& m2);
#endif
