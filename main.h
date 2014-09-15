//  Copyright (c) 2014 Eric. All rights reserved.
//

#ifndef main_h
#define main_h

#include <vector>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>

#include "readfile.h"

//========USER DEFINED VAR AREA========//
const int input_number = 2/*CHANGE HERE*/;
const int hiddenUnits_number = 2/*CHANGE HERE*/;
const int output_number = 2/*CHANGE HERE*/;
int set_num = 100/*CHANGE HERE*/;
double rate = 0.5/*CHANGE HERE*/;
int iter_limit = 40/*CHANGE HERE*/;
//===============AREA END==============//

/*structure of hidden Unit*/
struct hiddenUnit{
	double flow_in;
	double flow_out;
};

/*structure of output Unit*/
struct outputUnit{
	double flow_in;
	double output;
};


/*the three datasets*/
std::vector<std::vector<double> >  dataset;
std::vector<std::vector<double> >  inputs;
std::vector<std::vector<double> >  targets;

/*declare the hiddenLayer and outputLayer*/
std::vector<hiddenUnit>  hiddenLayer(hiddenUnits_number);
std::vector<outputUnit>  outputLayer(output_number);

/*weights from input to hiddenLayer and hiddenLayer to outputLayer*/
double inputToHidden_weights[input_number][hiddenUnits_number] = {};
double hiddenToOut_weights[hiddenUnits_number][output_number] = {};

/*the change of each weight*/
double dW[input_number][hiddenUnits_number] = {};
double dH[hiddenUnits_number][output_number] = {};

/*error of each unit*/
double sigma_out[output_number];
double sigma_w[hiddenUnits_number];

/*structure of hidden Unit*/

/*output function :: sigmoid function*/
double outputfunction(double value);

/*initialize all the changes of weight (△weights) to zero*/
void iniToZeros();

/*run over the whole network to get value of each unit*/
void runOver(std::vector<double> inputing);

/*Back Propagation to calculate errors and updates*/
void BP(std::vector<double> inputing, std::vector<double> targeting);

/*Update each weight*/
void updateWeights();

/*extract input data and target data from the whole dataset*/
void extractInputAndTargert();

std::vector<std::vector<double>> t_inputs;


/**
* To imporve the performance of BP, I adopted the SCAWI initialization method;
* For more information, please refer to http://bit.ly/1qCQYII

*Statistically controlled activation weight initialization(SCAWI).
*By: Gian Paolo Drago, Sandro Ridella
*In : IEEE Transactions on Neural Networks, 1992
*/

//=============main function=============//
void iniWeightsBySCAWI();
//=============sub functions=============//
//	transpose the 2d vector
void transpose();

//	calculate the average value of a vector;
double calculate_avg(std::vector<double> in);

//	calculate the variance value of a vector;
double calculate_var(std::vector<double> in, double avg);

//	generate a uniformly distributed real number between -1 and 1;
double uniform_dist_rand_generator();
//=================ENDING================//

#endif