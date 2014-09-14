//  Created by Jiarui Xu on 7/23/14.
//  Copyright (c) 2014 Jiarui Xu. All rights reserved.
//


#include <iostream>
#include <sstream>
#include <fstream>
#include "main.h"
#include <math.h>
#include <cstdlib>
#include <stdio.h>
#include "readfile.h"
#include <string>

using namespace std;

int main(int argc, const char * argv[])
{
	if (argc != 2){
		cout << "Usage: [FILEPATH] [LEARNING_RATE]" << endl;
	}

	if (!read(dataset, argv[1])){
		cout << "Can't open the file. Please enter a valid file path." << endl;//
		system("PAUSE");
		return 1;
	}
	extractInputAndTargert();
	for (int j = 0; j < 40; j++){
		iniToZeros();
		for (int i = 0; i < set_num; i++){
			vector<double> targeting = targets[i];
			vector<double> inputing = inputs[i];
			runOver(inputing);
			BP(inputing, targeting);
			
		}	
		updateWeights();
	}

	cout << hiddenToOut_weights[0][0] << endl;
	cout << "Name: Jiarui Xu; No. 20235857;" << endl;
	cout << "press something to continue...";
	getchar();//for viewing, pause;
	return 0;
}