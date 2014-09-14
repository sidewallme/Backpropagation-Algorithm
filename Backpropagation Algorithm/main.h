//
//  main.h
//  test
//
//  Created by Eric on 7/23/14.
//  Copyright (c) 2014 Eric. All rights reserved.
//

#ifndef test_main_h
#define test_main_h
#include <math.h>
#include <string>
#include <vector>
#include "readfile.h"

const int input_number = 2;
const int hiddenUnits_number = 2;
const int output_number = 2;

struct hiddenUnit{
	double flow_in;
	double flow_out;
};

struct outputUnit{
	double flow_in;
	double output;
};

double outputfunction(double value){
	double result = 1 / (1 + exp(-value));
	return result;
}

int set_num = 100;

double dW[input_number][hiddenUnits_number] = {};
double dH[hiddenUnits_number][output_number] = {};

void iniToZeros(){
	for (int i = 0; i < input_number; i++){
		for (int j = 0; j < hiddenUnits_number; j++){
			dW[i][j] = 0;
		}
	}
	for (int i = 0; i < hiddenUnits_number; i++){
		for (int j = 0; j < output_number; j++){
			dH[i][j] = 0;
		}
	}
}
double inputToHidden_weights[input_number][hiddenUnits_number] = { -0.546476, -0.846758, -0.246337, 0.663024 };
double hiddenToOut_weights[hiddenUnits_number][output_number] = { -0.854197, -1.201315, -0.119869, -0.065294 };

std::vector<std::vector<double> >  dataset;
std::vector<std::vector<double> >  inputs;
std::vector<std::vector<double> >  targets;

vector<hiddenUnit>  hiddenLayer(hiddenUnits_number);
vector<outputUnit>  outputLayer(output_number);

void runOver(vector<double> inputing){
	for (int j = 0; j < hiddenUnits_number; j++){
		double flow_in=0.0;
		for (int i = 0; i < input_number; i++){
			flow_in += (inputing[i] * inputToHidden_weights[i][j]);
		}
		hiddenLayer[j].flow_in = flow_in;
		hiddenLayer[j].flow_out = outputfunction(flow_in);
	}

	for (int k = 0; k < output_number; k++){
		double flow_in=0.0;
		for (int j = 0; j < hiddenUnits_number; j++){
			flow_in += (hiddenLayer[j].flow_out * hiddenToOut_weights[j][k]);
		}
		outputLayer[k].flow_in = flow_in;
		outputLayer[k].output = outputfunction(flow_in);
	}
}

double sigma_out[output_number];
double sigma_w[hiddenUnits_number];
double rate = 0.5;

void BP(vector<double> inputing, vector<double> targeting){
	for (int k = 0; k < output_number; k++){
		sigma_out[k] = outputLayer[k].output * (1 - outputLayer[k].output)*(targeting[k] - outputLayer[k].output);
	}
	for (int j = 0; j < hiddenUnits_number; j++){
		double temp=0.0;
		for (int k = 0; k < output_number; k++){
			temp += hiddenToOut_weights[j][k] * sigma_out[k];
		}
		sigma_w[j] = hiddenLayer[j].flow_out * (1 - hiddenLayer[j].flow_out)*temp;
	}
	for (int j = 0; j < hiddenUnits_number; j++){
		for (int k = 0; k < output_number; k++){
			dH[j][k] += rate*sigma_out[k] * hiddenLayer[j].flow_out;
		}
	}

	for (int i = 0; i < input_number; i++){
		for (int j = 0; j < hiddenUnits_number; j++){
			dW[i][j] += rate*sigma_w[j] * inputing[i];
		}
	}
}

void updateWeights(){
	for (int i = 0; i < input_number; i++){
		for (int j = 0; j < hiddenUnits_number; j++){
			inputToHidden_weights[i][j]+=dW[i][j];
		}
	}
	for (int j = 0; j < hiddenUnits_number; j++){
		for (int k = 0; k < output_number; k++){
			hiddenToOut_weights[j][k] += dH[j][k];
		}
	}
}
void extractInputAndTargert(){

	for (int i = 0; i < set_num; i++){
		vector<double> row;
		row.push_back(1.0);
		for (int j = 0; j < input_number-1; j++){
			row.push_back(dataset[i][j]);
		}
		inputs.push_back(row);
	}
	
	for (int i = 0; i < set_num; i++){
		vector<double> row;
		for (int j = input_number-1; j < output_number+input_number-1; j++){
			row.push_back(dataset[i][j]);
		}
		targets.push_back(row);
	}
}

//void initialize(){
//	for (int i = 0; i < input_number; i++){
//		for (int j = 0; j < hiddenUnits_number; j++){
//			inputToHidden_weights[i][j] = ((double)rand() / (RAND_MAX));
//		}
//	}
//
//	for (int i = 0; i < hiddenUnits_number; i++){
//		for (int j = 0; j < output_number; j++){
//			hiddenToOut_weights[i][j] = ((double)rand() / (RAND_MAX));
//		}
//	}
//}



#endif