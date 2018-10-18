#ifndef GUARD_NEURALNET_H
#define GUARD_NEURALNET_H

#include "neuron.h"

#include <vector>
#include <cstdlib>
#include <cassert>
#include <math.h> 

#include <iostream>



class NeuralNet{
public:
	NeuralNet(std::vector<unsigned> topology);

	void forwardProp(std::vector<double> input);
	void backProp(std::vector<double> target,double eta);
	
	double getNeuronVal(unsigned li, unsigned ni) const  { return layers[li][ni].getOutVal();}
	double getNeuronDelta(unsigned li, unsigned ni) const { return layers[li][ni].getDelta();}
	void setWeight(unsigned li, unsigned ni, unsigned nj,double val) 
					{ weights[li][ni][nj] = val;}
	double errorFunc(std::vector<double> targetVals);
	std::vector<double> getOutput();
private:
	std::vector<std::vector<Neuron> > layers;
	unsigned numLayers;
	// weights[l][i][j] is weight of 
	// neuron i in layer l to neuron j in layer l+1
	std::vector<std::vector<std::vector<double> > > weights;
	
};

std::vector<double> NeuralNet::getOutput()
{
	std::vector<double> output(layers[numLayers-1].size()-1);
	for(unsigned ni=0;ni<layers[numLayers-1].size()-1;++ni)
		output[ni] = layers[numLayers-1][ni].getOutVal();
	return output;
}
void NeuralNet::backProp(std::vector<double> target,double eta)
{
	assert(layers[numLayers-1].size()-1 == target.size());
	double sum;
	// ni is the index of a neuron in output layer
	for(unsigned ni = 0; ni < layers[numLayers-1].size() - 1; ++ ni ) {
		Neuron &n = layers[numLayers-1][ni];
		n.setDelta( (n.getOutVal() - target[ni])*n.getOutValDeriv()/(layers[numLayers-1].size()-1) );
		//n.setDelta( (n.getOutVal() - target[ni])/(layers[numLayers-1].size()-1) );

	}

	// li is layer index 
	for(int li = numLayers - 2;li >= 0; --li) {
		// ni is neuron index in layer li
		for(unsigned ni = 0;ni < layers[li].size()-1;++ni) {
			sum = 0.;
			// nj is neuron j in layer li+1
			for(unsigned nj = 0;nj<layers[li+1].size()-1;++nj) {
				sum += weights[li][ni][nj]*layers[li+1][nj].getDelta();
			}

			layers[li][ni].setDelta( sum*layers[li][ni].getOutValDeriv() );
		}

	}

	// update weights
	for(unsigned li = 0;li<numLayers -2;++li) {
		for(unsigned ni=0;ni<layers[li].size();++ni) {
			for(unsigned nj = 0;nj<layers[li+1].size()-1;++nj) {
				weights[li][ni][nj] -= eta*layers[li][ni].getOutVal()*layers[li+1][nj].getDelta();
			}
		}
	}

}

double NeuralNet::errorFunc(std::vector<double> targetVals)
{
	assert(layers[numLayers-1].size() - 1 == targetVals.size());

	double error = 0;
	double delta;
	for(unsigned n =0; n < targetVals.size();++n) {
		delta = targetVals[n]-layers[numLayers-1][n].getOutVal();
		error += delta*delta;
	}
	return error;
}


// changed input to setOutVal:CHECK!!!!!!!!
void NeuralNet::forwardProp(std::vector<double> input)
{
	assert(layers[0].size() - 1 == input.size());

	// set input layer
	for(unsigned n = 0;n < input.size();++n)
		layers[0][n].setOutVal( input[n]);
	double sum;

	// li = layer index
	for(unsigned li = 1;li < numLayers-1; ++li) {
		// -1 because you do not change the value of the bias neuron 
		// rni = right neuron index
		for(unsigned rni = 0; rni < layers[li].size() - 1;++rni) {
			// sum is input to rni
			sum  = 0.;
			//lni = left neuron index
			for(unsigned lni = 0;lni < layers[li-1].size();++lni) {
				sum += weights[li-1][lni][rni]*layers[li-1][lni].getOutVal();
			}
			layers[li][rni].setInVal(sum);
		}
	}
	int li = numLayers-1;
	for(unsigned rni = 0; rni < layers[li].size() - 1;++rni) {
		// sum is input to rni
		sum  = 0.;
		//lni = left neuron index
		for(unsigned lni = 0;lni < layers[li-1].size();++lni) {
			sum += weights[li-1][lni][rni]*layers[li-1][lni].getOutVal();
		}
		layers[li][rni].setInValo(sum);
	}
}

NeuralNet::NeuralNet(std::vector<unsigned> topology) 
{
	numLayers = topology.size();
	// add layers to the network 
	for(unsigned layerIndex = 0;layerIndex < topology.size(); ++layerIndex) {
		//add extra bias neuron if 
		layers.push_back(std::vector<Neuron>(topology[layerIndex]+1));
	}	

	// make the weight object
	for(unsigned layerIndex = 0;layerIndex < topology.size() - 1; ++layerIndex) {
		weights.push_back(std::vector<std::vector<double> >(topology[layerIndex]+1));

		for(unsigned leftNeuronIndex = 0;leftNeuronIndex < topology[layerIndex] + 1;
			++leftNeuronIndex) {

			weights[layerIndex].push_back(std::vector<double>());
			for(unsigned rightNeuronIndex = 0; rightNeuronIndex < topology[layerIndex+1];
				++rightNeuronIndex) {
				weights[layerIndex][leftNeuronIndex].push_back( -.5 + (double)rand()/RAND_MAX);

			}
		}
	}

}



#endif
