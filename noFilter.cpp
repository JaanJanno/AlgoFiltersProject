#include "noFilter.h"

NoFilter::NoFilter(){

}
NoFilter::~NoFilter(){
	
}

bool NoFilter::lookUp(Hash hash){
	if(std::find(array.begin(), array.end(), hash) != array.end()) {
		return true;
	}
	return false;
}

void NoFilter::insert(Hash hash){
	array.push_back(hash);
}