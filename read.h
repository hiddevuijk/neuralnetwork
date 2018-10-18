#ifndef GUARD_read_H
#define GUARD_read_H

#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::vector<double> split_string(std::string str, char sep)
{
	std::vector<double> vec;


	std::size_t l=0,r=0;
	r = str.find(',');
	while(r < str.size()-1 ) {

		vec.push_back(std::stod(str.substr(l,r-l)) );
		l = r+1;
		r = str.find(',',l);
	}
	vec.push_back( std::stod(str.substr(l,r-l) ));

 
	return vec;
}

std::vector<double> get_target(std::string name)
{
	std::vector<double> vec;

	std::fstream indata(name);
	std::string line;

	while( std::getline(indata,line) ) {
		vec.push_back(std::stoi(line));
	}	


	return vec;

}

std::vector<std::vector<double> > get_digits(std::string name)
{
	std::fstream indata(name);
	std::vector<std::vector<double> > data;
	std::string line;
	while( std::getline(indata,line) ) {
		data.push_back( split_string(line,',') );
	}
	return data;
}




#endif
