#ifndef __champion_h_
#define __champion_h_
#include <string>
#include <vector>
#include <iostream>
using namespace std;
//ALL DETAILS ON FUNCTIONS INCLUDED IN champion.cpp
class CHAMPION {
	public:
	CHAMPION(string aName);
	//ACCESSORS
	const string name() const {return name_;}
	const float win_percent() const {return win_percent_;}
	const int wins() const {return wins_;}
	const int losses() const {return losses_;}
	const int minion_deathC() const {return minion_deaths_;}
	//MODIFIERS
	void calculate_win_percent();
	void addMinionDeathC();
	void addWinOrLoss(int flag);
	//REPRESENTATION
	private:
	int minion_deaths_;
	string name_;
	float win_percent_;
	int wins_;
	int losses_;
};
bool higher_win_percent(const CHAMPION& P1, const CHAMPION& P2);
void output_champions(ostream& outfile, const vector<CHAMPION> &champions);
//functions to process vector of CHAMPION objects
bool isNotInListCHAMP(vector<CHAMPION>&champions,string champname);
int findIndexCHAMP(vector<CHAMPION> &champions,string champname);
#endif