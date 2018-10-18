#ifndef GUARD_AVG_H
#define GUARD_AVG_H

#include <vector>

void avg(std::vector<double>& v1, std::vector<double> v2) 
{

	for(int i=0;i<v1.size();++i) {
		v1[i] = 0.5*(v1[i]+v2[i]);
	}
}





#endif
