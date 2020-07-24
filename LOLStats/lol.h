#ifndef __lol_h_
#define __lol_h_
#include <string>
#include <vector>
#include <iostream>
using namespace std;
//ALL FUNCTIONS OF LOL EXPLAINED WITHIN LOL.CPP
class LOL {
	public:
	LOL(string aName);
	
	//Accessors
	const int kills() const {return kills_;}
	const int deaths() const {return deaths_;}
	const int wins() const {return wins_;}
	const int losses() const {return losses_;}
	const int minion_deaths() const {return minion_deaths_;}
	const string name() const {return name_;}
	const float kdr() const {return kdr_;}
	const float win_percent() const {return win_percent_;}
	const vector<string> champions_used() const {return champions_used_;}
	const float kpm() const {return kpm_;}
	const float dpm() const {return dpm_;}
	const float ktdpm() const {return ktdpm_;}
	
	//Modifiers
	void calculate_kdr();
	void calculate_win_percent();
	bool addChampion(string champion);
	void addKill(int timestamp);
	void addDeath(int timestamp);
	void addMinionDeath();
	void addWinOrLoss(int flag);
	bool calculate_kpm();
	bool calculate_dpm();
	void calculate_ktdpm();
	void sortChampions();
	
	private: //Representation
	string name_;
	int kills_;
	int deaths_;
	int wins_;
	int losses_;
	int minion_deaths_;
	vector<int> time_kills_; //stores the timestamps a player killed in all matches
	vector<int> time_deaths_; //stores the timestamps a player died in all matches
	float kdr_;
	float win_percent_;
	vector<string> champions_used_; //all the champions a player used in all matches
	float kpm_; //kills per minute
	float dpm_; //deaths per minute
	float ktdpm_; //kills to deaths per minute
};
//sorting functions
bool higher_kdr(const LOL& P1, const LOL& P2);
bool higher_win_percent(const LOL& P1, const LOL& P2);
bool higher_ktdpm(const LOL&P1,const LOL& P2);
//functions that output the chart for each option
void output_champions(ostream& outfile, const vector<LOL> &champions);
void output_player(ostream& outfile,const vector<LOL> &players);
void output_custom(ostream& outfile, const vector<LOL> &players);
#endif