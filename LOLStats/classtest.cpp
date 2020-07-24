#include "lol.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
using namespace std;
bool isNotInList(vector<string>&players,string playername) {
	for (unsigned int i =0; i<players.size(); i++) {
		if (players[i]== playername) {
			return false;
		}
	}
	return true;
}
int findIndexSTR(vector<string> &players, string player) {
	for (unsigned int i =0; i<players.size(); i++) {
		if (players[i] == player) {
			return i;
		}
	}
	return 0;
}
bool isNotInListLOL(vector<LOL>&players,string playername) {
	for (unsigned int i =0; i<players.size(); i++) {
		if (players[i].name() == playername) {
			return false;
		}
	}
	return true;
}
int findIndexLOL(vector<LOL> &players,string player) {
	for (unsigned int i =0; i<players.size(); i++) {
		if (players[i].name() == player) {
			return i;
		}
	}
	return 0;
}
int main(int argc, char* argv[]) {
	vector<LOL> players;
	ofstream outfile(argv[1]);
	players.push_back(LOL("rose"));
	players.push_back(LOL("greg"));
	players.push_back(LOL("bob"));
	for (unsigned int i=0;i<players.size();i++) {
		players[i].addChampion("champname");
	}
	cout<<setw(23)<<left<<"PLAYER NAME"<<setw(7)<<"KPM"<<setw(7)<<"DPM"<<setw(7)<<"KTDPM";
	cout<<"MINION DEATHS"<<endl;
	for (unsigned int j=0;j<players.size();j++) {
		LOL k = players[j];
		cout<<setw(21)<<left<<k.name()<<setw(5)<<right<<setprecision(2)<<fixed<<k.kpm()<<setw(7);
		cout<<setprecision(2)<<fixed<<k.dpm();
		cout<<setw(9)<<setprecision(2)<<fixed<<k.ktdpm()<<setw(15)<<k.minion_deaths()<<endl;
	}
return 0;
}