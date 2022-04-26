#include "Scale.h"
#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include "Globals.h"
#include "Interval.h"

//EXTERN-----------------------------------------------------------------------

Scale randomScale(std::vector<Note> fundamentalExclusions, std::vector<std::string> typeExclusions){
	Note fundamental;
	std::vector<std::string> emptyString;
	std::vector<int> octaveExclusions = {-2,-1,0,1,2,4,5,6,7,8};
	Scale scale;
	
	//get a type
	std::string type = randomType(typeExclusions);
	
	//get a valid scale
	do{
		//get an out of exclusions note
		do{
			fundamental = randomNote(emptyString, emptyString, octaveExclusions);
		} while(find(fundamentalExclusions.begin(), fundamentalExclusions.end(), fundamental) != fundamentalExclusions.end());		
	} while(!scale.setScale(fundamental, type)); 	//try to set scale and verify if it's valid
	
	return scale;
}

std::string randomType(std::vector<std::string> exclusions){
	std::string type;
	std::string scaleType;
	std::vector<int> scalePositions;
	do{
		tie(scaleType, scalePositions) = glob.SCALES_TYPES[std::rand()%glob.SCALES_TYPES.size()];
		type = scaleType;
	} while (find(exclusions.begin(), exclusions.end(), type) != exclusions.end());		
	return type;
}

//Scale CLASS---------------------------------------------------------------

Scale::Scale(){
	m_type = "mayor";
	//fill notes vector
	for(size_t i=0;i<glob.NOTES_NAMES.size();i++) { 
		//create note
		Note* notePtr = new Note();
		notePtr->setNote(glob.NOTES_NAMES[i], "", 3);
		m_notes.push_back(notePtr);
	}
}


bool Scale::setScale(Note fundamental, std::string type){
	//ONLY FOR NON-ARTIFICIAL SCALES!!
	//The valid scales are those which can be created without double alterations.
	
	
	//check if octave is valid
	if(fundamental.getOctave() != 3){
		return false;
	}
	//check if type is valid
	std::vector<int> scaleRelativePositions;
	bool typeIsValid = false;
	for(size_t i=0;i<glob.SCALES_TYPES.size();i++) { 
		std::string scaleType;
		std::tie(scaleType, scaleRelativePositions) = glob.SCALES_TYPES[i];
		//try to find the type
		if(scaleType == type){
			typeIsValid = true;
			break;
		}
	}
	if(!typeIsValid){
		return false;
	}
	//create notes and check if any note has needed a double alteration (this isn't valid.)
	vector<Note> auxNotes;
	for(size_t i=0;i<scaleRelativePositions.size();i++) {
		//create note
		Note note;
		auxNotes.push_back(note);
		auxNotes[i].setNote(fundamental.getName(),fundamental.getSignature(),fundamental.getOctave());
		//shift name
		auxNotes[i].shiftName(i);
		//adjust signature
		int diference = scaleRelativePositions[i] - calculateSemitones(fundamental, auxNotes[i]);
		auxNotes[i].shiftSignature(diference);
		//check if the note hasn't got double alteration
		if(auxNotes[i].getSignature() == "x" or auxNotes[i].getSignature() == "bb"){
			return false;
		}
	}
	
	//Only if all things are valid, change the attributes
	
	//set type
	m_type = type;
	
	//deallocate notes
	for(size_t i=0;i<m_notes.size();i++) { 
		delete m_notes[i];
	}
	//remove old pointers
	m_notes.resize(0);
	
	//refill
	for(size_t i=0;i<scaleRelativePositions.size();i++) {
		Note* notePtr = new Note();
		notePtr->setNote(auxNotes[i].getName(),auxNotes[i].getSignature(),auxNotes[i].getOctave());
		m_notes.push_back(notePtr);
	}
	
	return true;
}


bool Scale::setScale(const Scale &scale){
	//set type
	this->m_type = scale.getType();
	
	//deallocate notes
	for(size_t i=0;i<this->m_notes.size();i++) { 
		delete this->m_notes[i];
	}
	//remove old pointers
	this->m_notes.resize(0);
	
	//fill with new notes
	for(size_t i=0;i<scale.getNotes().size();i++) { 
		Note* notePtr = new Note();
		*notePtr = scale.getNote(i);
		this->m_notes.push_back(notePtr);
	}
	
	return true;
}


bool Scale::setScale(std::vector<Note> orderedNotes){
	std::string type;
	//recognize type
	bool isType;
	for(size_t i=0;i<glob.SCALES_TYPES.size();i++) { 
		isType = true;
		std::string scaleType;
		std::vector<int> scaleRelativePositions;
		std::tie(scaleType, scaleRelativePositions) = glob.SCALES_TYPES[i];
		//compare all notes with scale relative positions
		for(size_t i=0;i<orderedNotes.size();i++) { 
			if(calculateSemitones(orderedNotes[0], orderedNotes[i]) != scaleRelativePositions[i]){
				isType = false;
				break;
			}
		}
		//if the type was found, save it and don't check the following types
		if(isType){
			type = scaleType;
			break;
		}
	}
	
	//if the type wasn't found, don't change anything
	if(!isType){
		return false;
	}
	
	// Only if all things are valid
	setScale(orderedNotes[0], type);
	return true;
}

std::string Scale::getType() const{
	return m_type;
}
Note Scale::getFundamental() const{
	return *m_notes[0];
}
std::string Scale::getFullName(){
	ostringstream oss;
	oss << m_notes[0]->getFullName() << " " << m_type;
	return oss.str();
}

int Scale::size(){
	return m_notes.size();
}

std::vector<Note> Scale::getNotes() const{
	std::vector<Note> notes;
	for(size_t i=0;i<m_notes.size();i++) { 
		notes.push_back(*m_notes[i]);
	}
	return notes;
}


bool Scale::setType(std::string type){
	for(size_t i=0;i<glob.SCALES_TYPES.size();i++) { 
		std::string scaleType;
		std::vector<int> scaleRelativePositions;
		std::tie(scaleType, scaleRelativePositions) = glob.SCALES_TYPES[i];
		if(scaleType == m_type){
			m_type = type;
			return true;
		}
	}
	return false;
}

std::vector<int> Scale::getPositions(){
	for(size_t i=0;i<glob.SCALES_TYPES.size();i++) { 
		std::string scaleType;
		std::vector<int> scaleRelativePositions;
		std::tie(scaleType, scaleRelativePositions) = glob.SCALES_TYPES[i];
		if(scaleType == m_type){
			return scaleRelativePositions;
		}
	}
}

Note Scale::getNote(int position) const{	//this is for allow const getter in Scale(const Scale &scale)
	return *m_notes[position];
}

std::vector<int> Scale::getSemitonesPattern(){
	std::vector<int> semitonesPattern;
	for(size_t i=0;i<glob.SCALES_TYPES.size();i++) { 
		std::string scaleType;
		std::vector<int> scaleRelativePositions;
		std::tie(scaleType, scaleRelativePositions) = glob.SCALES_TYPES[i];
		//find the type
		if(scaleType == m_type){
			for(size_t i=1;i<scaleRelativePositions.size();i++) { 
				semitonesPattern.push_back(scaleRelativePositions[i] - scaleRelativePositions[i-1]);
			}
			semitonesPattern.push_back(12 - scaleRelativePositions[scaleRelativePositions.size()-1]);
			return semitonesPattern;
		}
	}
}
std::vector<Interval> Scale::getIntervalPattern(){
	Interval interval;
	std::vector<Interval> intervalPattern;
	for(size_t i=0;i<m_notes.size()-1;i++) {
		interval.setInterval(*m_notes[i], *m_notes[i+1]);
		intervalPattern.push_back(interval);
	}
	Note fundamentalOctave = *m_notes[0];
	fundamentalOctave.shiftOctave(1);
	interval.setInterval(*m_notes[m_notes.size()-1], fundamentalOctave);
	intervalPattern.push_back(interval);
	return intervalPattern;
}


Scale::~Scale(){
	for(size_t i=0;i<m_notes.size();i++) { 
		delete m_notes[i];
	}
}


Note& Scale::operator[](int i){
	return *m_notes[i];
}


std::ostream& operator<<(std::ostream &out, Scale &scale){
	out << scale.getFullName() << "    NOTES: ";
	for(Note &note : scale.getNotes()){
		out << note.getFullName() << " ";
	}
	return out;
}

bool operator==(const Scale &scale1, const Scale &scale2){
	return scale1.getFundamental() == scale2.getFundamental() and scale1.getType() == scale2.getType();
}
