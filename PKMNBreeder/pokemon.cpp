#include "pokemon.h"
#include <vector>
#include <string>
using namespace std;
Pokemon::Pokemon(const map<string,vector<string> >& facts) {
	map<string,vector<string> >::const_iterator itr = facts.begin();
	//read in the map and grab variables if they exist
	for(;itr!=facts.end();itr++) {
		if(itr->first=="id") {
			id = itr->second[0];
		} else if (itr->first=="label") {
			label = itr->second[0];
		} else if (itr->first=="species") {
			species = itr->second[0];
		} else if (itr->first=="genderThreshold") {
			genderThreshold = itr->second[0];
		} else if (itr->first=="catchRate") {
			catchRate = itr->second[0];
		} else if (itr->first=="hatchCounter") {
			hatchCounter = itr->second[0];
		} else if (itr->first=="height") {
			height = itr->second[0];
		} else if (itr->first=="weight") {
			weight = itr->second[0];
		} else if (itr->first=="baseExpYield") {
			baseExpYield = itr->second[0];
		} else if (itr->first=="baseFriendship") {
			baseFriendship = itr->second[0];
		} else if (itr->first=="expGroup") {
			expGroup = itr->second[0];
		} else if (itr->first=="color") {
			color = itr->second[0];
		} else if (itr->first=="types") {
			types = itr->second;
		} else if (itr->first=="abilities") {
			abilities = itr->second;
		} else if (itr->first=="eggGroups") {
			eggGroups = itr->second;
		} else if (itr->first=="evYield") {
			evYield = itr->second;
		} else if (itr->first=="baseStats") {
			baseStats = itr->second;
		} else if (itr->first=="bodyStyle") {
			bodyStyle = itr->second[0];
		}
	}
}
bool Pokemon::SharesEggGroup(Pokemon* other) {
	//determines if two pokemon can breed by comparing all of their egg groups
	for (unsigned int i=0; i<this->eggGroups.size();i++) {
		for (unsigned int j=0; j<other->eggGroups.size();j++) {
			if(this->eggGroups[i]=="Undiscovered"||other->eggGroups[j]=="Undiscovered") {
				//undiscovered pokemon cannot breed at all
				return false;
			} else if (this->eggGroups[i]==other->eggGroups[j]&&this->eggGroups[i]!="Ditto") {
				//if they have the same egg group, they can breed (unless they are Dittos)
				return true;
			} else if ((this->eggGroups[i]=="Ditto"&&other->eggGroups[j]!="Ditto")
			||(other->eggGroups[j]=="Ditto"&&this->eggGroups[i]!="Ditto")) {
				//Ditto can breed with anything but itself
				return true;
			}
		}
	}
	return false;
}
bool isEggGroup(const map<string,vector<string> >& facts, const string& type) {
	//for each egg group class, checks that a pokemon read in as a map is not part of that group
	map<string,vector<string> >::const_iterator itr = facts.begin();
	for(;itr!=facts.end();itr++) {
		if(itr->first=="eggGroups") {
	//checks that the pokemon is part target egg group
		for(unsigned int i=0;i<itr->second.size(); i++) {
			if(itr->second[i]==type) { return false;}
		}
		//exception will be thrown since no matches found
		return true;
		}
	}
	return true;
}
//Egg Group Constructors - all use isEggGroup to determine if pokemon is in the group
Monster::Monster(const map<string,vector<string> >& facts): Pokemon(facts) {
	if(isEggGroup(facts,string("Monster"))) {throw 1;}
}
Field::Field(const map<string,vector<string> >& facts): Pokemon(facts) {
	if(isEggGroup(facts,string("Field"))) {throw 1;}
}
HumanLike::HumanLike(const map<string,vector<string> >& facts): Pokemon(facts) {
	if(isEggGroup(facts,string("HumanLike"))) {throw 1;}
}
Water1::Water1(const map<string,vector<string> >& facts): Pokemon(facts) {
	if(isEggGroup(facts,string("Water1"))) {throw 1;}
}
Grass::Grass(const map<string,vector<string> >& facts): Pokemon(facts) {
	if(isEggGroup(facts,string("Grass"))) {throw 1;}
}
Bug::Bug(const map<string,vector<string> >& facts): Pokemon(facts) {
	if(isEggGroup(facts,string("Bug"))) {throw 1;}
}
Mineral::Mineral(const map<string,vector<string> >& facts): Pokemon(facts) {
	if(isEggGroup(facts,string("Mineral"))) {throw 1;}
}
Undiscovered::Undiscovered(const map<string,vector<string> >& facts): Pokemon(facts) {
	if(isEggGroup(facts,string("Undiscovered"))) {throw 1;}
}
Water2::Water2(const map<string,vector<string> >& facts): Pokemon(facts) {
	if(isEggGroup(facts,string("Water2"))) {throw 1;}
}
Water3::Water3(const map<string,vector<string> >& facts): Pokemon(facts) {
	if(isEggGroup(facts,string("Water3"))) {throw 1;}
}
Amorphous::Amorphous(const map<string,vector<string> >& facts): Pokemon(facts) {
	if(isEggGroup(facts,string("Amorphous"))) {throw 1;}
}
Flying::Flying(const map<string,vector<string> >& facts): Pokemon(facts) {
	if(isEggGroup(facts,string("Flying"))) {throw 1;}
}
Dragon::Dragon(const map<string,vector<string> >& facts): Pokemon(facts) {
	if(isEggGroup(facts,string("Dragon"))) {throw 1;}
}
Ditto::Ditto(const map<string,vector<string> >& facts): Pokemon(facts) {
	if(isEggGroup(facts,string("Ditto"))) {throw 1;}
}
Fairy::Fairy(const map<string,vector<string> >& facts): Pokemon(facts) {
	if(isEggGroup(facts,string("Fairy"))) {throw 1;}
}
//Pokemon Constructors - have all been tested against the entire pokedex, and these facts
//correctly determine what is what.
Sunkern::Sunkern(const map<string,vector<string> >& facts): Grass(facts) {
	map<string,vector<string> >::const_iterator itr = facts.begin();
	for(;itr!=facts.end();itr++) {
		if((itr->first=="types"&&itr->second[0]!="Grass")||(itr->first=="types"&&
		itr->second.size()!=1) ||(itr->first=="color"&&itr->second[0]!="Yellow")) {
			throw 1;}
	}
}
Sunflora::Sunflora(const map<string,vector<string> >& facts): Sunkern(facts) {
	map<string,vector<string> >::const_iterator itr = facts.begin();
	for(;itr!=facts.end();itr++) {
		if((itr->first=="types"&&itr->second[0]!="Grass")||(itr->first=="types"&&
		itr->second.size()!=1) ||(itr->first=="color"&&itr->second[0]!="Yellow")||
		(itr->first=="species"&&itr->second[0]!="Sun")) {
			throw 1;
		}
	}
}
Spheal::Spheal(const map<string,vector<string> >& facts): Pokemon(facts), Field(facts), Water1(facts) {
	map<string,vector<string> >::const_iterator itr = facts.begin();
	for(;itr!=facts.end();itr++) {
		if((itr->first=="types"&&itr->second.size()!=2)||(itr->first=="types"&&itr->second[0]!=
		"Ice"&&itr->second[1]!="Water")||(itr->first=="color"&&itr->second[0]!="Blue")) {
			throw 1;}
	}
}
Sealeo::Sealeo(const map<string,vector<string> >& facts): Pokemon(facts), Spheal(facts) {
	map<string,vector<string> >::const_iterator itr = facts.begin();
	for(;itr!=facts.end();itr++) {
		if((itr->first=="types"&&itr->second.size()!=2)||(itr->first=="types"&&itr->second[0]!=
		"Ice"&&itr->second[1]!="Water")||(itr->first=="color"&&itr->second[0]!="Blue")||
		(itr->first=="height"&&itr->second[0]!="1.100000"&&itr->second[0]!="1.400000")||
		(itr->first=="baseExpYield"&&itr->second[0]!="144"&&itr->second[0]!="239")) {
			throw 1;}
	}
}
Walrein::Walrein(const map<string,vector<string> >& facts): Pokemon(facts), Sealeo(facts) {
	map<string,vector<string> >::const_iterator itr = facts.begin();
	for(;itr!=facts.end();itr++) {
		if((itr->first=="types"&&itr->second.size()!=2)||(itr->first=="types"&&itr->second[0]!=
		"Ice"&&itr->second[1]!="Water")||(itr->first=="color"&&itr->second[0]!="Blue")||
		(itr->first=="height"&&itr->second[0]!="1.400000")||(itr->first=="baseExpYield"&&
		itr->second[0]!="239")||(itr->first=="species"&&itr->second[0]!="IceBreak")) {
			throw 1;}
	}
}
Chimchar::Chimchar(const map<string,vector<string> >& facts): Pokemon(facts), Field(facts), HumanLike(facts){
	map<string,vector<string> >::const_iterator itr = facts.begin();
	for(;itr!=facts.end();itr++) {
		if((itr->first=="types"&&itr->second[0]!="Fire")||(itr->first=="color"&&
		itr->second[0]!="Brown")) {
			throw 1;}
	}
}
Monferno::Monferno(const map<string,vector<string> >& facts): Pokemon(facts), Chimchar(facts) {
	map<string,vector<string> >::const_iterator itr = facts.begin();
	for(;itr!=facts.end();itr++) {
		if((itr->first=="types"&&itr->second.size()!=2)||(itr->first=="types"&&itr->second[0]!=
		"Fire"&&itr->second[1]!="Fighting")||(itr->first=="color"&&itr->second[0]!="Brown")) {
			throw 1;}
	}
}
Infernape::Infernape(const map<string,vector<string> >& facts): Pokemon(facts),Monferno(facts) {
	map<string,vector<string> >::const_iterator itr = facts.begin();
	for(;itr!=facts.end();itr++) {
		if((itr->first=="types"&&itr->second.size()!=2)||(itr->first=="types"&&itr->second[0]!=
		"Fire"&&itr->second[1]!="Fighting")||(itr->first=="color"&&itr->second[0]!="Brown")||
		(itr->first=="species"&&itr->second[0]!="Flame")) {
			throw 1;}
	}
}
Amaura::Amaura(const map<string,vector<string> >& facts): Monster(facts) {
	map<string,vector<string> >::const_iterator itr = facts.begin();
	for(;itr!=facts.end();itr++) {
		if((itr->first=="types"&&itr->second.size()!=2)||(itr->first=="types"&&(itr->second[0]!=
		"Rock"||itr->second[1]!="Ice"))||(itr->first=="color"&&itr->second[0]!="Blue")) {
		throw 1;}
	}
}
Aurorus::Aurorus(const map<string,vector<string> >& facts): Amaura(facts) {
	map<string,vector<string> >::const_iterator itr = facts.begin();
	for(;itr!=facts.end();itr++) {
		if((itr->first=="types"&&itr->second.size()!=2)||(itr->first=="types"&&(itr->second[0]!=
		"Rock"||itr->second[1]!="Ice"))||(itr->first=="color"&&itr->second[0]!="Blue")||
		(itr->first=="baseExpYield"&&itr->second[0]!="104")) {
		throw 1;}
	}
}