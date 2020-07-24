#include <vector>
#include <iostream>
#include <string>
#include <list>
using namespace std;
void print_board(const vector<vector<char> >& board) {
	cout<<"Board:"<<endl;
	for (unsigned int i = 0; i<board.size(); i++) {
		cout<<"  ";
		for (unsigned int j = 0; j<board[i].size(); j++) {
			cout<<board[i][j];
		}
		cout<<endl;
	}
}

bool blankspace(const vector<vector<char> >&grid, int& row, int& col) {
	for (unsigned int r=0; r<grid.size(); ++r) {
		for (unsigned int c=0; c<grid[r].size(); ++c) {
				if (grid[r][c]=='.') {
					row = r;
					col = c;
					return true;
				}
		}
	}
	return false;	
}
void printlist(const list<vector<vector<char> > >& solutions) {
	cout<<solutions.size()<<" solution(s)"<<endl;
	list<vector<vector<char> > >::const_iterator itr;
	for (itr = solutions.begin(); itr!=solutions.end();itr++) {
		print_board(*itr);
	}
}
bool ispalindrome(const string& word) {
	if (word == string(word.rbegin(), word.rend())) {
		return true;
	}
	return false;
}
bool search_from_loc(unsigned int x,unsigned int y, 
const vector<vector<char> >& board,const string& word) {

	bool found = false;
	if ((board[0].size())-y >= word.size()) {
		for (unsigned int i = 0; i<word.size(); i++) {
			if (board[x][y+i] != word[i]) {
				found = false;
				break;
			} // checks right/east
			found = true;
		}
	} 
	if (y+1>=word.size()&& !found) {
		for (unsigned int i = 0; i<word.size(); i++) {
			if(board[x][y-i] != word[i]) {
				found = false;
				break;
			} //checks left/west
			found = true;
		}

	} 
	if ((board.size())-x >= word.size() && !found) {
		for (unsigned int i = 0; i<word.size(); i++) {
			if(board[x+i][y] != word[i]) {
				found = false;
				break;
			}
			found = true;
		}		
	} 
	if (x+1>=word.size()&& !found) {
		for (unsigned int i = 0; i<word.size(); i++) {
			if(board[x-i][y] != word[i]) {
				found = false;
				break;
			}
			found = true;
		}
	} 
	if (((board.size())-x >= word.size())&&
	((board[0].size())-y >= word.size())&& !found) {
		found = true;
		for (unsigned int i = 0; i<word.size(); i++) {
			if(board[x+i][y+i] != word[i]) {
				found = false;
				break;
			}
		}
	}
	if ((y+1>=word.size())&&(x+1>=word.size())&& !found) {
		for (unsigned int i = 0; i<word.size(); i++) {
			if(board[x-i][y-i] != word[i]) {
				found = false;
				break;
			}
			found = true;
		}
	}
	if (((board.size())-x >= word.size())&&(y+1>=word.size())&& !found) {
		for (unsigned int i = 0; i<word.size(); i++) {
			if(board[x+i][y-i] != word[i]) {
				found = false;
				break;
			}
			found = true;
		}
	} 
	if ((x+1>=word.size())&&((board[0].size())-y >= word.size())&& !found) {
		for (unsigned int i = 0; i<word.size(); i++) {
			if(board[x-i][y+i] != word[i]) {
				break;
			}
			found = true;
		}
	} 
	if (found) {
		return true;
	} else {
	return false; }
}
void fillRemaining(list<vector<vector<char> > >& solutions,
const vector<vector<char> >& grid) {
	vector<vector<char> >temp;
	string alp = string("abcdefghijklmnopqrstuvwxyz");
	int row,col;
	if (!blankspace(grid,row,col)) {
		solutions.push_back(grid);
	} else {
	
	for (unsigned int i = 0; i<alp.size();i++) {
		temp = grid;
		temp[row][col] = alp[i];
		fillRemaining(solutions,temp);				
		}
	}
}
void driver(list<vector<vector<char> > >& solutions) {
	list<vector<vector<char> > >::iterator itr;
	list<vector<vector<char> > > temp, solutioncopy;
	temp = solutions;
	for (itr = temp.begin(); itr!=temp.end();itr++) {
		fillRemaining(solutioncopy,(*itr));
	}
	solutions = solutioncopy;
}
void reject_boards(list<vector<vector<char> > >& solutions, 
const vector<string>& reject) {
	list<vector<vector<char> > >::iterator itr;
	for (itr = solutions.begin(); itr!=solutions.end();itr++) {
	bool found = false;
	for (unsigned int i=0; i<reject.size()&& !found; i++)  {
		for (unsigned int r=0; r<(*itr).size() && !found; ++r) 
			for (unsigned int c=0; c<(*itr)[r].size() && !found; ++c) {
				if ((*itr)[r][c] == reject[i][0] && 
				search_from_loc(r,c, (*itr), reject[i])) {
					found = true;
				}
			}
		}
	if (found) {
		itr = solutions.erase(itr);
		itr--;
	}
	}
	}
int main() {
	vector<vector<char> > one,two,three,four,five;
	vector<char> temp1,temp2,temp3,temp4;
	temp1.push_back('.');
	temp1.push_back('a');
	temp1.push_back('t');
	temp2.push_back('e');
	temp2.push_back('n');
	temp2.push_back('o');
	temp3.push_back('s');
	temp3.push_back('u');
	temp3.push_back('n');
	temp4.push_back('f');
	temp4.push_back('u');
	temp4.push_back('n');
	one.push_back(temp1);
	one.push_back(temp2);
	
	two.push_back(temp2);
	two.push_back(temp3);
	
	three.push_back(temp3);
	three.push_back(temp1);
	
	four.push_back(temp3);
	four.push_back(temp4);
	vector<vector<char> > blank;
	for (int i = 0; i<3; i++) {
	  vector<char> temp;
	  for (int j = 0; j<3; j++) {
		  temp.push_back('.');
	  }
	  blank.push_back(temp);
	}
	ispalindrome(string("tenet"));
	ispalindrome(string("but"));
	list<vector<vector<char> > > solutions;
	solutions.push_back(two);
	solutions.push_back(one);
	printlist(solutions);
	vector<string> reject;
	cout<<"Filled:"<<endl;
	driver(solutions);
	printlist(solutions);
	return 0;
}