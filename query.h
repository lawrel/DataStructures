#ifndef __query_h_
#define __query_h_
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;
class Query {
	public:
	Query(string q; int m);
	void printMatches();
	private:
	string query;
	int max_mismatch;
	list<pair<string,int> > matches;
};
#endif