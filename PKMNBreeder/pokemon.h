#ifndef __pokemon_h_
#define __pokemon_h_
#include <map>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
//ALL COMMENTS ON FUNCTIONALITY IN POKEMON.CPP
class Pokemon {
	public:
	Pokemon(const map<string,vector<string> >& facts);
	virtual ~Pokemon() {};
	string getLabel() {return label;}
	bool SharesEggGroup( Pokemon* other);
	
	private:
	string id;
	string label;
	string species;
    string genderThreshold;
	string catchRate;
    string hatchCounter;
	string height;
	string weight;
    string baseExpYield;
	string baseFriendship;
    string expGroup;
	string color;
	vector<string> types;
	vector<string> abilities;
	vector<string> eggGroups;
    vector<string> evYield;
	vector<string> baseStats;
	string bodyStyle;
};
//Each class simply declares its types and a constructor
//assigned eggGroups
class Monster: public Pokemon {
	public:
	Monster(const map<string,vector<string> >& facts);
};
class Field : virtual public Pokemon {
	public:
	Field(const map<string,vector<string> >& facts);
};
class HumanLike: virtual public Pokemon {
	public:
	HumanLike(const map<string,vector<string> >& facts);
};
class Water1: virtual public Pokemon {
	public:
	Water1(const map<string,vector<string> >& facts);
};
class Grass: public Pokemon {
	public:
	Grass(const map<string,vector<string> >& facts);
};
//Assigned pokemon
class Sunkern: public Grass {
	public:
	Sunkern(const map<string,vector<string> >& facts);
};
class Sunflora: public Sunkern {
	public:
	Sunflora(const map<string,vector<string> >& facts);
};
class Spheal: public Field, public Water1{
	public:
	Spheal(const map<string,vector<string> >& facts);
};
class Sealeo: public Spheal {
	public:
	Sealeo(const map<string,vector<string> >& facts);
};
class Walrein: public Sealeo {
	public:
	Walrein(const map<string,vector<string> >& facts);
};
class Chimchar: public Field, public HumanLike {
	public:
	Chimchar(const map<string,vector<string> >& facts);
};
class Monferno: public Chimchar{
	public:
	Monferno(const map<string,vector<string> >& facts);
};
class Infernape: public Monferno {
	public:
	Infernape(const map<string,vector<string> >& facts);
};
class Amaura: public Monster {
	public:
	Amaura(const map<string,vector<string> >& facts);
};
class Aurorus: public Amaura {
	public:
	Aurorus(const map<string,vector<string> >& facts);
};
//rest of the egggroups
class Bug : public Pokemon {
	public:
	Bug(const map<string,vector<string> >& facts);
};
class Mineral : public Pokemon { 
	public:
	Mineral(const map<string,vector<string> >& facts);
};
class Undiscovered : public Pokemon { 
	public:
	Undiscovered(const map<string,vector<string> >& facts);
};
class Water2: public Pokemon { 
	public:
	Water2(const map<string,vector<string> >& facts);
};
class Water3 : public Pokemon { 
	public:
	Water3(const map<string,vector<string> >& facts);
};
class Amorphous: public Pokemon {
	public:
	Amorphous(const map<string,vector<string> >& facts);
};
class Flying : public Pokemon { 
	public:
	Flying(const map<string,vector<string> >& facts);
};
class Dragon : public Pokemon {
	public:
	Dragon(const map<string,vector<string> >& facts);
};
class Ditto : public Pokemon { 
	public:
	Ditto(const map<string,vector<string> >& facts);
};
class Fairy : public Pokemon{ 
	public:
	Fairy(const map<string,vector<string> >& facts);
};
#endif