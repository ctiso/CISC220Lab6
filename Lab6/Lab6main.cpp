/*
 * Lab6main.cpp
 *
 *  Created on: Nov 24, 2019
 *      Author: robertstahl
 */
#include "makeSeuss.hpp"
#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <string>
#include <fstream>


using namespace std;

int main(){
	srand(5);
	makeSeuss c1h1=makeSeuss("DrSeuss.txt","c1h1",true,true);
	makeSeuss c2h2=makeSeuss("DrSeuss.txt","c2h2",true,true);
	makeSeuss c2h1=makeSeuss("DrSeuss.txt","c1h1",true,true);
	makeSeuss c1h2=makeSeuss("DrSeuss.txt","c1h1",true,true);
	return 0;
}

