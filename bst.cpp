#include "bst.h"

BST::BST(uint64_t value){
	this->left = 0;
	this->right = 0;
	this->value = value;
}
BST::~BST(){
	if(this->left)
		delete this->left;
	if(this->right)
		delete this->right;
}

bool BST::lookUp(uint64_t hash){
	if(value == hash)
		return true;
	else {
		if(hash >= value){
			if(right == 0)
				return false;
			else
				right->lookUp(hash);
		}
		else if(hash < value){
			if(left == 0)
				return false;
			else
				left->lookUp(hash);
		}
	}
}

void BST::insert(uint64_t hash){
	if(hash >= value){
		if(right == 0)
			right = new BST(hash);
		else
			right->insert(hash);
	}
	else if(hash < value){
		if(left == 0)
			left = new BST(hash);
		else
			left->insert(hash);
	}
}