#include <fstream>
#include <iostream>
#include <string>
#include "SongLibrary.h"

//////////////////DO NOT CHANGE THIS CODE////////////////////////

//Construct a Song object with values
Song::Song(const std::string& title, const std::string& artist, 
     const std::string& album, unsigned int year){
	this->title = title;
	this->artist = artist;
	this->album = album;
	this->year = year;
	used = false;
	this->song_group_ptr = NULL;
}

//Song equality doesn't depend on pointers or being used
bool operator== (const Song& s1, const Song& s2){
	return (s1.getYear() == s2.getYear()) && (s1.getTitle() == s2.getTitle())
          && (s1.getAlbum() == s2.getAlbum()) && (s1.getArtist() == s2.getArtist());
}

//Modifier for group pointer
void Song::updateSongGroupPointer(SongGroupNode* ptr){
	if(ptr){
		//Check that ptr is actually for this Song.
		assert(ptr->m_song->value == *this); 
		song_group_ptr = ptr;
	}
	else{
		song_group_ptr = NULL;
	}
}

//Make output easier by overload operator<<
std::ostream& operator<< (std::ostream& ostr, const Song& song){
	if(!song.getSongGroupPointer()){
		ostr << "\"" << song.getTitle() << "\" by " << song.getArtist() << " on \"" 
	       << song.getAlbum() << "\" (" << song.getYear() << ")" << std::endl;
	}
	else{
		ostr << "\"" << song.getTitle() << "\" by " << song.getArtist() << " on \"" 
		<< song.getAlbum() << "\" (" << song.getYear() << ")" << " in Song Group "
		<< song.getSongGroupPointer()->id << std::endl;
	}
	return ostr;
}

/////////////////////////YOUR CODE STARTS HERE/////////////////////////////////


//////////////////////////////GROUP FUNCTIONS/////////////////////////////////

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-id is the ID of the list we are searching for
BEHAVIOR:
None
RETURN:
NULL if no list matches the ID, otherwise returns the GroupListNode* containing
the head of the list with ID id.
*/
GroupListNode* GroupExists(GroupListNode* song_groups, GroupID id){
	GroupListNode* temp = song_groups;
	while(temp!=NULL) {
		if(temp->value->id == id) {
			return temp;
		}
		temp = temp->ptr;
	}
	return NULL;
}

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-id is the ID of the list we are creating
BEHAVIOR:
Add a new song group to song_groups, give the new song group ID id. Order of
song groups is not guaranteed.
RETURN:
None
*/
void MakeGroup(GroupListNode*& song_groups, GroupID id){
	GroupListNode* temp = song_groups;
	GroupListNode* item = new GroupListNode;
	item->ptr = NULL;
	item->value = new SongGroupNode;
	item->value->next_song_ptr = NULL;
	item->value->prev_song_ptr = NULL;
	item->value->next_by_artist_ptr=NULL;
	item->value->prev_by_year_ptr=NULL;
	item->value->m_song = NULL;
	item->value->id = id;
	if (song_groups == NULL) {
		song_groups = item;
	} else {
		item->ptr = temp;
		song_groups = item;
	}
}


/*
ARGUMENTS:
-group_head points to the head of a song group
-song is the Song we are checking the group for
BEHAVIOR:
None
RETURN:
If song is found in the group return true. If song is not found,
return false.
*/
bool SongInGroup(SongGroupNode* group_head, const Song& song){
	SongGroupNode* temp = group_head;
		while(temp!=NULL) {
		if (song.getSongGroupPointer() == temp) {
			return true;
		}
		temp = temp->next_song_ptr;
	}
	return false;
}

/*
ARGUMENTS:
-library_ptr points to the LibraryNode* containing the Song we want to add.
-list_ptr is the head of the song group we want to add the song to.
BEHAVIOR:
Modify the group pointed to by list_ptr to reflect that the song is in the group.
This may change the length of the list. Modifies the Song's members as well.
RETURN:
None
*/
void AddToGroup(LibraryNode* library_ptr, GroupListNode* list_ptr){
	SongGroupNode* temp = list_ptr->value;
	
	if(temp->next_song_ptr==NULL&&temp->m_song==NULL) {
		temp->m_song = library_ptr;
		temp->m_song->value.setUsedInGroup(true);
		temp->m_song->value.updateSongGroupPointer(temp);
	} else {
	while(temp->next_song_ptr!=NULL) {
		temp = temp->next_song_ptr;
	}
	SongGroupNode* item = new SongGroupNode;
	item->next_song_ptr = NULL;
	item->prev_song_ptr = NULL;
	item->next_by_artist_ptr=NULL;
	item->prev_by_year_ptr=NULL;
	item->m_song = library_ptr;
	item->m_song->value.setUsedInGroup(true);
	item->id = list_ptr->value->id;
	
	temp->next_song_ptr = item;
	item->prev_song_ptr = temp;
	item->m_song->value.updateSongGroupPointer(item);
	}
}

/*
ARGUMENTS:
-library_ptr points to the LibraryNode* containing the Song we want to remove from a group.
-song_groups points to a singly-linked list of song group heads
BEHAVIOR:
Modifies the Song's member variables to reflect that it is not in a group. Modifies the group
so that the Song is not in the group. This function may cause song_groups to be modified as well.
RETURN:
None
*/
void RemoveFromGroup(LibraryNode* library_ptr, GroupListNode* song_groups){
	SongGroupNode* target = library_ptr->value.getSongGroupPointer();
	GroupID targ = target->id;
	GroupListNode* temp = song_groups;
	while(temp!=NULL) {
		if(temp->value->id==targ) {
			SongGroupNode* current = temp->value;
			SongGroupNode* prev;
			if (current->m_song==library_ptr&&current->next_song_ptr==NULL) {
				//if only one item in list
				current->m_song=NULL; 
				break;
			}else if(current->m_song==library_ptr) {
				//if item is first in list
				temp->value = current->next_song_ptr;
				delete current;
				break;
			}else{
			while(current!=NULL) {
				prev = current->prev_song_ptr;
				if (current->m_song==library_ptr) {
					SongGroupNode* next = current->next_by_artist_ptr;
					if (prev!=NULL) {
						prev->next_song_ptr = next;
					}
					if(next!=NULL){
						next->prev_song_ptr=prev;
					}
					delete current;
					current = next;
				} else {
				current = current->next_song_ptr;
			}
			}
			}
		library_ptr->value.setUsedInGroup(false);
		library_ptr->value.updateSongGroupPointer(NULL);
		}
		temp = temp->ptr;
	}
}
/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-list_ptr1 contains to the song group head of Group A
-list_ptr2 contains the song group head of Group B
BEHAVIOR:
Modify Group A so that at the end of its songs, the songs of Group B are added in the same
order they were found in Group B. Remove the now-empty Group B.
RETURN:
None
*/
void CombineGroups(GroupListNode*& song_groups, GroupListNode*& list_ptr1, GroupListNode*& list_ptr2){
	if (list_ptr2->value->m_song==NULL) {
		delete list_ptr2->value;
	} else {
		SongGroupNode* temp2 = list_ptr2->value;
		while(temp2!=NULL) {
			temp2->id = list_ptr1->value->id;
			temp2 = temp2->next_song_ptr;
		}
		if(list_ptr1->value->m_song==NULL) {
			delete list_ptr1->value;
			list_ptr1->value = list_ptr2->value;
		} else {
			SongGroupNode* temp = list_ptr1->value;
			while(temp->next_song_ptr!=NULL){
				temp= temp->next_song_ptr;
			}
			temp->next_song_ptr=list_ptr2->value;
			list_ptr2->value->prev_song_ptr = temp;
		}
	}
	GroupListNode* current = song_groups;
	GroupListNode* next;
	if(current == list_ptr2) { //if merged is first
		next = current->ptr;
		delete current;
		song_groups = next;
	} else {
		while(current!=NULL) {
			next = current->ptr;
			if(next == list_ptr2) {
				if (next->ptr==NULL) {
					current->ptr=NULL; //if merged is last
					delete next;
					next = NULL;
					break;
				} else {
					current->ptr = next->ptr;
					delete next;
					next = current->ptr;
					break;
				}
			}
			current = next;
		}//special cases to consider: first, middle, last
	}
}

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-library_ptr points to the LibraryNode* containing the Song we want to remove from a group.
BEHAVIOR:
Remove the group from the list of song groups. No Song objects should remain associated with the
group, and the function should modify Song member variables appropriately to reflect this. Any
memory associated with the group must be released.
RETURN:
None
*/
void RemoveGroup(GroupListNode*& song_groups, GroupListNode* list_ptr){
	SongGroupNode* current2 = list_ptr->value;
	SongGroupNode* next2;
	while(current2!=NULL) {
		next2 = current2->next_song_ptr;
		if (current2->m_song!=NULL) {
		current2->m_song->value.setUsedInGroup(false);
		current2->m_song->value.updateSongGroupPointer(NULL);
		}
		delete current2;
		current2 = next2;
	}
	GroupListNode* current = song_groups;
	GroupListNode* next;
	//if group to be removed is the only one in the list
	if (current==list_ptr&&current->ptr==NULL) {
		delete current;
		song_groups = NULL;
	//if group to be deleted is first but NOT ONLY
	} else if (current==list_ptr) {
		next = current->ptr;
		delete current;
		song_groups = next;
	} else {
	while(current!=NULL) {
		next = current->ptr;
		if(next == list_ptr) {
			current->ptr = next->ptr;
			delete next;
			next = current->ptr;
		}
		current = next;
	}
	}
}//special cases : one or last

/*
ARGUMENTS:
-list_ptr is the head of the song group we want to add the song to.
BEHAVIOR:
Recompute all prev_by_year_ptr members in the song group pointed to by
list_ptr.
RETURN:
None
*/
void RecomputePrevByYear(GroupListNode* list_ptr){
	SongGroupNode* current = list_ptr->value;
	SongGroupNode* tail;
	while(current->next_song_ptr!=NULL) {
		current = current->next_song_ptr;
	}
	while(current!=NULL) {
		tail = current;
		while(tail!=NULL) {
			if ((current->m_song->value.getYear()>tail->m_song->value.getYear())&&
				current!=tail){
				current->prev_by_year_ptr = tail;
				break;
			}
			tail = tail->prev_song_ptr;
		}
	current = current->prev_song_ptr;
	}
}

////////////////////////////PRINT FUNCTIONS////////////////////////////////////

/*
ARGUMENTS:
-library_head points to the first LibraryNode* of the song library
-print_file points to an ostream to print output to
BEHAVIOR:
Print each song in the library in the order it was added.
RETURN:
None
*/
void PrintLibrary(LibraryNode* library_head,std::ostream& print_file){
	LibraryNode* temp = library_head;
	int count = 0;
	while(temp!=NULL) {
		print_file<<temp->value;
		temp = temp->ptr;
		count++;
	}
	print_file<<"Library contains "<<count<<" song(s)"<<std::endl;
}

/*
ARGUMENTS:
-group_head points to the first SongGroupNode* of the group to print
-print_file points to an ostream to print output to
BEHAVIOR:
Print each song in the group in the order it was added.
RETURN:
None
*/
void PrintGroupSequential(SongGroupNode* group_head,std::ostream& print_file){
	SongGroupNode* temp = group_head;
	int count = 0;
	print_file<<"List ID "<<temp->id<<" contains:"<<std::endl;
	if(temp->m_song!=NULL){
	while(temp!=NULL) {
		print_file<<"\""<<temp->m_song->value.getTitle()<<"\" by "<<temp->m_song->value.getArtist();
		print_file<<" on \""<<temp->m_song->value.getAlbum()<<"\" ("<<temp->m_song->value.getYear();
		print_file<<") in Song Group "<<temp->id<<std::endl;
		temp = temp->next_song_ptr;
		count++;
	}
	}
	print_file<<count<<" song(s)"<<std::endl;
}

/*
ARGUMENTS:
-group_ptr points to the location in a particular song group to start printing from
-print_file points to an ostream to print output to
BEHAVIOR:
Print a rewind list by following the prev_by_year_ptr pointers, starting from the song
pointed to by group_ptr.
RETURN:
None
*/
void PrintGroupRewind(SongGroupNode* group_ptr,std::ostream& print_file){
	SongGroupNode* current = group_ptr;
	SongGroupNode* tail;
	while(current->next_song_ptr!=NULL) {
		current = current->next_song_ptr;
	}
	while(current!=NULL) {
		tail = current;
		while(tail!=NULL) {
			if ((current->m_song->value.getYear()>tail->m_song->value.getYear())&&
				current!=tail){
				current->prev_by_year_ptr = tail;
				break;
			}
			tail = tail->prev_song_ptr;
		}
	current = current->prev_song_ptr;
	}
	SongGroupNode* temp = group_ptr;
	print_file<<"Rewind list for "<<temp->m_song->value.getYear()<<std::endl;
	int count = 0;
	if(temp->m_song!=NULL){
	while(temp!=NULL) {
		count++;
		print_file<<"\t#"<<count<<": \""<<temp->m_song->value.getTitle()<<"\" by "
		<<temp->m_song->value.getArtist()<<" on \""<<temp->m_song->value.getAlbum()<<"\" ("
		<<temp->m_song->value.getYear()<<") in Song Group "<<temp->id<<std::endl;
		temp = temp->prev_by_year_ptr;
	}
	}
print_file<<"Rewind list contained "<<count<<" song(s)."<<std::endl;
}

/*
ARGUMENTS:
-group_ptr points to the location in a particular song group to start printing from
-print_file points to an ostream to print output to
BEHAVIOR:
Print a rewind list by following the next_by_artist_ptr pointers, starting from the song
pointed to by group_ptr.
RETURN:
None
*/
void PrintGroupMarathon(SongGroupNode* group_ptr,std::ostream& print_file){
	SongGroupNode* current = group_ptr;
	SongGroupNode* tail;
	while(current->next_song_ptr!=NULL) {
		tail = current;
		while(tail!=NULL) {
			if((current->m_song->value.getAlbum())==(tail->m_song->value.getAlbum())
				&&current!=tail) {
				current->next_by_artist_ptr=tail;
				break;
			}
			tail =  tail->next_song_ptr;
		}
		current = current->next_song_ptr;
	}
	//RecomputePrevByYear(group_ptr);
	SongGroupNode* temp = group_ptr;
	int count = 0;
	print_file<<"Marathon list for "<<temp->m_song->value.getArtist()<<std::endl;
	if(temp->m_song!=NULL){
	while(temp!=NULL) {
		count++;
		print_file<<"\t#"<<count<<": \""<<temp->m_song->value.getTitle()<<"\" by "
		<<temp->m_song->value.getArtist()<<" on \""<<temp->m_song->value.getAlbum()<<"\" ("
		<<temp->m_song->value.getYear()<<") in Song Group "<<temp->id<<std::endl;
		temp = temp->next_by_artist_ptr;
	}
	}
	print_file<<"Marathon list contained "<<count<<" song(s)."<<std::endl;
}

/*
ARGUMENTS:
-group_head points to the first SongGroupNode* of the group to analyze
-print_file points to an ostream to print output to
BEHAVIOR:
Find the rewind list with the most songs in the song group pointed to by group_head.
Print the rewind list and the song count to print_file.
RETURN:
None
*/
void PrintLongestGroupRewind(GroupListNode* group_head,std::ostream& print_file){
	RecomputePrevByYear(group_head);
	SongGroupNode* temp = group_head->value;
	int count = 0;
	print_file<<"Maximum size rewind list is for year "<<temp->m_song->value.getYear()
	<<std::endl;
	if(temp->m_song!=NULL){
		while(temp!=NULL) {
		count++;
		print_file<<"\t#"<<count<<": \""<<temp->m_song->value.getTitle()<<"\" by "
		<<temp->m_song->value.getArtist()<<" on \""<<temp->m_song->value.getAlbum()<<"\" ("
		<<temp->m_song->value.getYear()<<") in Song Group "<<temp->id<<std::endl;
		temp = temp->prev_by_year_ptr;
	}
}
print_file<<"Longest rewind list contained "<<count<<" song(s)."<<std::endl;
}

///////////////////////////////CLEANUP/////////////////////////////////////////

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
BEHAVIOR:
Delete every group. Do not leak. Modifies all groups and the song_groups list.
Update every Song to reflect not being in a group.
RETURN:
None
*/
void DeleteAllSongGroups(GroupListNode*& song_groups){
	GroupListNode* current = song_groups;
	GroupListNode* next;
	while (current!=NULL) {
		next = current->ptr;
		SongGroupNode* current2 = current->value;
		SongGroupNode* next2;
		while(current2!=NULL) {
			next2 = current2->next_song_ptr;
			delete current2;
			current2 = next2;
		}
		delete current;
		current = next;
	}
}