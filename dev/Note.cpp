#include "Note.h"
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Globals.h"

//EXTERN-----------------------------------------------------------------------
std::string randomName(std::vector<std::string> exclusions){
	std::string name;
	do{
	name = glob.NOTES_NAMES[std::rand()%glob.NOTES_NAMES.size()];
	} while (find(exclusions.begin(), exclusions.end(), name) != exclusions.end());		
	return name;
}

std::string randomSignature(std::vector<std::string> exclusions){
	std::string signature;
	do{
		signature = glob.SIGNATURES_NAMES[std::rand()%glob.SIGNATURES_NAMES.size()];
	} while(find(exclusions.begin(), exclusions.end(), signature) != exclusions.end());
	return signature;
}

int randomOctave(std::vector<int> exclusions){
	int octave;
	do{
		octave = std::rand()%11 - 2;	//from -2 to 8
	} while(find(exclusions.begin(), exclusions.end(), octave) != exclusions.end());
	return octave;
}

Note randomNote(std::vector<std::string> NameExclusions, std::vector<std::string> SignatureExclusions, std::vector<int> OctaveExclusions){
	Note note;
	bool isValid = true;
	do{
		isValid = note.setNote(randomName(NameExclusions), randomSignature(SignatureExclusions), randomOctave(OctaveExclusions));
	} while(!isValid);
	return note;
}

vector<Note> getNotesByPosition(int position){
	//declarations
	std::vector<Note> notes, correctNotes;
	int octave, octavePosition, nearestNaturalNoteIndex;
	
	//basic calcs
	octave = position/12 - 2;
	octavePosition = position%12;
	
	//calculate the nearest natural note (previous or the same)
	for(size_t i=0;i<glob.NOTES_NAMES.size();i++) { 
		nearestNaturalNoteIndex = i;
		if(i != glob.NOTES_NAMES.size()-1){		//to avoid an out of range index with i+1
			if(octavePosition - glob.NOTES_POSITIONS[glob.NOTES_NAMES[i+1]] < 0){
				break;
			}
		}
	}
	
	for(int i=0;i<4;i++) {
		Note note;
		note.setName(glob.NOTES_NAMES[nearestNaturalNoteIndex]);
		note.setOctave(octave);
		notes.push_back(note);
	}
	notes[0].shiftName(0);		//(nearby, must exist)		the previous or the same (if it's natural)	
	notes[1].shiftName(1);		//(nearby, must exist)		the next
	notes[2].shiftName(-1);		//(distant, maybe exist)	the previous of previous
	notes[3].shiftName(2);		//(distant, maybe exist)	the next of next
	
	
	//adjust signature
	for (Note &note : notes){
		for(std::string signature : glob.SIGNATURES_NAMES) {
			note.setSignature(signature);
			if (note.getPosition() == position){
				correctNotes.push_back(note);
				break;
			}
		}
	}
	return correctNotes;
}

//Note CLASS

//constructors
Note::Note(){
	//assign default attributes
	m_name = "do";
	m_signature = "";
	m_octave = 3;
	m_position = 60;
}

//getters
std::string Note::getName() const{
	return m_name;
}
std::string Note::getSignature() const{
	return m_signature;
}
int Note::getOctave() const{
	return m_octave;
}
int Note::getPosition() const{
	return m_position;
}

std::string Note::getFullName() const{
	return m_name + m_signature;
}

//setters
bool Note::setNote(std::string name, std::string signature, int octave){
	//Work with parameters instead of attributes until assignation.
	
	int position;
	bool nameIsValid, signatureIsValid, octaveIsValid;
	nameIsValid = signatureIsValid = octaveIsValid = false;
	
	//validate name
	for(std::string validName : glob.NOTES_NAMES){
		if (name == validName){
			nameIsValid = true;
			break;
		}
	}
	if(!nameIsValid){
		return false;
	}
	
	//validate Signature
	for(std::string validSignature: glob.SIGNATURES_NAMES){
		if (signature == validSignature){
			signatureIsValid = true;
			break;
		}
	}
	if(!signatureIsValid){
		return false;
	}
	
	//Validate octave and position
	if(nameIsValid and signatureIsValid){	//to avoid calculating errors
		position = (octave + 2)*12 + glob.NOTES_POSITIONS[name] + glob.SIGNATURES_EFFECTS[signature];
		if(position >= 0 and position <= 127){
			octaveIsValid = true;
		}
	}
	if (!octaveIsValid){
		return false;
	}
	
	//Only if all parameters are valid
	m_name = name;
	m_signature = signature;
	m_octave = octave;
	m_position = position;
	return true;
}

bool Note::setName(std::string name){
	return setNote(name, m_signature, m_octave);
}
bool Note::setSignature(std::string signature){
	return setNote(m_name, signature, m_octave);	
}
bool Note::setOctave(int octave){
	return setNote(m_name, m_signature, octave);	
}

//others
bool Note::shiftName(int movement){
	if(movement != 0){
		std::string name;
		bool isPositive;
		int distance;
		int octaveMovement;
		auto nameIt = find(glob.NOTES_NAMES.begin(), glob.NOTES_NAMES.end(), m_name);
		//take abs and save sign
		if (movement > 0){
			isPositive = true;
		}
		else{
			movement = -movement;
			isPositive = false;
		}
		//shift
		octaveMovement = movement/7;
		if (!isPositive){
			octaveMovement = -octaveMovement;
		}
		movement = movement%7;
		if (isPositive){
			distance = (glob.NOTES_NAMES.end()-1) - nameIt;		//the -1 is because end() points to the next after the last
			if (movement <= distance){
				name = *(nameIt + movement);
			}
			else{
				octaveMovement += 1;
				movement = (movement-1) - distance;		//the -1 is because one movement is for arrive to the begin()
				name = *(glob.NOTES_NAMES.begin() + movement);
			}
		}
		else{
			distance = nameIt - glob.NOTES_NAMES.begin();
			if (movement <= distance){
				name = *(nameIt - movement);
			}
			else{
				octaveMovement -= 1;
				movement = (movement-1) - distance;	//the -1 is because one movement is for arrive to the end()
				name = *((glob.NOTES_NAMES.end()-1) - movement);	//the -1 is because end() points to the next after the last
			}
		}
		return setNote(name, m_signature, m_octave + octaveMovement);
	}
	else{
		return true;
	}
}

bool Note::shiftSignature(int movement){
	if (movement != 0){
		std::string signature;
		bool isPositive;
		int distance;
		auto signatureIt = find(glob.SIGNATURES_NAMES.begin(), glob.SIGNATURES_NAMES.end(), m_signature);
		//save sign and take abs
		if (movement > 0){
			isPositive = true;
		}
		else{
			movement = -movement;
			isPositive = false;
		}
		//shift
		if (isPositive){
			distance = (glob.SIGNATURES_NAMES.end()-1) - signatureIt;		//the -1 is because end() points to the next after the last
			if (movement <= distance){
				signature = *(signatureIt + movement);
			}
			else{
				signature = "notValid";
			}
		}
		else{
			distance = signatureIt - glob.SIGNATURES_NAMES.begin();
			if (movement <= distance){
				signature = *(signatureIt - movement);
			}
			else{
				signature = "notValid";
			}
		}
		return setNote(m_name, signature, m_octave);
	}
	else{
		return true;
	}
}

bool Note::shiftOctave(int movement){
	if (movement != 0){
		return setNote(m_name, m_signature, m_octave+movement);
	}
	else{
		return true;
	}
}


//OPERATORS--------------------------------------------------------------------
std::ostream& operator<<(std::ostream &out, Note &note){
	out << note.getFullName() << "(" << note.getOctave() << ")" << " - " << note.getPosition();
	return out;
}
bool operator==(const Note &note1, const Note &note2){
	return note1.getName() == note2.getName() and note1.getSignature() == note2.getSignature() and note1.getOctave() == note2.getOctave();
}
