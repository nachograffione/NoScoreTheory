#include "Interval.h"
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "Globals.h"
#include "Note.h"

/*
POINTS OF VIEW:
	- mathematical:
		The only relevant thing is the distance between the names.
		(i.e. dob-do# will be considered as an unison, dobb-six as a 7th, or do-rebb as a 2nd)
	- musical:
		The considered intervals are those which are in INTERVAL_NAMES
*/



//EXTERN-----------------------------------------------------------------------

//VERIFICATIONS------------------------------------------------

bool nameDistanceIsInRange(Note startNote, Note endNote){
	//IT WILL BE CALLED ONLY BY calculateIntervalName
	//It works under the mathematical point of view (see above).
	//Filter notes which not exceed the 7th ("accepted intervals").
	
	/*
	Working:
	For filtering, the function follows this criterion:
	The startNote defines a radius (+- 1 octave) which includes all the accepted notes.
	This radius include:
		("previous" and "next" refers to the position in the names vector)
		(for the begin and end notes of the vector, some of these options could not apply)
		- the same note, obviously in the same octave
		- previous and next notes in the same octave
		- previous notes in the next octave
		- next notes in the previous octave
	*/
	
	bool isInRange;
	
	//get position names
	auto startNoteIt = std::find(glob.NOTES_NAMES.begin(),glob.NOTES_NAMES.end(), startNote.getName());
	auto endNoteIt = std::find(glob.NOTES_NAMES.begin(),glob.NOTES_NAMES.end(), endNote.getName());
	
	//verify if it is an accepted interval
	isInRange = false;
	if (endNoteIt == startNoteIt and endNote.getOctave() == startNote.getOctave()){
		isInRange = true;
	}
	else if (endNoteIt > startNoteIt and (endNote.getOctave() == startNote.getOctave() or endNote.getOctave() == startNote.getOctave()-1)){
		isInRange = true;
	}
	else if (endNoteIt < startNoteIt and (endNote.getOctave() == startNote.getOctave() or endNote.getOctave() == startNote.getOctave()+1)){
		isInRange = true;
	}
	
	return isInRange;
}


//CALCULATIONS---------------------------------------------------
int calculateSemitones(Note note1, Note note2){
	return std::abs(note2.getPosition() - note1.getPosition());	
}

std::string calculateDirection(Note startNote, Note endNote){
	if (startNote.getPosition() < endNote.getPosition()){
		return glob.DIRECTIONS[0];
	}
	else if (startNote.getPosition() > endNote.getPosition()){
		return glob.DIRECTIONS[1];
	}
	else{
		return glob.DIRECTIONS[2];
	}
}

std::string calculateNameDistance(Note startNote, Note endNote){
	//IT WILL BE CALLED ONLY BY calculateIntervalName
	//It works under the mathematical point of view (see above).
	int itDistance;
	bool isUpward;
	std::string nameDistance;
	
	if (nameDistanceIsInRange(startNote, endNote)){		//Verify if the interval not exceed the 7th.
		
		//get position names
		auto startNoteIt = std::find(glob.NOTES_NAMES.begin(),glob.NOTES_NAMES.end(), startNote.getName());
		auto endNoteIt = std::find(glob.NOTES_NAMES.begin(),glob.NOTES_NAMES.end(), endNote.getName());
		
		//itDistance "a priori"
		itDistance = abs(endNoteIt - startNoteIt);
		
		//verify if it's necessary to invert
		isUpward = endNote.getPosition() > startNote.getPosition();
		if ((isUpward and endNoteIt < startNoteIt) or (!isUpward and endNoteIt > startNoteIt)){
			itDistance = 7 - itDistance;
		}
		
		//convert index distance into traditional nomenclature (the +1 is for adapt it, i.e. distance 1 is a 2nd)
		for(size_t i=0;i<glob.INTERVALS_INT_EQUIVALENCES.size();i++) { 
			int distanceInt;
			std::string distanceStr;
			tie(distanceInt, distanceStr) = glob.INTERVALS_INT_EQUIVALENCES[i];
			if (distanceInt == itDistance+1){
				nameDistance = distanceStr;
				break;
			}
		}
		return nameDistance;
	}
	else{
		return "invalid";
	}
}

std::string calculateIntervalName(Note startNote, Note endNote){
	//It works under the musical point of view (see above).
	
	//calculate name distance
	std::string nameDistance;
	nameDistance = calculateNameDistance(startNote, endNote);	//it includes verification
	if (nameDistance == "invalid"){
		return "invalid";
	}
	
	
	//calculate semitones
	int semitones;
	semitones = calculateSemitones(startNote, endNote);
	
	//check if the interval is valid
	bool isValid;
	std::string intervalName;
	std::string intervalAttribute;
	int intervalSemitones;
	
	isValid = false;
	for(size_t i = 0; i < glob.INTERVALS.size(); i++){
		tie(intervalName, intervalAttribute, intervalSemitones) = glob.INTERVALS[i];
		if (intervalName == nameDistance){
			if (intervalSemitones == semitones){
				isValid = true;
				break;
			}
		}
	}
	
	//if is valid, return it
	if (isValid){
		return intervalName + " " + intervalAttribute;
	}
	else{
		return "invalid";
	}
}


Note calculateEndNote(const Note &startNote, std::string name, std::string attribute, std::string direction, int semitones){
	//IT HAS NO VALIDATION!! Some start notes (with double alterations) have problems
	
	//start from startNote without signature
	Note endNote = startNote;
	endNote.setSignature("");
	
	//adjust name
	for(size_t i=0;i<glob.INTERVALS_INT_EQUIVALENCES.size();i++) { 
		int distanceInt;
		std::string distanceStr;
		tie(distanceInt, distanceStr) = glob.INTERVALS_INT_EQUIVALENCES[i];
		if (distanceStr == name){
			distanceInt -= 1;	//this is for convert nomenclature into index movement
			if (direction == "desc"){
				distanceInt = -distanceInt;
			}
			endNote.shiftName(distanceInt);
			break;
		}
	}
	
	//adjust signature
	int diference = semitones - calculateSemitones(startNote, endNote);
	if (direction == "desc"){
		diference = -diference;
	}
	endNote.shiftSignature(diference);
	
	return endNote;
}


//Interval CLASS---------------------------------------------------------------

//constructors
Interval::Interval(){
	Note startNote, endNote;
	startNote.setNote("do");
	endNote.setNote("do");
	
	m_name = "unisono";
	m_attribute = "";
	m_semitones = 0;
	m_direction = "";
	m_startNote = startNote;
	m_endNote = endNote;
}

//getters
Note& Interval::getStartNote(){
	return m_startNote;
}
Note& Interval::getEndNote(){
	return m_endNote;
}
std::string Interval::getName(){
	return m_name;
}
std::string Interval::getAttribute(){
	return m_attribute;
}
std::string Interval::getDirection(){
	return m_direction;
}
int Interval::getSemitones(){
	return m_semitones;
}

std::string Interval::getFullName(){
	std::string fullname;
	fullname += m_name;
	if(m_attribute != ""){
		fullname += (" " + m_attribute);
	}
	if(m_direction != ""){
		fullname += (" " + m_direction);
	}
	return fullname;
}

Interval Interval::getInvertion(){
	Interval interval;
	Note startNote = m_startNote;
	Note endNote = m_endNote;
	if (m_name != "unison"){
		if (m_direction == "asc"){
			endNote.shiftOctave(-1);
		}
		else if (m_direction == "desc"){
			endNote.shiftOctave(1);
		}
		interval.setInterval(startNote, endNote);
		return interval;
	}
	else{
		interval.setInterval(startNote, endNote);
		return interval;
	}
}


//setters
bool Interval::setInterval(Note startNote, Note endNote){
	//calculate name (with validation)
	std::string fullName;
	fullName = calculateIntervalName(startNote, endNote);
	
	if(fullName != "invalid"){
		//separate fullName in the attributes
		int spacePos;
		spacePos = fullName.find(" ");
		m_name = fullName.substr(0, spacePos);
		m_attribute = fullName.substr(spacePos+1, fullName.length()-spacePos);
		m_semitones = calculateSemitones(startNote, endNote);
		m_direction = calculateDirection(startNote, endNote);
		m_startNote = startNote;
		m_endNote = endNote;
		return true;
	}
	return false;
}


bool Interval::setInterval(Note startNote, std::string name, std::string attribute, std::string direction){
	//Work with parameters instead of attributes until assignation.
	
	bool nameIsValid, attributeIsValid, directionIsValid;
	nameIsValid = attributeIsValid = directionIsValid = false;
	
	//validate direction
	for(std::string validDirection : glob.DIRECTIONS) { 
		if (direction == validDirection) {
			directionIsValid = true;
			break;
		}
	}
	if(!directionIsValid){
		return false;
	}
	
	//validate name and attribute (and save semitones for avoid iterate the vector again)
	int semitones;
	for(size_t i=0;i<glob.INTERVALS.size();i++) { 
		std::string intervalName;
		std::string intervalAttribute;
		int intervalSemitones;
		tie(intervalName, intervalAttribute, intervalSemitones) = glob.INTERVALS[i];
		if (intervalName == name and intervalAttribute == attribute){
			nameIsValid = true;
			attributeIsValid = true;
			semitones = intervalSemitones;
			break;
		}
	}
	if (!nameIsValid or !attributeIsValid){
		return false;
	}
	
	//validate endNote (to avoid out of range problem)
	if (startNote.getPosition() + semitones > 127 or startNote.getPosition() - semitones < 0){
		return false;
	}
	
	//Only if all parameters are valid
	m_startNote = startNote;
	m_endNote = calculateEndNote(startNote, name, attribute, direction, semitones);
	m_name = name;
	m_attribute = attribute;
	m_semitones = semitones;
	m_direction = direction;
	return true;
}

bool Interval::setStartNote(Note note){
	return setInterval(note, m_endNote);
}

bool Interval::setEndNote(Note note){
	return setInterval(m_startNote, note);
}

bool Interval::setNameAndAttribute(std::string name, std::string attribute){
	return setInterval(m_startNote, name, attribute, m_direction);
}

bool Interval::setAttribute(std::string attribute){
	return setInterval(m_startNote, m_name, attribute, m_direction);
}

bool Interval::setDirection(std::string direction){
	return setInterval(m_startNote, m_name, m_attribute, direction);
}

//others
void Interval::invert(){
	//it calls getInvertion instead of implements the algorithm again to avoid problems if the algorithm changes
	Interval invertion = getInvertion();
	setInterval(invertion.getStartNote(), invertion.getEndNote());
}

Interval randomInterval(Note startNote, std::vector<std::string> nameExclusions, 
						std::vector<std::string> attributeExclusions, std::vector<std::string> directionExclusions){
	Interval interval;
	std::string intervalName;
	std::string intervalAttribute;
	std::string intervalDirection;
	do{
		//avoid exlusions
		do{
			tie(intervalName, intervalAttribute, ignore) = glob.INTERVALS[std::rand()%glob.INTERVALS.size()];
		} while(find(nameExclusions.begin(), nameExclusions.end(), intervalName) != nameExclusions.end() or
				find(attributeExclusions.begin(), attributeExclusions.end(), intervalAttribute) != attributeExclusions.end());
		do{
			intervalDirection = glob.DIRECTIONS[std::rand()%glob.DIRECTIONS.size()];
		} while(find(directionExclusions.begin(), directionExclusions.end(), intervalDirection) != directionExclusions.end());
	//avoid non valid intervals
	} while (!interval.setInterval(startNote, intervalName, intervalAttribute, intervalDirection));
	return interval;
}


//OPERATORS--------------------------------------------------------------------
std::ostream& operator<<(std::ostream &out, Interval &interval){
	out << interval.getFullName() << " (" << interval.getSemitones() << "st)";
	out << "    FROM " << interval.getStartNote() << "    TO " << interval.getEndNote();
	return out;
}

bool operator==(Interval &interval1, Interval &interval2) {
	return interval1.getName() == interval2.getName() and interval1.getAttribute() == interval2.getAttribute() and 
		interval1.getDirection() == interval2.getDirection();
}
