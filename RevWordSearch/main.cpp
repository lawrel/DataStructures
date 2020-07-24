#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

bool compare(const string& a, const string& b){
	//function to sort list by putting largest words first
    return (a.size() > b.size()); 
}
bool blankspace(const vector<vector<char> >&grid, int& row, int& col) {
	//checks if there is a blank space in the given grid
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
void print_board(const vector<vector<char> >& grid,ofstream& out) {
	//prints one grid to the output in the format
	out<<"Board:"<<endl;
	for (unsigned int i = 0; i<grid.size(); i++) {
		out<<"  ";
		for (unsigned int j = 0; j<grid[i].size(); j++) {
			out<<grid[i][j];
		}
		out<<endl;
	}
}
void printlist(const list<vector<vector<char> > >& solutions,ofstream& out) {
	//for each solution in the list, calls print_board to output
	out<<solutions.size()<<" solution(s)"<<endl;
	list<vector<vector<char> > >::const_iterator itr;
	for (itr = solutions.begin(); itr!=solutions.end();itr++) {
		print_board((*itr),out);
	}
}
bool ispalindrome(const string& word) {
	//checks if word is a palindrome. used in create to make sure
	//palindromes are only inserted half the time
	if (word == string(word.rbegin(), word.rend())) {
		return true;
	}
	return false;
}
bool search_from_loc(unsigned int x,unsigned int y, 
const vector<vector<char> >& board,const string& word) {
	//used in reject to find forbidden words in the gird.
	//checks if word is in all 8 linear directions from one point
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
			} //checks down
			found = true;
		}		
	} 
	if (x+1>=word.size()&& !found) {
		for (unsigned int i = 0; i<word.size(); i++) {
			if(board[x-i][y] != word[i]) {
				found = false;
				break;
			} //checks up
			found = true;
		}
	} 
	if (((board.size())-x >= word.size())&&
	((board[0].size())-y >= word.size())&& !found) {
		for (unsigned int i = 0; i<word.size(); i++) {
			if(board[x+i][y+i] != word[i]) {
				found = false;
				break;
			} //checks southeast
			found = true;
		}
	}
	if ((y+1>=word.size())&&(x+1>=word.size())&& !found) {
		for (unsigned int i = 0; i<word.size(); i++) {
			if(board[x-i][y-i] != word[i]) {
				found = false;
				break;
			} //checks northwest
			found = true;
		}
	}
	if (((board.size())-x >= word.size())&&(y+1>=word.size())&& !found) {
		for (unsigned int i = 0; i<word.size(); i++) {
			if(board[x+i][y-i] != word[i]) {
				found = false;
				break;
			} //checks northeast
			found = true;
		}
	} 
	if ((x+1>=word.size())&&((board[0].size())-y >= word.size())&& !found) {
		for (unsigned int i = 0; i<word.size(); i++) {
			if(board[x-i][y+i] != word[i]) {
				found = false;
				break;
			} //checks southwest
			found = true;
		}
	} 
	if (found) {
		return true;
	} else {
	return false; }
}
void create(const vector<vector<char> >& grid,const vector<string>& add,
list<vector<vector<char> > >& solutions,int pos) {
	if (pos>=add.size()) {
	//if we are at the end of words to add, this is a solution
		solutions.push_back(grid);
	} else {
	for (unsigned int row = 0; row<grid.size(); row++) {
		for (unsigned int col = 0; col<grid[0].size(); col++) {
			//for point in grid, check if word can be inserted in 
			//all 8 linear directions, if it can, recurse
			vector<vector <char> > temp;
			
			if ((grid[row][col]=='.'||grid[row][col]==add[pos][0])&&
			((grid[0].size())-col >= add[pos].size())) {
				//if there is enough room to traverse right, create a
				//copy of the grid and try to insert the word we are on
				temp = grid;
				bool success = true;
				for (unsigned int i = 0; i<add[pos].size(); i++) {
					if (temp[row][col+i] == add[pos][i]||temp[row][col+i]=='.') {
						temp[row][col+i] = add[pos][i];
					} else { success = false;}
				}
				//if it is insertable, recurse on the copy of the grid
				//and increment the position by 1
				if (success) {
				create(temp,add,solutions,pos+1);
				}
			}
			if ((grid[row][col]=='.'||grid[row][col]==add[pos][0])&&
			!ispalindrome(add[pos])&&(col+1)>=add[pos].size()) {
				//if there is enough room to traverse left, create a
				//copy of the grid and try to insert the word we are on
				bool success = true;
				temp = grid;
				for (unsigned int i = 0; i<add[pos].size(); i++) {
					if ((temp[row][col-i] == add[pos][i])||temp[row][col-i]=='.') {
						temp[row][col-i] = add[pos][i];
					} else { success = false;}
				}
				if (success) {
				create(temp,add,solutions,pos+1);
				}
			}
			if ((grid[row][col]=='.'||grid[row][col]==add[pos][0])&&
			grid.size()-row >= add[pos].size()) {
				//if there is enough room to traverse down, create a
				//copy of the grid and try to insert the word we are on
				bool success = true;
				temp = grid;
				for (unsigned int i = 0; i<add[pos].size(); i++) {
					if ((temp[row+i][col] == add[pos][i])||temp[row+i][col]=='.') {
						temp[row+i][col] = add[pos][i];
					} else { success = false;}
				}
				if (success) {
				create(temp,add,solutions,pos+1);
				}
			}
			if ((grid[row][col]=='.'||grid[row][col]==add[pos][0])&&
			!ispalindrome(add[pos])&&(row+1)>=add[pos].size()) {
				//if there is enough room to traverse up, create a
				//copy of the grid and try to insert the word we are on
				bool success = true;
				temp = grid;
				for (unsigned int i = 0; i<add[pos].size(); i++) {
					if ((temp[row-i][col] == add[pos][i])||temp[row-i][col]=='.') {
						temp[row-i][col] = add[pos][i];
					} else { success = false;}
				}
				if (success) {
				create(temp,add,solutions,pos+1);
				}
			} //diagonals
			if ((grid[row][col]=='.'||grid[row][col]==add[pos][0])&&
			(col+1>=add[pos].size())&&(row+1>=add[pos].size())) {
				//if there is enough room to traverse northwest, create a
				//copy of the grid and try to insert the word we are on
				bool success = true;
				temp = grid;
				for (unsigned int i = 0; i<add[pos].size(); i++) {
					if ((temp[row-i][col-i] == add[pos][i])||temp[row-i][col-i]=='.') {
						temp[row-i][col-i] = add[pos][i];
					} else { success = false;}
				}
				if (success) {
				create(temp,add,solutions,pos+1);
				}
			}
			if ((grid[row][col]=='.'||grid[row][col]==add[pos][0])&&
			!ispalindrome(add[pos])&&((grid.size())-row >= add[pos].size())&&
			((grid[0].size())-col >= add[pos].size())) {
				//if there is enough room to traverse southeast, create a
				//copy of the grid and try to insert the word we are on
				bool success = true;
				temp = grid;
				for (unsigned int i = 0; i<add[pos].size(); i++) {
					if ((temp[row+i][col+i] == add[pos][i])||temp[row+i][col+i]=='.') {
						temp[row+i][col+i] = add[pos][i];
					} else { success = false;}
				}
				if (success) {
				create(temp,add,solutions,pos+1);
				}
			}
			if ((grid[row][col]=='.'||grid[row][col]==add[pos][0])&&
			((grid.size())-row >= add[pos].size())&&(col+1)>=add[pos].size()) {
				//if there is enough room to traverse southwest create a
				//copy of the grid and try to insert the word we are on
				bool success = true;
				temp = grid;
				for (unsigned int i = 0; i<add[pos].size(); i++) {
					if ((temp[row+i][col-i] == add[pos][i])||temp[row+i][col-i]=='.') {
						temp[row+i][col-i] = add[pos][i];
					} else { success = false;}
				}
				if (success) {
				create(temp,add,solutions,pos+1);
				}
			}
			if ((grid[row][col]=='.'||grid[row][col]==add[pos][0])&&
			!ispalindrome(add[pos])&&(row+1>=add[pos].size())&&
			((grid[0].size())-col >= add[pos].size())) {
				//if there is enough room to traverse northeast, create a
				//copy of the grid and try to insert the word we are on
				bool success = true;
				temp = grid;
				for (unsigned int i = 0; i<add[pos].size(); i++) {
					if ((temp[row-i][col+i] == add[pos][i])||temp[row-i][col+i]=='.') {
						temp[row-i][col+i] = add[pos][i];
					} else { success = false;}
				}
				if (success) {
				create(temp,add,solutions,pos+1);
				}
			}
		}
		}
	}
}
void reject_boards(list<vector<vector<char> > >& solutions, 
const vector<string>& reject) {
	//for board in list of solutions, for point in board, search
	//for forbidden word of list
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
	//if forbidden word found, remove that board from solutions
	if (found) {
		itr = solutions.erase(itr);
		itr--;
	}
	}
	}
void fillRemaining(list<vector<vector<char> > >& solutions,
const vector<vector<char> >& grid) {
	vector<vector<char> >temp;
	string alp = string("abcdefghijklmnopqrstuvwxyz");
	int row,col;
	//if the grid has a blankspace, create 26 new grids and fill space
	//with every letter of the alphabet. recurse til board is full
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
void remove_dupes(list<vector<vector<char> > >& solutions) {
	//locate duplicate grids in list and remove them
	list<vector<vector<char> > >::iterator itr;
	  list<vector<vector<char> > >::iterator itr2;
	  for (itr = solutions.begin(); itr!=solutions.end();itr++) {
		  for (itr2 = solutions.begin(); itr2!=solutions.end();itr2++) {
			  if (itr != itr2) {
				  bool isdupe = true;
				  for (unsigned int i = 0; i<(*itr).size(); i++) {
					for (unsigned int j = 0; j<(*itr)[i].size(); j++) {
						if ((*itr)[i][j]!=(*itr2)[i][j]) {
							isdupe = false;
							break;
						}
					}
					if (!isdupe) {
							break;
						}
				  }
				  if (isdupe) {
					itr2 = solutions.erase(itr2);
					itr2--;
				  }
						
			  }
		}
	  }
}
void fillBlanks(list<vector<vector<char> > >& solutions) {
	//for solution in list, fill blanks in it using fillRemaining
	list<vector<vector<char> > >::iterator itr;
	list<vector<vector<char> > > temp, solutioncopy;
	temp = solutions;
	//must use a copy to iterate or will loop infinitely as things added
	for (itr = temp.begin(); itr!=temp.end();itr++) {
		fillRemaining(solutioncopy,(*itr));
	}
	solutions = solutioncopy;
}
int main(int argc, char* argv[]) {
	//verify input and output files are real
	ifstream instr(argv[1]);
	if (!instr) {
    cerr << "Could not open " << argv[1] << endl;
    return 1;
  }
  ofstream out(argv[2]);
  if (!out) {
    cerr << "Could not open " << argv[2] << endl;
    return 1;
  }
  //parse the file, read in rows and cols and create blank grid
  int cols,rows;
  instr>>cols>>rows;
  vector<vector<char> > blank;
  for (int i = 0; i<rows; i++) {
	  vector<char> temp;
	  for (int j = 0; j<cols; j++) {
		  temp.push_back('.');
	  }
	  blank.push_back(temp);
  }
  //parse all the words, add to lists to add or reject
  string state,word;
  vector<string> add, reject;
  while (instr>>state>>word) {
	  if (state == "+") {
		add.push_back(word);
	  }
	  if(state == "-") {
		  reject.push_back(word);
	  }
  }
  sort(add.begin(),add.end(),compare);
  //create blank list of solutions and create grids
  list<vector<vector<char> > > solutions;
  if (string(argv[3]) == "one_solution") {
	  create(blank,add,solutions,0);
	  reject_boards(solutions,reject);
	  fillBlanks(solutions); 
	  reject_boards(solutions,reject);
	  if (solutions.size()==0) {
		  out<<"No solutions found";
	  } else {
		  print_board((*solutions.begin()),out);
	  } //for one solution, it doesn't matter if there are
	  //duplicate boards in solutions since only one is output
  } else if (string(argv[3]) == "all_solutions") {
	  create(blank,add,solutions,0);
	  reject_boards(solutions,reject);
	  fillBlanks(solutions); 
	  reject_boards(solutions,reject);
	  remove_dupes(solutions);
	  if (solutions.size()==0) {
		  out<<"No solutions found";
	  } else {
		  printlist(solutions,out);
	  }
  }
  //note: for speed reasons, reject is called twice. no point creating
  //26^n copies of a grid if it contains a banned word
	return 0;
}
