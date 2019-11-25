/*
 * hashNode.cpp
 *
 *  Created on: Nov 20, 2019
 *      Author: robertstahl
 */

#include "hashNode.hpp"
#include <stdlib.h>

hashNode::hashNode(){
	keyword="";
	valuesSize=0;
	currSize=0;
	values=NULL;
}

hashNode::hashNode(string s){
	keyword=s;
	valuesSize=10;
	currSize=0;
	values=new string[valuesSize];
}

hashNode::hashNode(string s, string v){
	keyword=s;
	valuesSize=10;
	currSize=1;
	values=new string[valuesSize];
	values[0]=v;
}

void hashNode::dblArray(){
	string x[valuesSize];
	for(int i=0;i<valuesSize;i++){
		x[i]=values[i];
	}
	delete []values;
	values=new string[2*valuesSize];
	for(int i=0;i<valuesSize;i++){
		values[i]=x[i];
	}
	valuesSize*=2;
}

void hashNode::addValue(string v){
	currSize++;
	if(currSize>valuesSize){
		dblArray();
	}
	values[currSize-1]=v;
}

string hashNode::getRandValue(){
	cout<<"made rand"<<endl;
	string x;
	cout<<"initialized"<<endl;
	cout<<valuesSize<<endl;
	if(currSize==0){
		x="";
	}
	else{
		cout<<"made idx"<<endl;
		int idx=rand()%currSize;
		x=values[idx];
	}
	cout<<"skipped"<<endl;
	return x;
}
