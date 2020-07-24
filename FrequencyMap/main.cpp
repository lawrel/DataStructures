// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// NOTE TO SELF: WHEN TESTING, USE: ./test.exe < in.txt > out.txt
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include <assert.h>
#include "mtrand.h"
using namespace std;


//different map types for the different windows, i call them frames
typedef  map<string,map<string,int> > frame2;
typedef  map<string,map<string,map<string,int> > > frame3;

//function to generate a random # from 0 to an integer n
int rand0toN(int n) {
	static MTRand_int32 mtrand;
     return (mtrand() % n);
}
//totals the instances of a word in a frame2 structure
int total2(const map<string,int>& data) {
	int occur = 0;
	map<string,int>::const_iterator itr = data.begin();
	for (itr = data.begin();itr!=data.end() ;itr++) {
		occur += itr->second;
	}
	return occur;
}
//totals the instances of a wotd in a frame3 structure
int total(const frame3 &data3, const string &w1, const string& w2) {
	int occur = 0;
	frame3::const_iterator temp1 = data3.find(w1);
	frame2::const_iterator temp = temp1->second.find(w2);
	map<string,int>::const_iterator itr = temp->second.begin();
	for (itr = temp->second.begin();itr!=temp->second.end() ;itr++) {
		occur += itr->second;
	}
	return occur;
}
//pushes back a word to a vector the number of times it occurs,
//in order to weight random selection of a word. for frame2 structures
string random2(const map<string,int>& data) {
	vector<string> options;
	string word;
	map<string,int>::const_iterator itr;
	for(itr=data.begin(); itr!=data.end();itr++) {
		for(int i =0; i<itr->second; i++) {
			options.push_back(itr->first);
		}
	}
	//selects a random word by randomly generating an index
	word = options[rand0toN(options.size())];
	return word;
}
//pushes back a word to a vector the number of times it occurs,
//in order to weight random selection of a word. for frame3 structures
string random3(const frame2& data) {
	vector<string> options;
	string word;
	frame2::const_iterator itr;
	for(itr=data.begin(); itr!=data.end();itr++) {
		for(int i =0; i<total2(itr->second); i++) {
			options.push_back(itr->first);
		}
	}
	//selects a random word by randomly generating an index
	word = options[rand0toN(options.size())];
	return word;
}
//finds the most commonly occuring word in a frame2 structure
//assuming we already have the previous word+ are inside its map
string greatest2(const map<string,int>& data) {
	string greatest;
	int maxoccur = 0;
	map<string,int>::const_iterator itr;
	for (itr = data.begin(); itr!=data.end(); itr++) {
		if (itr->second>maxoccur) {
			greatest = itr->first;
			maxoccur = itr->second;
		}
	}
	return greatest;
}
//finds the most commonly occuring word in a frame3 structure
//assuming we already have the previous word+ are inside its map
string greatest3(const frame2& data) {
	string greatest;
	int maxoccur = 0;
	frame2::const_iterator temp = data.begin();
	for (temp = data.begin(); temp!=data.end(); temp++) {
		if (total2(temp->second) > maxoccur) {
			greatest = temp->first;
			maxoccur = total2(temp->second);
		}
		
	}
	return greatest;
}

// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word. UNALTERED BY STUDENT
bool ReadNextWord(std::istream &istr, std::string &word) {
  char c;
  word.clear();
  while (istr) {
    // just "peek" at the next character in the stream
    c = istr.peek();
    if (isspace(c)) {
      // skip whitespace before a word starts
      istr.get(c);
      if (word != "") {
	// break words at whitespace
	return true;
      }
    } else if (c == '"') {
      // double quotes are a delimiter and a special "word"
      if (word == "") {
	istr.get(c);
	word.push_back(c);
      }
      return true;
    } else if (isalpha(c)) {
      // this a an alphabetic word character
      istr.get(c);
      word.push_back(tolower(c));
    } else {
      // ignore this character (probably punctuation)
      istr.get(c);
    }
  }
  return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased. UNALTERED BY STUDENT
std::vector<std::string> ReadQuotedWords(std::istream &istr) {
  // returns a vector of strings of the different words
  std::vector<std::string> answer;
  std::string word;
  bool open_quote = false;
  while (ReadNextWord(istr,word)) {
    if (word == "\"") {
      if (open_quote == false) { open_quote=true; }
      else { break; }
    } else {
      // add each word to the vector
      answer.push_back(word);
    }
  }
  return answer;
}


// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText(frame2 &data, const std::string &filename, int window, 
const std::string &parse_method, map<string,int>& wordcount, frame3 &data3) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  if (window < 2) {
    std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }
  string word,prev, prev2;
  prev = "."; prev2 = ".";
  if (window == 2) {
  while (ReadNextWord(istr,word)) {
	  wordcount[word]++;
	  // skip the quotation marks (not used for this part)
    if (word == "\"") continue;
	  if (prev!=".") {
		  data[prev][word]++;
	  }//save the previous word, add current to previous' map 
	  //and increment its value
	prev = word;
  }
  } else if (window == 3) {
	  while (ReadNextWord(istr,word)) {
	  wordcount[word]++;
	  // skip the quotation marks (not used for this part)
	  if (word == "\"") {continue;}
	  if (prev!="."&&prev2!=".") {
		  data3[prev2][prev][word]++;
	  }//save the previous two words, add current to two words 
	  //previous' map and increment its value
	  prev2 = prev;
	  prev = word;
	  }
  }
  //parsing successful, output the conditions used
  cout << "Loaded "<<filename<<" with window = "<<window<<" and parse method = "
  <<parse_method<<endl<<endl;
}


int main () {
  // set up data structures
  frame2 data;
  frame3 data3;
  map<string,int> wordcount;
  int window;
  
  // Parse each command
  std::string command;    
  while (std::cin >> command) {

    // load the sample text file
    if (command == "load") {
      std::string filename;
      std::string parse_method;
      std::cin >> filename >> window >> parse_method;      
	  LoadSampleText(data,filename,window,parse_method,wordcount,data3);
    } 

    // print the portion of the map structure with the choices for the
    // next word given a particular sequence.
    else if (command == "print") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
	  
	  if (window == 2) {
	  frame2::const_iterator itr = data.find(sentence[0]);
	  map<string,int>::const_iterator itr2;
	  //check all input to make sure the words are in the text
	  bool badword = false;
	  for (unsigned int i =0; i<sentence.size(); i++) {
		 if (data.find(sentence[i])==data.end()) {
			badword = true;
			cout<<"The word "<<sentence[i]<<"does not appear in this text."<<endl;
		   }
		 }
	  if (!badword) {
		  // check that the phrase can be accessed in the structure
	  if (sentence.size()>2||sentence.size()==0) {
			cout<<"Invalid entry, phrases must be between 1-2 words.";
			
	  } else if (sentence.size() == 2) {
		  //if two words given, access that pair and output its occurences
		  cout<<itr->first<<" "<<sentence[1]
		  <<" ("<<data[sentence[0]][sentence[1]]<<")"<<endl;
		  
	  } else {
		//if one word given, find its map, output total occurences, and 
		//every word that comes after it plus occurences
		cout<<itr->first<<" ("<<wordcount[itr->first]<<")"<<endl;
		for(itr2 = itr->second.begin();itr2!=itr->second.end();itr2++) {
			cout<<itr->first<<" "<<itr2->first<<" ("<<itr2->second<<")"<<endl;
		}
	  }
	  cout<<endl;
		 }
	  } else if (window==3) {
		frame3::const_iterator itr = data3.find(sentence[0]);
		frame2::const_iterator itr2;
	    map<string,int>::const_iterator itr3;
		//check all input to make sure the words are in the text
		bool badword = false;
		 for (unsigned int i =0; i<sentence.size(); i++) {
		 if (data3.find(sentence[i])==data3.end()) {
			 badword = true;
			 cout<<"The word "<<sentence[i]<<"does not appear in this text."<<endl;
		 }
		 }
		 if(!badword) {
		// check that the phrase can be accessed in the structure
		if (sentence.size()>3||sentence.size()==0) {
			cout<<"Invalid entry, phrases must be between 1-3 words.";
			
		}else if (sentence.size()==3) {
			//if three words are given, find that particular location and
			//out put it and its value
			cout<<sentence[0]<<" "<<sentence[1]<<" "<<sentence[2]
			<<" ("<<data3[sentence[0]][sentence[1]][sentence[2]]<<")"<<endl;
			
		} else if (sentence.size() == 2) {
			//if two words given, find its map, output total occurences, and 
		    //every word that comes after it plus its occurences
			cout<<sentence[0]<<" "<<sentence[1]<<" ("<<
			total(data3,sentence[0],sentence[1])<<")"<<endl;
			itr2 = itr->second.find(sentence[1]);
			for(itr3 = itr2->second.begin();itr3!=itr2->second.end();itr3++) {
				cout<<sentence[0]<<" "<<sentence[1]<<" "<<itr3->first
			<<" ("<<data3[sentence[0]][sentence[1]][itr3->first]<<")"<<endl;
			}
			
		} else if (sentence.size() == 1) {
			//if one word given, find its map, output total occurences, and 
		    //every word that comes after it plus its total occurences
			cout<<itr->first<<" ("<<wordcount[sentence[0]]<<")"<<endl;
			for(itr2 = itr->second.begin();itr2!=itr->second.end();itr2++) {
				cout<<itr->first<<" "<<itr2->first<<
				" ("<<total(data3,sentence[0],itr2->first)<<")"<<endl;
		}
		}
		cout<<endl;
	  }
	  }
    }

    // generate the specified number of words 
    else if (command == "generate") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      // how many additional words to generate
      int length;
      std::cin >> length;
      std::string selection_method;
      std::cin >> selection_method;
      bool random_flag;
      if (selection_method == "random") {
	    random_flag = true;
      } else {
      assert(selection_method == "most_common");
	    random_flag = false;
      }
	  string word,prev,prev2;
	  prev="."; prev2=".";
	 if (window == 2) {
		 //check all input to make sure the words are in the text
		 bool badword = false;
		 for (unsigned int i =0; i<sentence.size(); i++) {
		 if (data.find(sentence[i])==data.end()) {
			 badword = true;
			 cout<<"The word "<<sentence[i]<<"does not appear in this text."<<endl;
		   }
		 }
		 
		 if (!badword) {
		 if (random_flag){
			 //print given words and save out the last one
			 prev = sentence[sentence.size()-1];
			 for (unsigned int j =0; j<sentence.size(); j++) {
				cout<<sentence[j]<<" ";
			 }
			 //based on previous word, randomly select the next and output
			 for (int i = 0; i<length; i++) {
				word = random2(data.find(prev)->second);
				if (i==length-1) {
					cout<<word;
				} else {
					cout<<word<<" ";
				}
				prev = word;
			 }
			 cout<<endl<<endl;
			 
		 } else {
			 //print given words and save out the last one
			 prev = sentence[sentence.size()-1];
			 for (unsigned int j =0; j<sentence.size(); j++) {
				cout<<sentence[j]<<" ";
			 }
			 //based on previous word, select the next by determining
			//which occurs most often and output
			 for (int i = 0; i<length; i++) {
				word = greatest2(data.find(prev)->second);
				if (i==length-1) {
					cout<<word;
				} else {
					cout<<word<<" ";
				}
				prev = word;
			 }
			 cout<<endl<<endl;
		 }
	 }
	 } else if (window == 3) {
		 //check all input to make sure the words are in the text
		 bool badword = false;
		 for (unsigned int i =0; i<sentence.size(); i++) {
		 if (data3.find(sentence[i])==data3.end()) {
			 badword = true;
			 cout<<"The word "<<sentence[i]<<"does not appear in this text."<<endl;
		 }
		 }
		 if(!badword) {
		 if (random_flag){
			 //print given words and save out the last one, last two
			 //if two words given
			 prev = sentence[sentence.size()-1];
			 if (sentence.size() > int(1)) {
				prev2 = sentence[sentence.size()-2];
			 }
			 for (unsigned int j =0; j< sentence.size(); j++) {
				cout<<sentence[j]<<" ";
			 }
			 //based on previous words, select the next randomly
			 for (int i = 0; i<length; i++) {
				frame3::const_iterator temp;
				frame2::const_iterator itr;
				if (prev2!=".") {
					temp = data3.find(prev2);
					itr = temp->second.find(prev);
					word = random2(itr->second);
				 } else {
					//if only one word given, base calculation on only it
					temp = data3.find(prev);
					word = random3(temp->second);
				 }
				 if (i==length-1) {
					cout<<word;
				} else {
					cout<<word<<" ";
				}
				 prev2 = prev;
				 prev = word;
			 }
			 cout<<endl<<endl;
		 } else {
			 //print given words and save out the last one, last two
			 //if two words given
			 cout<<endl;
			 prev = sentence[sentence.size()-1];
			 if (sentence.size() > int(1)) {
				prev2 = sentence[sentence.size()-2];
			 }
			 for (unsigned int j =0; j< sentence.size(); j++) {
				cout<<sentence[j]<<" ";
			 }
			 //based on previous words, select the next by determining
			//which occurs most often and output
			 for (int i = 0; i<length; i++) {
				frame3::const_iterator temp;
				frame2::const_iterator itr;
				if (prev2!=".") {
					temp = data3.find(prev2);
					itr = temp->second.find(prev);
					word = greatest2(itr->second);
				 } else {
					 temp = data3.find(prev);
					word = greatest3(temp->second);
				 }
				 if (i==length-1) {
					cout<<word;
				} else {
					cout<<word<<" ";
				}
				 prev2 = prev;
				 prev = word;
			 }
			 cout<<endl;
		 }
	 }
	 }

    //exit program
    } else if (command == "quit") {
      break;
    } else {
      std::cout << "WARNING: Unknown command: " << command << std::endl;
    }
  }
}
