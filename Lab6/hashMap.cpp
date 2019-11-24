/*
 * hashMap.cpp
 *
 *  Created on: Nov 23, 2019
 *      Author: robertstahl
 */

#include "hashMap.hpp"
#include "hashNode.hpp"
#include <stdlib.h>
#include <math.h>
#include <string.h>

hashMap::hashMap(bool hash1,bool coll1){
	h1=hash1;
	c1=coll1;
	numKeys=0;
	mapSize=547;
	collisionct1=0;
	collisionct2=0;
	first="";
	map=new hashNode *[547];
	for(int i=0;i<547;i++){
		map[i]=NULL;
	}
}

/*First hash function. Takes first letter ASCII value and multiplies it by the sum of the ASCII
 * values of each character in the string. Then it takes the modulus by the mapSize.
 * This gets rid of the Anagram problem but other collisions will occur
 */
int hashMap::calcHash(string k){
	int x=0;
	int len=(int)strlen((char *)k);
	for(int i=0;i<len;i++){
		x+=k[i];
	}
	return (k[0]*x)%mapSize;
}

void hashMap::getClosestPrime(){
	int x=2*mapSize;
	bool y=true;
	for(int i=2;i<(int)sqrt(x);i++){
		if(x%i==0){
			y=false;
		}
	}
	while(y){
		x++;
		for(int i=2;i<(int)sqrt(x);i++){
				if(x%i==0){
					y=false;
				}
		}
	}
	mapSize=x;
}

//Handles collisions using quadratic probing. i should be incremented before passing in
int hashMap::collHash1(int h, int i){
	return (h+i*i)%mapSize;
}

int hashMap::findKey(string k){
	int x=calcHash(k);
	int y=x;
	if(map[x]->keyword==k){
		return x;
	}
	else{
		int i=1;
		while(map[x]->keyword!=k||i<collisionct2+1){
			x=collHash1(y,i);
			i++;
		}
		if(map[x]->keyword!=k){
			x=-1;
		}
	}
	return x;
}
