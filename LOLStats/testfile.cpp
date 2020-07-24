#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "player.h"
#include "champion.h"
using namespace std;
//ALL FUNCTIONS OF CLASS EXPLAINED WITHIN CLASS.CPP
bool isNotInList(vector<string>&players,string playername) {
	//determines if string is NOT in list of strings
	for (unsigned int i =0; i<players.size(); i++) {
		if (players[i]== playername) {
			return false;
		}
	}
	return true;
}
int findIndexSTR(vector<string> &players, string player) {
	//returns the index location of a string in a vector
	for (unsigned int i =0; i<players.size(); i++) {
		if (players[i] == player) {
			return i;
		}
	}
	return 0;
}
void buildLists(int flag,string champion,string player,vector<string> &player_names,
	 vector<string> &champion_names, vector<PLAYER> &players, vector<CHAMPION> &champions) {
	//function to determine if the player/champion already is in the list of players/champions
	if (isNotInListPLAYER(players,player)) {
		players.push_back(PLAYER(player));
	}//if player does not exist, creates new PLAYER object and pushes into vector
	if (isNotInListCHAMP(champions,champion)) {
		champions.push_back(CHAMPION(champion)); 
	}//if champion does not exist, creates new CHAMPION object and pushes into vector
	player_names.push_back(player); //saves player name to vector for that specific match
	champion_names.push_back(champion); //saves champion name to vector for that specific match
	players[findIndexPLAYER(players,player)].addChampion(champion); 
	//adds current champion to list the player has used
	champions[findIndexCHAMP(champions,champion)].addWinOrLoss(flag); 
	//adds win or loss dependent on flag
}
string parse_file2(ifstream& infile, vector<PLAYER> &players, vector<CHAMPION> &champions, 
	int flag1,int flag2) {
		//parses ONE MATCH of the input
	string temp;
	string temp2;
	int timestamp;
	string player;
	string champion;
	vector<string> player_names;
	vector<string> champion_names;
	infile>>temp>>player;
	while (player!="LOSING"&&player!="EVENTS"&&player=="WINNING") {
		infile>>temp>>temp2>>champion;
		buildLists(flag1,champion,player,player_names,champion_names,players,champions);
		infile>>player;
		} 
	if (player=="LOSING"||player=="WINNING") {
		infile>>temp>>player;
		while (player!="WINNING"&&player!="EVENTS"&&player!="LOSING") {
			infile>>temp>>temp2>>champion;
			buildLists(flag2,champion,player,player_names,champion_names,players,champions);
			infile>>player;
			}
		}
	if (player=="EVENTS") {
		infile>>temp;
		while(temp!="END") {
			int minion = 1; //this flag tells the program a minion killed the player
			infile>>timestamp>>player;
			if (player!="minion") {
				players[findIndexPLAYER(players,player)].addKill(timestamp);
				minion = 0; //if player not a minion, give them a kill and set minion flag to 0
				}
				while(temp!="killed") {
					infile>>temp;
				}
				infile>>player; //reads in player that was killed and adds death
				players[findIndexPLAYER(players,player)].addDeath(timestamp);
				if (minion ==1) { //death by minion added to both player and champion he used if minion flag is 1
					int i = findIndexSTR(player_names,player);
					champions[findIndexCHAMP(champions,champion_names[i])].addMinionDeathC();	
					players[findIndexPLAYER(players,player)].addMinionDeathP();
				}					
				infile>>temp;
				}
			}
		return temp;
}
void parse_file(ifstream& infile, vector<PLAYER> &players, vector<CHAMPION> &champions) {
	string player;
	while (infile>>player) {
		if (player=="WINNING") { 
		//case 1: WINNING TEAM appears first
			player = parse_file2(infile,players, champions, 1, 0);
		} //case 2: LOSING TEAM appears first
		if (player=="LOSING") {
			player = parse_file2(infile,players, champions, 0, 1);
		}
	}
} 
int main(int argc, char* argv[]) {
	vector<PLAYER> players;
	vector<CHAMPION> champions;
	ifstream infile(argv[1]);
	if (!infile.good()) { //tests that file is valid
		cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}
	//if infile is good, pass it to be parsed
	parse_file(infile,players,champions);
	ofstream outfile(argv[2]);
	if (!outfile.good()) { //tests that out file is valid
		cerr << "Can't open " << argv[2] << " to write.\n";
		exit(1);
	}
	
	if (string(argv[3])=="players") {
		//if players, calculate kill:death rate for each player in vector
		for (unsigned int i=0; i<players.size();i++) {
			players[i].calculate_kdr();
		}
		sort(players.begin(),players.end(),higher_kdr); //sort players by highest kdr
		output_player(outfile,players); //write into file
		
	} else if (string(argv[3])=="champions") {
		//if champions, calculate percent matches won for each champion in vector
		for (unsigned int i=0; i<champions.size();i++) {
			champions[i].calculate_win_percent(); 
		}
		sort(champions.begin(),champions.end(),higher_win_percent); //sort champions by highest win%
		output_champions(outfile,champions); //write info to file
		
	} else if (string(argv[3])=="custom") {
		//if custom, calculate death/min, kills/min, and kills:death/min for each player in vector
		for (unsigned int i=0; i<players.size();i++) {
			players[i].calculate_kpm();
			players[i].calculate_dpm();
			players[i].calculate_ktdpm();
		}
		sort(players.begin(),players.end(),higher_ktdpm); //sort players by highest ktdpm
		output_custom(outfile,players); //write info to file
		
	} else { 
	//if invalid command, exits program
		cerr<<"Invalid command :"<<argv[3]<<endl;
		exit(1);
	}
	return 0;
}