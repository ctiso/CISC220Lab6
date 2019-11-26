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
	mapSize=251;
	collisionct1=0;
	collisionct2=0;
	first="";
	map=new hashNode *[mapSize];
	for(int i=0;i<mapSize;i++){
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

//Squares the string length, then multiplies by the counts of vowels and consonants. Then subtracts the amount of consoanants and then adds the number of vowels
int hashMap::calcHash2(string k){
	int len=k.size()*k.size();
	int x=k.size();
	int vCount=0;
	int cCount=0;
	for(int i=0;i<x;i++){
		if(k[i]=='A'||k[i]=='a'||k[i]=='e'||k[i]=='E'||k[i]=='i'||k[i]=='I'||k[i]=='o'||k[i]=='u'||k[i]=='O'||k[i]=='u'||k[i]=='y'||k[i]=='Y'){
			vCount++;
		}
		else{
			cCount++;
		}
	}
	len=len*cCount/vCount;
	len=len-cCount+vCount;
	return len%mapSize;
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
//Linear probing
int hashMap::collHash2(int h){
	while(map[h]!=NULL){
		h++;
	}
	return h;
}
int hashMap::findKey(string k){
	int x;
	if(h1==true){
		x=calcHash(k);
	}
	else if(h1==false){
		x=calcHash2(k);
	}
	int y=x;
	if(map[x]->keyword==k){
		return x;
	}
	else{
		int i=1;
		while(map[x]->keyword!=k||i<collisionct2+1){
			if(c1==true){
				x=collHash1(y,i);
			}
			else if(c1==false){
				x=collHash2(y);
			}
			i++;
		}
		if(map[x]->keyword!=k){
			x=-1;
		}
	}
	return x;
}

void hashMap::reHash(){
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
	delete []map;
	map=new hashNode *[mapSize];
	for(int i=0;i<mapSize;i++){
		map[i]=NULL;
	}
	for(int y=0;y<numKeys;y++){
		if(h1==true){
			keyIdx=calcHash(x[y]->keyword);
		}
		else if(h1==false){
			keyIdx=calcHash2(x[y]->keyword);
		}
		else if(map[keyIdx]==NULL){
			map[keyIdx]=x[y];
		}
		else{
			collisionct1++;
			if(c1==true){
				keyIdx=collHash1(keyIdx,coll);
			}
			else if(c1==false){
				keyIdx=collHash2(keyIdx);
			}
			coll++;
			while(map[keyIdx]!=NULL){
				collisionct2++;
				if(c1==true){
					keyIdx=collHash1(keyIdx,coll);
				}
				else if(c1==false){
					keyIdx=collHash2(keyIdx);
				}
				coll++;
			}
			map[keyIdx]=x[y];
			coll=1;
		}
	}
}

int hashMap::getIndex(string k){
	if(((double)numKeys)/((double)mapSize)>.7){
		reHash();
	}
	int x;
	if(h1==true){
		x=calcHash(k);
	}
	else if(h1==false){
		x=calcHash2(k);
	}
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
			if(coll==1){
				collisionct1++;
			}
			else{
				collisionct2++;
			}
			if(c1 ==true){
			x=collHash1(y,coll);
			}
			else if(c1==false){
				x=collHash2(y);
			}
			coll++;
		}
	}
	return x;
}

void hashMap::addKeyValue(string k, string v){
	int x=getIndex(k);
	if(map[x]==NULL){
		map[x]=new hashNode(k,v);
		numKeys++;
	}
	else{
		map[x]->addValue(v);
	}
}
