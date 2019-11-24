/*
 * hashMap.cpp
 *
 *  Created on: Nov 23, 2019
 *      Author: robertstahl
 */

#include "hashMap.hpp"
#include "hashNode.hpp"
#include <stdlib.h>

hashMap::hashMap(bool hash1,bool coll1){
	h1=hash1;
	c1=coll1;
	numKeys=0;
	mapSize=547;
	collisionct1=0;
	collisionct2=0;
	first="";
}


