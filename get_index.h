#ifndef GUARD_GET_INDEX_H
#define GUARD_GET_INDEX_H


void get_index(
	const std::vector<double>& output,
	const std::vector<double>& target,
	int& iout,int& itar)
{
	double out = output[0];
	double tar = target[0];

	for(int i=0;i<output.size();++i) {
		if(out<output[i]) {
			out = output[i];
			iout = i;
		}
		if(tar<target[i]) {
			tar = target[i];
			itar = i;
		}
	}


}





#endif
