#include "Globals.h"
#include <vector>
#include <map>
#include <tuple>

Glob glob;

void globInit(){
	//NOTES
	glob.NOTES_NAMES.push_back("do");
	glob.NOTES_NAMES.push_back("re");
	glob.NOTES_NAMES.push_back("mi");
	glob.NOTES_NAMES.push_back("fa");
	glob.NOTES_NAMES.push_back("sol");
	glob.NOTES_NAMES.push_back("la");
	glob.NOTES_NAMES.push_back("si");
	
	glob.SIGNATURES_NAMES.push_back("bb");
	glob.SIGNATURES_NAMES.push_back("b");
	glob.SIGNATURES_NAMES.push_back("");
	glob.SIGNATURES_NAMES.push_back("#");
	glob.SIGNATURES_NAMES.push_back("x");
	
	glob.NOTES_POSITIONS.insert(std::make_pair("do",0));
	glob.NOTES_POSITIONS.insert(std::make_pair("re",2));
	glob.NOTES_POSITIONS.insert(std::make_pair("mi",4));
	glob.NOTES_POSITIONS.insert(std::make_pair("fa",5));
	glob.NOTES_POSITIONS.insert(std::make_pair("sol",7));
	glob.NOTES_POSITIONS.insert(std::make_pair("la",9));
	glob.NOTES_POSITIONS.insert(std::make_pair("si",11));
	
	glob.SIGNATURES_EFFECTS.insert(std::make_pair("bb",-2));
	glob.SIGNATURES_EFFECTS.insert(std::make_pair("b",-1));
	glob.SIGNATURES_EFFECTS.insert(std::make_pair("",0));
	glob.SIGNATURES_EFFECTS.insert(std::make_pair("#",1));
	glob.SIGNATURES_EFFECTS.insert(std::make_pair("x",2));

	//INTERVALS
	glob.INTERVALS.push_back(std::make_tuple("unisono", "", 0));
	glob.INTERVALS.push_back(std::make_tuple("2da", "menor", 1));
	glob.INTERVALS.push_back(std::make_tuple("2da", "mayor", 2));
	glob.INTERVALS.push_back(std::make_tuple("2da", "aumentada", 3));
	glob.INTERVALS.push_back(std::make_tuple("3ra", "disminuida", 2));	//invertion of 6ta disminuida
	glob.INTERVALS.push_back(std::make_tuple("3ra", "menor", 3));
	glob.INTERVALS.push_back(std::make_tuple("3ra", "mayor", 4));
	glob.INTERVALS.push_back(std::make_tuple("4ta", "disminuida", 4));	//invertion of 5ta aumentada
	glob.INTERVALS.push_back(std::make_tuple("4ta", "justa", 5));
	glob.INTERVALS.push_back(std::make_tuple("4ta", "aumentada", 6));
	glob.INTERVALS.push_back(std::make_tuple("5ta", "disminuida", 6));
	glob.INTERVALS.push_back(std::make_tuple("5ta", "justa", 7));
	glob.INTERVALS.push_back(std::make_tuple("5ta", "aumentada", 8));
	glob.INTERVALS.push_back(std::make_tuple("6ta", "menor", 8));
	glob.INTERVALS.push_back(std::make_tuple("6ta", "mayor", 9));
	glob.INTERVALS.push_back(std::make_tuple("6ta", "aumentada", 10));
	glob.INTERVALS.push_back(std::make_tuple("7ma", "disminuida", 9));
	glob.INTERVALS.push_back(std::make_tuple("7ma", "menor", 10));
	glob.INTERVALS.push_back(std::make_tuple("7ma", "mayor", 11));
	
	glob.DIRECTIONS.push_back("asc");
	glob.DIRECTIONS.push_back("desc");
	glob.DIRECTIONS.push_back("");		//this is for unison
	
	glob.INTERVALS_INT_EQUIVALENCES.push_back(std::make_tuple(1,"unisono"));
	glob.INTERVALS_INT_EQUIVALENCES.push_back(std::make_tuple(2,"2da"));
	glob.INTERVALS_INT_EQUIVALENCES.push_back(std::make_tuple(3,"3ra"));
	glob.INTERVALS_INT_EQUIVALENCES.push_back(std::make_tuple(4,"4ta"));
	glob.INTERVALS_INT_EQUIVALENCES.push_back(std::make_tuple(5,"5ta"));
	glob.INTERVALS_INT_EQUIVALENCES.push_back(std::make_tuple(6,"6ta"));
	glob.INTERVALS_INT_EQUIVALENCES.push_back(std::make_tuple(7,"7ma"));
	
	//SCALES
	std::vector<int> majorScalePositions = {0, 2, 4, 5, 7, 9, 11};
	glob.SCALES_TYPES.push_back(std::make_tuple("mayor", majorScalePositions));
	std::vector<int> naturalMinorScalePositions = {0, 2, 3, 5, 7, 8, 10};
	glob.SCALES_TYPES.push_back(std::make_tuple("menor natural", naturalMinorScalePositions));
	//WARNING!
	//For artificial scales, the Scale constructor should be changed (because it throws an exception
	//if there is some note with a double alteration. This is correct only for non-artificial scales.)
	
	
	
	//SCALES AND HARMONY
	glob.GRADES.push_back("I");
	glob.GRADES.push_back("II");
	glob.GRADES.push_back("III");
	glob.GRADES.push_back("IV");
	glob.GRADES.push_back("V");
	glob.GRADES.push_back("VI");
	glob.GRADES.push_back("VII");
}
