#include <iostream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ifstream>
using namespace std;
// a constamt for genrating seat aisle labels
const std::string ALPHABET("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
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
int main() {
	int row = 3;
	size_t col = 2;
	string a="3B"
	bool flag = GetSeatRowCol(a,8,4,row,col);
	cout<<row<<endl<<col;
}