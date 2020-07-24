#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;
// a constant for genrating seat aisle labels
const string ALPHABET("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

bool isNotInVector(vector<string> vec, string x) {
	//function used to determine if a string is in a 1D vector 
	for (unsigned int i =0;i<vec.size();i++) {
		if (x == vec[i]) {
		return false;
		}
	}
	return true;
}
bool GetSeatRowCol(const string& seat_request, unsigned int total_rows,
unsigned int total_columns,int& seat_row, size_t& seat_col) {
  //given function. splits a seat request from a string into indices for the plane seating chart
  string row_str;
  string col_str;
  for (unsigned int i = 0; i < seat_request.size(); ++i) { //splits seat request into two variables
    if (seat_request[i] >= '0' && seat_request[i] <= '9')
      row_str += seat_request[i];
    else
      col_str += seat_request[i];	
  }
    
  seat_row = atoi(row_str.c_str()) - 1; //converts letter into appropriate row index
  if (seat_row < 0 || seat_row > (int) total_rows - 1) { //determines if the seat row within bounds of plane
    return false;
  }

  seat_col = ALPHABET.find(col_str); //using position in alphabet variable, finds
  if (seat_col == string::npos || seat_col > total_columns - 1) { //determines if seat col within bounds of plane
    return false;
  }

  return true; //if both row and column are valid, returns true
}
bool srn(vector<vector<string> > &seatingChart,string seat_request,string frequent_flier,
vector<string> &firstClass, vector<string> &businessClass, string passID, vector<string> seat_types) {
	//function to assign passengers a seat based on class alone
	if (seat_request!="F"&&seat_request!="C"&&seat_request!="B") { //if the class is invalid, give an error
		cout<<"Invalid seating class - "<<seat_request<<"."<<endl;
		return false; //no attempt made to seat person
	} else {
	//else, for each row on the plane in the class, check if aisle or window seats are available
		for (unsigned int i=0; i<seatingChart.size();i++) {
			//if the first seat is available, passenger is put there
			if (seatingChart[i][0]=="...."&&seat_types[i] == seat_request){
				seatingChart[i][0] = passID;
				cout<<"Passenger "<<passID<<" was given seat "<<i+1<<"A."<<endl;
				return true;
			} else { //else, check if any aisle seats are available and place them there
				for (unsigned int s=1;s<seatingChart[i].size()-1;s++ ) {
					if (seat_types[i]==seat_request&&(seatingChart[i][s+1]=="!!!!"||
					seatingChart[i][s-1]=="!!!!")&&seatingChart[i][s]=="....") {
					seatingChart[i][s] = passID;
					cout<<"Passenger "<<passID<<" was given seat "<<i+1<<ALPHABET[s]<<"."<<endl;
					return true;
					}
				}
				//else, checks the window seat at the end of the row and assigns there
				if (seatingChart[i][seatingChart[0].size()-1]=="...."&&seat_types[i]==seat_request) {
					seatingChart[i][seatingChart[0].size()-1] = passID;
					cout<<"Passenger "<<passID<<" was given seat "<<i+1<<ALPHABET[seatingChart[0].size()-1]<<"."<<endl;
					return true;
					}
			}
		}
		//if no window or aisle seats are available on any row, iterate through to fill the middle seats
		for (unsigned int i=0; i<seatingChart.size();i++) {
			for (unsigned int s=0;s<seatingChart[i].size();s++ ) {
			if (seatingChart[i][s]=="...."&&seat_types[i] == seat_request){
				seatingChart[i][s] = passID;
				cout<<"Passenger "<<passID<<" was given seat "<<i+1<<ALPHABET[s]<<endl;
				return true;
			}
			}
		}
	//if no seats are found, and the passenger is a frequent flier, add them to a queue for the next higher class
	if (frequent_flier == "Y"&& isNotInVector(businessClass,passID) && isNotInVector(firstClass,passID)) {
		if (seat_request=="C") {
			businessClass.push_back(passID);
		} else if (seat_request=="B"){
			firstClass.push_back(passID);
		}
	//if they are not a frequent flier, they do not get a seat on the plane, and message output
	} else {
		cout<<"Could not find a seat in the "<<seat_request<<" section for passenger "<<passID<<"."<<endl;
	}
	return false;
	}
}
void ssr(vector<vector<string> > &seatingChart,string passID,string seat_request,
string frequent_flier, vector<string> &firstClass, vector<string> &businessClass,
vector<string> seat_types) { //function to seat passenger in a specific requested seat
	//get the total number of rows and columns on the plane
	unsigned int total_rows = seatingChart.size();
	unsigned int total_columns = seatingChart[0].size();
	int row;
	size_t col;
	if (GetSeatRowCol(seat_request, total_rows, total_columns, row, col)) {
		//if the seat is valid, and empty/not an aisle, seat passenger there
		if (seatingChart[row][col] == "....") {
		seatingChart[row][col] = passID;
		cout<<"Passenger "<<passID<<" was given seat "<<seat_request<<"."<<endl;
	} else if (seatingChart[row][col] == "!!!!") { //if an aisle, give an error and try to find a seat in the class
		cout<<"Passenger "<<passID<<" requested an invalid seat "<<seat_request<<"."<<endl;
		srn(seatingChart,seat_types[row],frequent_flier,firstClass,businessClass,passID,seat_types);
	} else { //if occupied, give an error and try to find a seat in requested class
		cout<<"Passenger "<<passID<<" requested an occupied seat "<<seat_request<<"."<<endl;
		srn(seatingChart,seat_types[row],frequent_flier,firstClass,businessClass,passID,seat_types);
	}
} else { //if the seat is invalid, error message is output an no attempt to seat is made
	cout<<"Passenger "<<passID<<" requested an invalid seat "<<seat_request<<"."<<endl;
}
}
void cancel(vector<vector<string> > &seatingChart, vector<string> &firstClass,
vector<string> &businessClass,string passID) {
	int passFound = 0; //flag variable to tell function if the passenger was found onboard or in any queues
	//each seat in the plane is checked, row by column, and the seat made available if passID found
	for (unsigned int i =0;i<seatingChart.size();i++) {
		for (unsigned int s=0; s<seatingChart[i].size();s++) {
			if (seatingChart[i][s] == passID)  {
			seatingChart[i][s] = "....";
			passFound = 1;
			break;
			}
		}
	}
	//each upgrade queue is checked for the passID, if found, it is replaced with "." (since erase not allowed)
	for (unsigned int i =0; i<firstClass.size(); i++) {
		if (firstClass[i] == passID) {
			firstClass[i] = ".";
			passFound = 1;
			break;
		}
	}
	for (unsigned int i =0; i<businessClass.size(); i++) {
		if (businessClass[i] == passID) {
			businessClass[i] = ".";
			passFound = 1;
			break;
		}
	}
	if (passFound == 0) { //if the passenger is not on board this flight or in a queue, print an error
		cout<<"Passenger "<<passID<<" could not be found."<<endl;
	}
}
void upgrade(vector<vector<string> > &seatingChart,vector<string> &businessClass
, vector<string> &firstClass, vector<string> seat_types) {
	//iterates through both upgrade queues and calls srn to find a seat for each one
	for (unsigned int i=0; i<firstClass.size(); i++) {
		if (firstClass[i] != ".") { //this statement skips over any cancelations, represented by "."
		if (srn(seatingChart,"F","N",firstClass,businessClass,firstClass[i],seat_types)) {
			cout<<"Passenger "<<firstClass[i]<<" was upgraded to the first class section."<<endl;
		}
		}
	}
	for (unsigned int i=0; i<businessClass.size();i++) {
		if (businessClass[i] != ".") {
		if (srn(seatingChart,"B","N",firstClass,businessClass,businessClass[i],seat_types)) {
			cout<<"Passenger "<<businessClass[i]<<" was upgraded to the business class section."<<endl;
		}
		}
	}
	firstClass.clear(); //both queues cleared, regardless of if all passengers seated
	businessClass.clear();
}
void print_upgrades(vector<string> &firstClass, vector<string> &businessClass) {
	//iterates through the two upgrade queues and prints their contents on a newline
	cout<<"The following passengers are scheduled to be upgraded to first class:"<<endl;
	for (unsigned int i=0; i<firstClass.size(); i++) {
		if (firstClass[i] != ".") {
		cout<<firstClass[i]<<endl; }
	}
	cout<<"The following passengers are scheduled to be upgraded to business class:"<<endl;
	for (unsigned int i=0; i<businessClass.size(); i++) {
		if (businessClass[i] != ".") {
	cout<<businessClass[i]<<endl; }
	}
}
void print_chart(vector<vector<string> > &seatingChart, int flightno,vector<string> seat_types) {
	cout<<"Seating Chart for Flight "<<flightno<<endl<<"\t";
	for (unsigned int i =0; i<seatingChart[0].size(); i++) {
		cout<<ALPHABET[i]<<"    "; //for the #columns in the plane, prints a letter from the alphabet
	}
	cout<<"Seating Class"<<endl; 
	for (unsigned int i=0; i<seatingChart.size();i++)		
	{   cout<<i+1<<"\t"; //prints the row # plus a tab for formatting for each row
		for (unsigned int j=0; j<seatingChart[i].size(); j++ ) 
		{
			cout<<seatingChart[i][j]<<' '; //for each row, for each column, print the seat plus a space
		}
		cout<<seat_types[i]<<endl; //prints the seating class for each row
	}
}
int main(int argc, char* argv[]) {
	//declarations for all the variables necessary for the program
	string command;
	vector<string> seat_types;
	vector<string> firstClass;
	vector<string> businessClass;
	vector<vector<string> > seatingChart;
	string seat;
	vector<string> temp_vector;
	int flightno;
	//read first file into 2D vector
	ifstream in_str(argv[1]);
	if (!in_str.good()) { //tests that file is valid
		cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}
	while (in_str>>seat) {
		if(seat!="F"&&seat!="C"&&seat!="B") { //skips class, and changes seats to print format before adding
			if (seat == "!"){                 //to a temporary vector that will be pushed back each line
				seat = "!!!!";
			} else if (seat == ".") {
			seat = "....";}
			temp_vector.push_back(seat);
		}
		if (seat=="F"||seat=="C"||seat=="B") {
			seat_types.push_back(seat); //pushes the class of seating to its own vector of just seat types
			if (!temp_vector.empty()){ 
			//since the lines start with the class, the first temp vector will be empty, this ignores empty vectors
				seatingChart.push_back(temp_vector);
				temp_vector.clear();
			}
		}
	}
	//pushes back the last vector, since lines start with classes, which were used to break up the lines
	seatingChart.push_back(temp_vector);
	//read second file in for commands
	ifstream infile(argv[2]);
	infile>>flightno;
	if (!infile.good()) { //tests that file is valid
		std::cerr << "Can't open " << argv[2] << " to read.\n";
		exit(1);
	}
	while (infile>>command) {
		//declarations for variables read in on each line
		string passID;
		string seat_request;
		string frequent_flier;
	// determines the first command of each line, reads in variables, and passes them to associated functions
	if (command == "SRN") {
		infile>>passID>>seat_request>>frequent_flier;
		srn(seatingChart,seat_request,frequent_flier,firstClass,businessClass,passID,seat_types);
	} else if (command == "SSR") {
		infile>>passID>>seat_request>>frequent_flier;
		ssr(seatingChart,passID,seat_request,frequent_flier,firstClass,businessClass,seat_types);
	} else if (command == "PRT") {
		print_chart(seatingChart,flightno,seat_types);
	} else if (command == "CXL") {
		infile>>passID;
		cancel(seatingChart,firstClass,businessClass,passID);
	} else if (command == "UPP") {
		upgrade(seatingChart,businessClass,firstClass,seat_types);
	} else if (command == "UPL") {
		print_upgrades(firstClass,businessClass);
	} else {
		cout<<"Invalid command: "<<command<<endl; //if there is no associated function, prints an error.
	}
}
  return 0;
}