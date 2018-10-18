#ifndef GUARD_SPLIT_DATA_H
#define GUARD_SPLIT_DATA_H

#include <vector>

void split_data(
	std::vector<std::vector<double> > images,
	std::vector<double> targets,
	std::vector<std::vector<double> >& imTest,
	std::vector<std::vector<double> >& imTrain,
	std::vector<std::vector<double> >& tarTest,
	std::vector<std::vector<double> >& tarTrain,
	int n)
{
	
	std::vector<double> temp(10,0);	
	for(int i=0;i<images.size();++i) {
		if(i>=n) {
			imTest.push_back(images[i]);

			temp[targets[i]] = 1.;
			tarTest.push_back(temp);
			temp[targets[i]] = 0.;

		} else {
			imTrain.push_back(images[i]);
			temp[targets[i]] = 1.;
			tarTrain.push_back(temp);		
			temp[targets[i]] = 0.;
		}
	}

}












#endif
