

#include "neuralNet.h"


#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>


using namespace std;

int main()
{
	srand(124242334);

	vector<unsigned> topology(5);
	topology[0] = 1;
	topology[1] = 15;
	topology[2] = 15;
	topology[3] = 15;
	topology[4] = 2;
	NeuralNet net(topology);
	NeuralNet net2(topology);	

	vector<double> input(1);
	vector<double> target(1);
	vector<double> output(2);

	int N = 10;

	vector<vector<double> > inputTrain(N,vector<double>(1));
	vector<vector<double> > targetTrain(N,vector<double>(2));
	vector<double> errorTrain;
	vector<vector<double> > inputTest(N,vector<double>(1));
	vector<vector<double> > targetTest(N,vector<double>(2));
	vector<double> errorTest;

	//training data
	for(int i =0;i<N;++i){
		inputTest[i][0] = 4*(1-2*( (double)rand()/(double)RAND_MAX));
		targetTest[i][0] = sin(inputTest[i][0]);
		targetTest[i][1] = cos(inputTest[i][0]);
		inputTrain[i][0] = 4*(1-2*( (double)rand()/(double)RAND_MAX));
		targetTrain[i][0] = sin(inputTrain[i][0]);
		targetTrain[i][1] = cos(inputTrain[i][0]);
	}
	double eta = 0.1;
	double eTest = 0.;
	double eTrain = 0.;
	for(int i=0;i<2000;++i) {
		eTrain = 0.;
		eTest = 0.;
		for(int j=0;j<N;++j) {
			net.forwardProp(inputTrain[j]);
			eTrain += net.errorFunc(targetTrain[j]);
			net.forwardProp(inputTest[j]);
			eTest += net.errorFunc(targetTest[j]);
		}
		errorTrain.push_back(eTrain/N);
		errorTest.push_back(eTest/N);

		for(int j=0;j<N;++j) {
			int k = rand()%N;
			net.forwardProp(inputTrain[k]);
			net.backProp(targetTrain[k],eta);
		}
		if(i == 1000) eta = 0.01;
	}

	ofstream outTrain("errorTrain.dat");
	ofstream outTest("errorTest.dat");
	for(unsigned i=0;i<errorTrain.size();++i) {

		outTrain << errorTrain[i] << '\n';
		outTest << errorTest[i] << '\n';
	}
	ofstream outX("xtrain.dat");
	ofstream outYs("ytrains.dat");
	ofstream outYc("ytrainc.dat");
	ofstream outXtest("xtest.dat");
	ofstream outYtests("ytests.dat");
	ofstream outYtestc("ytestc.dat");
	for(int i =0;i<N;++i){
		net.forwardProp(inputTrain[i]);
		output = net.getOutput();

		outX << inputTrain[i][0] << '\n';
		outYs << output[0] << '\n';
		outYc << output[1] << '\n';
		net.forwardProp(inputTest[i]);
		output = net.getOutput();
		outXtest << inputTest[i][0] << '\n';
		outYtests << output[0] << '\n';
		outYtestc << output[1] << '\n';

	}

	return 0;
}
