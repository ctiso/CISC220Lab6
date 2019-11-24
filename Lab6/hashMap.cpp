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
	int len=k.size();
	for(int i=0;i<len;i++){
		x+=k[i];
	}
	return (k[0]*x)%mapSize;
}

void hashMap::getClosestPrime(){
	int x=2*mapSize;
	bool y=false;
	for(int i=2;i<(int)sqrt(x);i++){
		if(x%i==0){
			y=true;
		}
	}
	while(y){
		x++;
		y=false;
		for(int i=2;i<(int)sqrt(x);i++){
				if(x%i==0){
					y=true;
				}
		}
	}
	mapSize=x;
}

//Handles collisions using quadratic probing. i should be incremented before passing in
int hashMap::collHash1(int h, int i){
	return ((h+i*i*i)%mapSize);
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

void hashMap::reHash(){
	cout<<numKeys<<endl;
	hashNode *x[numKeys];
	int j=0;
	int keyIdx;
	int coll=1;
	for(int i =0;i<mapSize;i++){
		if(map[i]!=NULL){
			x[j]=map[i];
			j++;
		}
	}
	getClosestPrime();
	delete map;
	map=new hashNode *[mapSize];
	int count=0;
	for(int i=0;i<mapSize;i++){
		map[i]=NULL;
	}
	for(int y=0;y<numKeys;y++){
		keyIdx=calcHash(x[y]->keyword);
		cout<<count<<endl;
		if(map[keyIdx]==NULL){
			map[keyIdx]=x[y];
		}
		else{
			collisionct1++;
			keyIdx=collHash1(keyIdx,coll);
			coll++;
			while(map[keyIdx]!=NULL){
				collisionct2++;
				keyIdx=collHash1(keyIdx,coll);
				coll++;
			}
			map[keyIdx]=x[y];
			coll=1;
		}
		count++;
	}
}

int hashMap::getIndex(string k){
	if(((double)numKeys)/((double)mapSize)>.7){
		cout<<"gotta rehash"<<endl;
		reHash();
	}
	int x=calcHash(k);
	int coll=1;
	int y=x;
	bool loop=map[x]!=NULL;
	while(loop){
		if(map[x]==NULL){
			loop=false;
		}
		else if(map[x]->keyword==k){
			loop=false;
		}
		else{
			if(coll==1){collisionct1++;}
			else{collisionct2++;}
			x=collHash1(y,coll);
			coll++;
		}
	}
	return x;
}

void hashMap::addKeyValue(string k, string v){
	int x=getIndex(k);
	if(map[x]==NULL){
		map[x]=new hashNode(k,v);
	}
	else{
		map[x]->addValue(v);
	}
	numKeys++;
}
