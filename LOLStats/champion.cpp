#include "champion.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;
CHAMPION::CHAMPION(string aName) {
	name_ = aName;
	win_percent_ = 0.0;
	minion_deaths_ = 0;
	wins_ = 0;
	losses_= 0;
}
void CHAMPION::addMinionDeathC() { //adds minion death
	minion_deaths_++;
}
void CHAMPION::calculate_win_percent() {
	//calculates % of matches won, with 1.0 = 100%
		win_percent_= float(wins_)/float(wins_+losses_);
}
void CHAMPION::addWinOrLoss(int flag) { 
//adds a win or loss depending on what was passed in from parsing
	if (flag == 0) { //0 = loss, 1 = win
		losses_++;
	} else if (flag==1) {
		wins_++;
	}
}
bool higher_win_percent(const CHAMPION& P1, const CHAMPION& P2) {
	//sorts players by win%, then wins, then losses, then name
	if (P1.win_percent()>P2.win_percent()) {
		return true;
	} else if (P1.win_percent()==P2.win_percent()&&P1.wins()>P2.wins()) {
		return true;
	} else if (P1.win_percent()==P2.win_percent()&&P1.wins()==P2.wins()&&P1.losses()<P2.losses()) {
		return true;
	} else if (P1.win_percent()==P2.win_percent()&&P1.wins()==P2.wins()&&P1.losses()==P2.losses()
		&&P1.name()<P2.name()) {
		return true;
	}
	return false;
}
void output_champions(ostream& outfile, const vector<CHAMPION> &champions) {
	//this function outputs the chart of champions, wins, losses, win%, and minion deaths
	outfile<<left<<setw(24)<<"CHAMPION NAME"<<setw(6)<<"WINS"<<setw(10)<<"LOSSES";
	outfile<<left<<setw(7)<<"WIN%"<<"MINION DEATHS"<<endl;
	//for each champion in list, outputs their stats in format on one line each
	for (unsigned int j=0;j<champions.size();j++) {
		CHAMPION k = champions[j];
		outfile<<left<<setw(24)<<k.name()<<right<<setw(4)<<k.wins()<<setw(8)<<k.losses()<<setw(8);
		outfile<<setprecision(2)<<fixed<<k.win_percent()<<setw(16)<<k.minion_deathC()<<endl;
	}
}
bool isNotInListCHAMP(vector<CHAMPION>&champions,string champname) {
	//determines if champion is NOT in list of champions by comparing player.name() to string
	for (unsigned int i =0; i<champions.size(); i++) {
		if (champions[i].name() == champname) {
			return false;
		}
	}
	return true;
}
int findIndexCHAMP(vector<CHAMPION> &champions,string champname) {
	//returns the index location of a champion in a vector of CHAMPION objects
	for (unsigned int i =0; i<champions.size(); i++) {
		if (champions[i].name() == champname) {
			return i;
		}
	}
	return 0;
}