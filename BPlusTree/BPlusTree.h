/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/
#include <utility>
#include <list>
#include <vector>
#include <algorithm>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE
using namespace std;
///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////
template <class T> class BPlusTree;

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only, this is actually bad to have because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////
template <class T> class BPlusTree {
	
	public:
	BPlusTree(const int& b);
	BPlusTree(const BPlusTree<T>& old);
	~BPlusTree(){this->destroy(root_);}
	
	BPlusTree<T>* operator=(const BPlusTree<T>& old);
	bool operator==(const BPlusTree<T>& old) const { return (old.root_ == this->root_); }
	bool operator!=(const BPlusTree<T>& old) const { return (old.root_ != this->root_); }
	
	BPlusTreeNode<T>* find(const T& key);
	void insert(const T& key);
	void print_sideways(ostream& outfile);
	void print_BFS(ostream& outfile);
	void print_BFS_pretty(ostream& outfile);
	
	private:
	BPlusTreeNode<T>* root_;
	unsigned int bvalue;
	void copytree(BPlusTreeNode<T>* root,BPlusTreeNode<T>* parent,BPlusTreeNode<T>* &newnode);
	void destroy(BPlusTreeNode<T>* root);
	BPlusTreeNode<T>* locate(const T& key,BPlusTreeNode<T>* root);
	BPlusTreeNode<T>* locateins(const T& key,BPlusTreeNode<T>* root);
	void split(BPlusTreeNode<T>* node);
	void sideways(ostream& ostr, int depth, BPlusTreeNode<T>* node);
};
template <class T> BPlusTree<T>::BPlusTree(const int& b){
	bvalue = b;
	root_ = NULL;
}
template <class T> BPlusTree<T>::BPlusTree(const BPlusTree<T>& old){
	this->bvalue = old.bvalue;
	BPlusTreeNode<T>* newnode;
	copytree(old.root_,NULL,newnode);
	this->root_=newnode;
}
template <class T> BPlusTree<T>* BPlusTree<T>::operator=(const BPlusTree<T>& old) {
	if (&old!=this) {
	this->destroy(root_);
	this->bvalue = old.bvalue;
	BPlusTreeNode<T>* newnode;
	copytree(old.root_,NULL,newnode);
	this->root_=newnode;
	}
	return this;
}
template <class T> BPlusTreeNode<T>* BPlusTree<T>::locateins(const T& key,BPlusTreeNode<T>* root){
	if (root->is_leaf()) {
		return root;
	}
	if (key<root->keys[0]) {
		return locateins(key,root->children[0]);
	}
	for(unsigned int i=0; i<(root->keys.size()-1);i++) {
		if(key>=root->keys[i]&&key<root->keys[i+1]) {
			return locateins(key,root->children[i]);
		}
	}
	return locateins(key,root->children[root->keys.size()]);
}
template <class T> BPlusTreeNode<T>* BPlusTree<T>::locate(const T& key,BPlusTreeNode<T>* root){
	if (root->is_leaf()) {
		return root;
	}
	if (key<root->keys[0]) {
		return locate(key,root->children[0]);
	}
	for(unsigned int i=0; i<(root->keys.size()-1);i++) {
		if(root->keys[i]==key) {
			return root;
		}
		if(key>=root->keys[i]&&key<root->keys[i+1]) {
			return locate(key,root->children[i]);
		}
	}
	if(root->keys[root->keys.size()-1]==key) {
			return root;
		}
	return locate(key,root->children[root->keys.size()]);
}
template <class T> BPlusTreeNode<T>* BPlusTree<T>::find(const T& key){
	if (root_==NULL) {
		return NULL;
	}
	return locate(key,root_);
}
template <class T> void BPlusTree<T>::split(BPlusTreeNode<T>* node){
	BPlusTreeNode<T>* new1, *new2;
	T mid;
	if (node==NULL) {return;}
	if (node->keys.size()<bvalue) {return;}
	sort(node->keys.begin(),node->keys.end());
	vector<T> saves = node->keys;
	mid = saves[(saves.size()/2)+1];
	unsigned int midval = (saves.size()/2)+1;
	if (node->parent) {
		node->keys.clear();
		new1 = new BPlusTreeNode<T>;
		new1->parent = node->parent;
		for(unsigned int i = 0;i<midval;i++) {
			node->keys.push_back(saves[i]);
		}
		for(unsigned int i = midval;i<saves.size() ;i++) {
			new1->keys.push_back(saves[i]);
		}
		node->parent->children.push_back(new1);
		node->parent->keys.push_back(mid);
		if (new1->parent->keys.size()>(bvalue-1)) {
			split(new1->parent);
		}
	} else if(node->is_leaf()){
		new1 = new BPlusTreeNode<T>;
		new2 = new BPlusTreeNode<T>;
		new1->parent = node;
		new2->parent = node;
		node->children.push_back(new1);
		node->children.push_back(new2);
		node->keys.clear();
		node->keys.push_back(mid);
		for(unsigned int i = 0;i<midval;i++) {
			new1->keys.push_back(saves[i]);
		}
		for(unsigned int i = midval;i<saves.size() ;i++) {
			new2->keys.push_back(saves[i]);
		}
	}
}
template <class T> void BPlusTree<T>::insert(const T& key) {
	BPlusTreeNode<T>* temp;
	bool notinkeys = true;
	if (root_==NULL) {
		root_= new BPlusTreeNode<T>;
		root_->parent = NULL;
		root_->keys.push_back(key);
		return;
	} else {
		temp = locateins(key,root_);
		typename vector<T>::iterator itr;
		for (itr=temp->keys.begin();itr<temp->keys.end();itr++) {
			if(key < *itr) {
				notinkeys = false;
				temp->keys.insert(itr,key);
				break;
			}
		}
		if (notinkeys) {
			temp->keys.push_back(key);
		}
		if(temp->keys.size()>bvalue-1){
			split(temp);
		}
	}
}

template <class T> void BPlusTree<T>::print_sideways(ostream& outfile){
	if (root_==NULL) {
		outfile<<"Tree is empty."<<endl;
		return;
	}
	sideways(outfile,0,root_);
	outfile<<endl;
}
template <class T> 
void BPlusTree<T>::sideways(ostream& ostr, int depth, BPlusTreeNode<T>* node) {
	if(node->is_leaf()) {
		for (int k=0; k<depth; ++k) ostr << "\t";
		for (unsigned int k=0; k<node->keys.size()-1; ++k)
			ostr << node->keys[k]<<", ";
		ostr<<node->keys[node->keys.size()-1]<<endl;
	} else {
	for(unsigned int i=0;i<node->children.size();i++) {
		if(node->children[i]->keys[0]<node->keys[0]) {
			sideways(ostr,depth+1,node->children[i]);
	}}
	for (int k=0; k<depth; ++k) ostr << "\t";
	for (unsigned int k=0; k<node->keys.size()-1; ++k)
		ostr << node->keys[k]<<",";
	ostr<<node->keys[node->keys.size()-1]<<endl;
	for(unsigned int i=0;i<node->children.size();i++) {
		if (node->children[i]->keys[0]>=node->keys[0]) {
			sideways(ostr,depth+1,node->children[i]);
		}
	}
	}
}
template <class T> void BPlusTree<T>::print_BFS(ostream& outfile){
	if (root_==NULL) {
		outfile<<"Tree is empty."<<endl;
		return;
	}
	list<BPlusTreeNode<T>* > toPrint;
	toPrint.push_back(root_);
	typename list<BPlusTreeNode<T>* >::iterator temp = toPrint.begin();
	BPlusTreeNode<T>* parent = (*temp)->parent;
	for (unsigned int i=0;i<(*temp)->children.size();i++) {
		toPrint.push_back((*temp)->children[i]);
	}
	for(temp=toPrint.begin();temp!=toPrint.end();temp++) {
		if (parent == (*temp)->parent) {
			for (unsigned int k=0; k<(*temp)->keys.size()-1; ++k)
			outfile << (*temp)->keys[k]<<",";
			outfile<<(*temp)->keys[(*temp)->keys.size()-1]<<" ";
		}
		if (parent != (*temp)->parent) {
			outfile<<endl;
			parent = (*temp)->parent;
		}
	}
	outfile<<endl;
}
template <class T> void BPlusTree<T>::print_BFS_pretty(ostream& outfile) {
	if (root_==NULL) {
		outfile<<"Tree is empty."<<endl;
		return;
	}
}

template <class T> void BPlusTree<T>::copytree(BPlusTreeNode<T>* root,BPlusTreeNode<T>* parent,BPlusTreeNode<T>* &newnode){
	if (root==NULL) {
		newnode = NULL;
		return;
	}
	
	newnode = new BPlusTreeNode<T>;
	newnode->parent = parent;
	newnode->keys=vector<T>(root->keys);
	
	for(unsigned int i=0;i<root->children.size();i++) {
		newnode->children.push_back(NULL);
		copytree(root->children[i],newnode,newnode->children[i]);
	}
	
}
template <class T> void BPlusTree<T>::destroy(BPlusTreeNode<T>* root) {
	if (root==NULL) {return;}
	for(unsigned int i=0;i<root->children.size();i++) {
		destroy(root->children[i]);
	}
	delete root;
}

#endif
