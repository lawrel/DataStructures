#include <iostream>
#include "hashtable.h"
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;

const string ParseForVec(ifstream& g, int k, vector<Node>& extra) {
	//extra credit function
	string temp;
	string genome = "";
	while(g>>temp) {
		genome+=temp; }
	unsigned int pos = 0;
	while((pos+k)<genome.size()) {
		vector<Node>::iterator it = extra.begin();
		for (;it!=extra.end();it++) {
			if((*it)==genome.substr(pos,k)) {
				break;
			}
		}
		if (it==extra.end()) {
		   extra.push_back(Node(genome.substr(pos,k),pos));
		} else {
			(*it).positions.push_back(pos);
		}
		pos+=1;
	}
	return genome;
}
void findQueryVec(const string& q, int m, int k, vector<Node>& extra,
string& genome) {
	//extra credit function
	string match;
	bool ran = false;
	vector<Node>::iterator it = extra.begin();
	for (;it!=extra.end();it++) {
		if((*it)==q.substr(0,k)) {
			break;
		}
	}
	cout<<"Query: "<<q<<endl;
	if (it!=extra.end()) {
	vector<int> pos = (*it).positions;
	vector<Match> matches;
	//for each position, create a new match object
	for (unsigned int i=0;i<pos.size();i++) {
		if ((pos[i]+q.size())<genome.size()) {
			match = genome.substr(pos[i],q.size());
			matches.push_back(Match(match,pos[i],q));
			
		}
	}
	for (unsigned int i=0;i<matches.size();i++) {
		matches[i].getMismatches();
	}
	for (unsigned int i=0;i<matches.size();i++) {
		if (matches[i].mismatch<=m) {
			ran=true;
			matches[i].printMatch();
		}
	}
	}
	if(!ran) {
		cout<<"No Match"<<endl;
	}
}
const string parseGenome(ifstream& g, int k, 
Hashtable& Table) {
	//each newline creates a new string when read in,
	//so the genome must first be put together
	string temp;
	string genome = "";
	while(g>>temp) {
		genome+=temp; }
	//now, for each character in genome, a new kmer is added to
	//the hashtable. 
	unsigned int pos = 0;
	while((pos+k)<genome.size()) {
		Table.insert(genome.substr(pos,k),pos);
		pos+=1;
	}
	//return genome so we can use it again in FindQuery
	return genome;
}
void findQuery(const string& q, int m, int k, Hashtable& Table,
string& genome) {
	string match;
	//find the first kmer in query in the data, grab its positions.
	vector<int> pos = Table.find(q.substr(0,k));
	vector<Match> matches;
	//for each position, create a new match object
	for (unsigned int i=0;i<pos.size();i++) {
		if ((pos[i]+q.size())<genome.size()) {
			match = genome.substr(pos[i],q.size());
			matches.push_back(Match(match,pos[i],q));
			
		}
	}
	bool ran = false;
	cout<<"Query: "<<q<<endl;
	//while calculating the mismatches could have been done in the
	//above loop, the program runs about 0.030 seconds faster this way.
	for (unsigned int i=0;i<matches.size();i++) {
		matches[i].getMismatches();
	}
	//print all the matches, skipping those above the max mismatches
	for (unsigned int i=0;i<matches.size();i++) {
		if (matches[i].mismatch<=m) {
			ran=true;
			matches[i].printMatch();
		}
	}
	//if none printed, print no matches.
	if(!ran) {
		cout<<"No Match"<<endl;
	}
}
int main() {
	//all variables declared in the broadest scope so they
	//can be accessed anywhere in the loop.
	Hashtable Table;
	vector<Node> extra;
	string command;
	int k,tablesize,mismatch;
	float occupancy;
	string query,filename,gene;
		
	while(cin>>command) {
		if(command=="genome") {
			cin>>filename;
			
		} else if(command=="occupancy") {
			cin>>occupancy;
			Table.setOccupancy(occupancy);
			
		} else if(command=="table_size") {
			cin>>tablesize;
			Table.setSize(tablesize);
			
		} else if(command=="kmer") {
			//in order to be used in this scope, genome must be
			//read in here as opposed to when the fileame is read
			cin>>k;
			Table.setKmer(k);
			ifstream genome(filename.c_str());
			if(!genome) {
				cerr<<"Could not open file "<<filename<<endl;
				return 1;
			}
			gene = parseGenome(genome,k,Table);
			//uncomment to run as vector - extra credit
			//gene = ParseForVec(genome,k,extra);
			
		} else if(command=="query") {
			cin>>mismatch>>query;
			findQuery(query,mismatch,k,Table,gene);
			//uncomment to run as vector - extra credit
			//findQueryVec(query,mismatch,k,extra,gene);
		} else if (command=="quit") {
			break;
		} else {
			cerr<<"ERROR: Invalid command "<<command<<endl;
			return 1;
		}
	}
	return 0;
}