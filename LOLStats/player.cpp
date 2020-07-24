#include "player.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;
PLAYER::PLAYER(string aName) {
	//method to create a PLAYER object from only the name being passed in
	name_ = aName;
	kills_ = 0;
	deaths_ = 0;
	deaths_ = 0;
	minion_deaths_ = 0;
	kdr_ = 0.0;
	kpm_ = 0.0;
	dpm_ = 0.0;
	ktdpm_ = 0.0;
}
void PLAYER::calculate_kdr() { //calculates kill:death rate
	if (deaths_== 0) {  //if the player didn't die, their rate is kills
		kdr_=float(kills_);
	} else {
		kdr_= float(kills_)/float(deaths_);
	}
}

bool PLAYER::addChampion(string champion) {
	//if champion in vector of champions used, do nothing, if not, add champion name to vector
	for (unsigned int i=0;i<champions_used_.size();i++) {
		if (champions_used_[i]==champion) {
			return false;
		}
	}
	champions_used_.push_back(champion);
	return true;
}
void PLAYER::addKill(int timestamp) { //adds kill and saves timestamp in vector;
	kills_++;
	time_kills_.push_back(timestamp);
}
void PLAYER::addDeath(int timestamp) { //adds death and saves timestamp in vector
	deaths_++;
	time_deaths_.push_back(timestamp);
}
void PLAYER::addMinionDeathP() { //adds minion death
	minion_deaths_++;
}
bool PLAYER::calculate_kpm() { //calculate the rate of kills per minute
	if (kills_ == 0||time_kills_.size()==1) {
		kpm_ = 0.0;//if there are no or only one kill, no calculations can be made, left at 0
		return false;
	}
	vector<float> elapsedtime;
	for (unsigned int i=0;i<time_kills_.size()-1;i++) {
		if (time_kills_[i]<time_kills_[i+1]) {
			elapsedtime.push_back(time_kills_[i+1]-time_kills_[i]);
		}//saves the difference in time between each kill out in a vector
	}
	int sum = 0;
	for (unsigned int i=0;i<elapsedtime.size();i++) {
		sum += elapsedtime[i]; //adds all the elapsed times
	}
	sum/=float(60000); //time converted from milliseconds to minutes
	kpm_ = float(elapsedtime.size())/float(sum);
	return true;
}
bool PLAYER::calculate_dpm() { //calculate the rate of deaths per minute
	if (deaths_ == 0||time_deaths_.size()==1) {
		dpm_ = 0.0; //if there are no or only one death, no calculations can be made, left at 0
		return false;
	}
	vector<int> elapsedtime;
	for (unsigned int i=0;i<time_deaths_.size()-1;i++) {
		if (time_deaths_[i]<time_deaths_[i+1]) {
			elapsedtime.push_back(time_deaths_[i+1]-time_deaths_[i]);
		}//saves the difference in time between each death out in a vector
	}
	int sum = 0;
	for (unsigned int i=0;i<elapsedtime.size();i++) {
		sum += elapsedtime[i]; //adds all the elapsed times
	}
	sum/=float(60000); //time converted from milliseconds to minutes
	dpm_ = float(elapsedtime.size())/float(sum);
	return true;
}
void PLAYER::calculate_ktdpm() {
	if(dpm_==0){ //if deaths per minute is zero, ktdpm set to kills per minute
		ktdpm_= kpm_;
	} else {
	ktdpm_ = kpm_/dpm_;
	}
}
void PLAYER::sortChampions() { //sorts list of champions used lexographically
	sort(champions_used_.begin(),champions_used_.end());
}
void output_player(ostream& outfile,const vector<PLAYER> &players) {
	//this function writes to file the chart of players, kills, deaths, kdr, and champions used by each player
	outfile<<setw(23)<<left<<"PLAYER NAME"<<setw(7)<<"KILLS"<<setw(11)<<"DEATHS"<<setw(6)<<"KDR";
	outfile<<"PLAYED WITH CHAMPION(S)"<<endl;
	for (unsigned int j=0;j<players.size();j++) {
		PLAYER k = players[j];
		outfile<<setw(23)<<left<<k.name()<<setw(5)<<right<<k.kills()<<setw(8)<<k.deaths()<<setw(8)<<setprecision(2);
		outfile<<fixed<<k.kdr()<<"   ";
		//this prints all the champions used by a player with a ", " behind it except the last one
		k.sortChampions(); 
		if (k.champions_used().size()>1) {
			for (unsigned int i=0; i<k.champions_used().size()-1;i++) {
				outfile<<k.champions_used()[i]<<", ";
			}
		}
		int i = k.champions_used().size()-1;
		outfile<<k.champions_used()[i]<<endl;
	}
}
void output_custom(ostream& outfile,const vector<PLAYER> &players) {
	//this function writes to file the chart of players kpm,dpm,ktdpm, and minion deaths
	outfile<<setw(23)<<left<<"PLAYER NAME"<<setw(7)<<"KPM"<<setw(7)<<"DPM"<<setw(7)<<"KTDPM";
	outfile<<"MINION DEATHS"<<endl;
	for (unsigned int j=0;j<players.size();j++) {
		//for each player, output their stats on a single formatted line 
		PLAYER k = players[j];
		outfile<<setw(21)<<left<<k.name()<<setw(5)<<right<<setprecision(2)<<fixed<<k.kpm()<<setw(7);
		outfile<<setprecision(2)<<fixed<<k.dpm();
		outfile<<setw(9)<<setprecision(2)<<fixed<<k.ktdpm()<<setw(15)<<k.minion_deathP()<<endl;
	}
} 
bool higher_kdr(const PLAYER& P1, const PLAYER& P2) {
	//sorts players by kdr, then kills, then deaths, then name
	if (P1.kdr()>P2.kdr()) {
		return true;
	} else if (P1.kdr()==P2.kdr()&&P1.kills()>P2.kills()) {
		return true;
	} else if (P1.kdr()==P2.kdr()&&P1.kills()==P2.kills()&&P1.deaths()<P2.deaths()) {
		return true;
	} else if (P1.kdr()==P2.kdr()&&P1.kills()==P2.kills()&&P1.deaths()==P2.deaths()&&P1.name()<P2.name()) {
		return true;
	}
	return false;
}
bool higher_ktdpm(const PLAYER&P1,const PLAYER& P2) {
	//sorts players by ktdpm, kpm, dpm, then name
	if (P1.ktdpm()>P2.ktdpm()) {
		return true;
	} else if (P1.ktdpm()==P2.ktdpm()&&P1.kpm()>P2.kpm()) {
		return true;
	} else if (P1.ktdpm()==P2.ktdpm()&&P1.kpm()==P2.kpm()&&P1.dpm()<P2.dpm()) {
		return true;
	} else if (P1.ktdpm()==P2.ktdpm()&&P1.kpm()==P2.kpm()&&P1.dpm()==P2.dpm()&&P1.name()<P2.name()) {
		return true;
	}
	return false;
}
bool isNotInListPLAYER(vector<PLAYER>&players,string playername) {
	//determines if player is NOT in list of players by comparing player.name() to string
	for (unsigned int i =0; i<players.size(); i++) {
		if (players[i].name() == playername) {
			return false;
		}
	}
	return true;
}
int findIndexPLAYER(vector<PLAYER> &players,string player) {
	//returns the index location of a player in a vector of PLAYER objects
	for (unsigned int i =0; i<players.size(); i++) {
		if (players[i].name() == player) {
			return i;
		}
	}
	return 0;
}