#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <string>
#include <map>
#include <tuple>
using namespace std;

struct Glob{
	//NOTES
	std::vector<std::string> NOTES_NAMES;
	std::vector<std::string> SIGNATURES_NAMES;
	std::map<std::string,int> NOTES_POSITIONS;
	std::map<std::string,int> SIGNATURES_EFFECTS;
	//INTERVALS
	std::vector<std::tuple<std::string,std::string,int>> INTERVALS;
	std::vector<tuple<int, std::string>> INTERVALS_INT_EQUIVALENCES;
	std::vector<std::string> DIRECTIONS;
	//SCALES
	std::vector<std::tuple<std::string, std::vector<int>>> SCALES_TYPES;
	std::vector<std::string> GRADES;
	
};

extern Glob glob;

void globInit();

#endif
