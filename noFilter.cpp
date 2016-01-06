#include "noFilter.h"

NoFilter::NoFilter(){

}
NoFilter::~NoFilter(){
	
}

bool NoFilter::lookUp(Hash hash){
	return std::find(array.begin(), array.end(), hash) != array.end();
}

void NoFilter::insert(Hash hash){
	array.push_back(hash);
}