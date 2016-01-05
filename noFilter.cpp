#include "noFilter.h"

NoFilter::NoFilter(){

}
NoFilter::~NoFilter(){
	
}

bool NoFilter::lookUp(Hash hash){
	return bst.lookUp(hash);
}

void NoFilter::insert(Hash hash){
	bst.insert(hash);
}