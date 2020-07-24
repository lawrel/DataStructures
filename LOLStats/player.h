#ifndef __player_h_
#define __player_h_
#include <string>
#include <vector>
#include <iostream>
using namespace std;
//ALL FUNCTIONS OF PLAYER EXPLAINED WITHIN PLAYER.CPP
class PLAYER {
	public:
	PLAYER(string aName);
	
	//Accessors
	const int kills() const {return kills_;}
	const int deaths() const {return deaths_;}
	const int minion_deathP() const {return minion_deaths_;}
	const string name() const {return name_;}
	const float kdr() const {return kdr_;}
	const vector<string> champions_used() const {return champions_used_;}
	const float kpm() const {return kpm_;}
	const float dpm() const {return dpm_;}
	const float ktdpm() const {return ktdpm_;}
	
	//Modifiers
	void calculate_kdr();
	bool addChampion(string champion);
	void addKill(int timestamp);
	void addDeath(int timestamp);
	void addMinionDeathP();
	bool calculate_kpm();
	bool calculate_dpm();
	void calculate_ktdpm();
	void sortChampions();
	
	private: //Representation
	string name_;
	int kills_;
	int deaths_;
	int minion_deaths_;
	vector<int> time_kills_; //stores the timestamps a player killed in all matches
	vector<int> time_deaths_; //stores the timestamps a player died in all matches
	float kdr_;
	vector<string> champions_used_; //all the champions a player used in all matches
	float kpm_; //kills per minute
	float dpm_; //deaths per minute
	float ktdpm_; //kills to deaths per minute
};
//sorting functions
bool higher_kdr(const PLAYER& P1, const PLAYER& P2);
bool higher_ktdpm(const PLAYER&P1,const PLAYER& P2);
//functions that output the chart for each option
void output_player(ostream& outfile,const vector<PLAYER> &players);
void output_custom(ostream& outfile, const vector<PLAYER> &players);
//functions for processing vectors of PLAYERs
int findIndexPLAYER(vector<PLAYER> &players,string player);
bool isNotInListPLAYER(vector<PLAYER>&players,string playername);
#endif