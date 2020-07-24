#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;
// a constamt for genrating seat aisle labels
const string ALPHABET("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

bool isNotInVector(vector<string> vec, string x) {
	for (unsigned int i =0;i<vec.size();i++) {
		if (x == vec[i]) {
		return false;
		}
	}
	return true;
}
bool GetSeatRowCol(const string& seat_request, unsigned int total_rows,
		   unsigned int total_columns,int& seat_row, size_t& seat_col) {
  
  string row_str;
  string col_str;
  for (unsigned int i = 0; i < seat_request.size(); ++i) {
    if (seat_request[i] >= '0' && seat_request[i] <= '9')
      row_str += seat_request[i];
    else
      col_str += seat_request[i];	
  }
    
  seat_row = atoi(row_str.c_str()) - 1;
  if (seat_row < 0 || seat_row > (int) total_rows - 1) {
    return false;
  }

  seat_col = ALPHABET.find(col_str);
  if (seat_col == string::npos || seat_col > total_columns - 1) {
    return false;
  }

  return true;
}
bool srn(vector<vector<string> > &seatingChart,string seat_request,string frequent_flier,
vector<string> &firstClass, vector<string> &businessClass, string passID, vector<string> seat_types) {
	if (seat_request!="F"&&seat_request!="C"&&seat_request!="B") {
		cout<<"Invalid seating class - "<<seat_request<<"."<<endl;
		return false;
	} else {
		for (unsigned int i=0; i<seatingChart.size();i++) {
			if (seatingChart[i][0]=="...."&&seat_types[i] == seat_request){
				seatingChart[i][0] = passID;
				cout<<"Passenger "<<passID<<" was given seat "<<i+1<<"A."<<endl;
					return true;
			} else {
				for (unsigned int s=1;s<seatingChart[i].size()-1;s++ ) {
					if (seat_types[i]==seat_request&&(seatingChart[i][s+1]=="!!!!"||
					seatingChart[i][s-1]=="!!!!")&&seatingChart[i][s]=="....") {
					seatingChart[i][s] = passID;
					cout<<"Passenger "<<passID<<" was given seat "<<i+1<<ALPHABET[s]<<"."<<endl;
					return true;
					}
				}
				
				if (seatingChart[i][seatingChart[0].size()-1]=="...."&&seat_types[i]==seat_request) {
					seatingChart[i][seatingChart[0].size()-1] = passID;
					cout<<"Passenger "<<passID<<" was given seat "<<i+1<<ALPHABET[seatingChart[0].size()-1]<<"."<<endl;
					return true;
					}
			}
		}
		
		for (unsigned int i=0; i<seatingChart.size();i++) {
			for (unsigned int s=0;s<seatingChart[i].size();s++ ) {
			if (seatingChart[i][s]=="...."&&seat_types[i] == seat_request){
				seatingChart[i][s] = passID;
				cout<<"Passenger "<<passID<<" was given seat "<<i+1<<ALPHABET[s]<<endl;
				return true;
			}
			}
		}
	if (frequent_flier == "Y"&& isNotInVector(businessClass,passID) && isNotInVector(firstClass,passID)) {
		if (seat_request=="C") {
			businessClass.push_back(passID);
		} else if (seat_request=="B"){
			firstClass.push_back(passID);
		}
	} else {
		cout<<"Could not find a seat in the "<<seat_request<<" section for passenger "<<passID<<"."<<endl;
	}
	return false;
	}
}
void ssr(vector<vector<string> > &seatingChart,string passID,string seat_request,
string frequent_flier, vector<string> &firstClass, vector<string> &businessClass,
vector<string> seat_types) {
	unsigned int total_rows = seatingChart.size();
	unsigned int total_columns = seatingChart[0].size();
	int row;
	size_t col;
	if (GetSeatRowCol(seat_request, total_rows, total_columns, row, col)) {
		if (seatingChart[row][col] == "....") {
		seatingChart[row][col] = passID;
		cout<<"Passenger "<<passID<<" was given seat "<<seat_request<<"."<<endl;
	} else if (seatingChart[row][col] == "!!!!") {
		cout<<"Passenger "<<passID<<" requested an invalid seat "<<seat_request<<"."<<endl;
		srn(seatingChart,seat_types[row],frequent_flier,firstClass,businessClass,passID,seat_types);
	} else {
		cout<<"Passenger "<<passID<<" requested occupied seat "<<seat_request<<"."<<endl;
		srn(seatingChart,seat_types[row],frequent_flier,firstClass,businessClass,passID,seat_types);
	}
} else {
	cout<<"Passenger "<<passID<<" requested an invalid seat "<<seat_request<<"."<<endl;
}
}
void upgrade(vector<vector<string> > &seatingChart,vector<string> &businessClass
, vector<string> &firstClass, vector<string> seat_types) {
	for (unsigned int i=0; i<businessClass.size();i++) {
		if (businessClass[i] != ".") {
		if (srn(seatingChart,"B","N",firstClass,businessClass,businessClass[i],seat_types)) {
			cout<<"Passenger "<<businessClass[i]<<" was upgraded to the business class section."<<endl;
		}
		}
	}
	for (unsigned int i=0; i<firstClass.size(); i++) {
		if (firstClass[i] != ".") {
		if (srn(seatingChart,"F","N",firstClass,businessClass,firstClass[i],seat_types)) {
			cout<<"Passenger "<<firstClass[i]<<" was upgraded to the first class section."<<endl;
		}
		}
	}
	firstClass.clear();
	businessClass.clear();
}
void print_upgrades(vector<string> &firstClass, vector<string> &businessClass) {
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
void cancel(vector<vector<string> > &seatingChart, vector<string> &firstClass,
vector<string> &businessClass,string passID) {
	int passFound = 0;
	for (unsigned int i =0;i<seatingChart.size();i++) {
		for (unsigned int s=0; s<seatingChart[i].size();s++) {
			if (seatingChart[i][s] == passID)  {
			seatingChart[i][s] = "....";
			passFound = 1;
			break;
			}
		}
	}
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
	if (passFound == 0) {
		cout<<"Passenger "<<passID<<" could not be found."<<endl;
	}
}
void print_chart(vector<vector<string> > &seatingChart, int flightno,vector<string> seat_types) {
	cout<<"Seating Chart for Flight "<<flightno<<endl<<"\t ";
	for (unsigned int i =0; i<seatingChart[0].size(); i++) {
		cout<<ALPHABET[i]<<"    ";
	}
	cout<<"Seating Class"<<endl; 
	for (unsigned int i=0; i<seatingChart.size();i++)		
	{   cout<<i+1<<"\t";
		for (unsigned int j=0; j<seatingChart[i].size(); j++ ) 
		{
			cout<<seatingChart[i][j]<<' ';
		}
		cout<<seat_types[i]<<endl;
	}
}
int main(int argc, char* argv[]) {
	string command;
	vector<string> seat_types;
	vector<string> firstClass;
	vector<string> businessClass;
	vector<vector<string> > seatingChart;
	ifstream in_str(argv[1]);
	string seat;
	//reaad into 2D vector
	vector<string> temp_vector;
	while (in_str>>seat) {
		if(seat!="F"&&seat!="C"&&seat!="B") {
			if (seat == "!"){
				seat = "!!!!";
			} else if (seat == ".") {
			seat = "....";}
			temp_vector.push_back(seat);
		}
		if (seat=="F"||seat=="C"||seat=="B") {
			seat_types.push_back(seat);
			if (!temp_vector.empty()){
				seatingChart.push_back(temp_vector);
				temp_vector.clear();
			}
		}
	}
	seatingChart.push_back(temp_vector);
	int flightno;
	ifstream infile(argv[2]);
	infile>>flightno;
	//
	while (infile>>command) {
		string passID;
		string seat_request;
		string frequent_flier;
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
		cout<<"Invalid command: "<<command<<endl;
	}
}
  return 0;
}