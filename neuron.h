#ifndef GUARD_NEURON_H
#define GUARD_NEURON_H

#include <math.h>

class Neuron{
public:
	Neuron() : outVal(1.){};
	void setOutVal(double newVal) { outVal = newVal;}
	void setInVal(double newVal) { 
			inVal = newVal;
			outVal = transferFunc(newVal);
			outValDeriv = transferFuncDeriv(newVal); }
	void setOutValo(double newVal) { outVal = newVal;}
	void setInValo(double newVal) { 
			inVal = newVal;
			outVal = outFunc(newVal);
			outValDeriv = outFuncDeriv(newVal); }


	double getInVal() const {return inVal;}
	double getOutVal() const {return outVal;}
	double getOutValDeriv() const {return outValDeriv;}
	double getDelta() const { return delta;}
	void setDelta(double newDelta) { delta = newDelta;}
private:
	static double transferFunc(double x) { return tanh(x);}
	static double transferFuncDeriv(double x) { return 1-tanh(x)*tanh(x);}
	static double outFunc(double x) { return .5+0.5*tanh(x);}
	static double outFuncDeriv(double x) {return  0.5 - 0.5*tanh(x)*tanh(x);}
	//static double outFunc(double x) { return x;}
	//static double outFuncDeriv(double x) {return  1.;}
	double inVal;
	double outVal;
	double outValDeriv;
	double delta;
};




#endif
