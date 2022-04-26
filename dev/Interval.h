#ifndef INTERVAL_H
#define INTERVAL_H

#include <cstdlib>
#include "Note.h"
#include "Globals.h"



int calculateSemitones(Note note1, Note note2);

std::string calculateDirection(Note startNote, Note endNote);

bool validateNameDistance(Note startNote, Note endNote);

std::string calculateNameDistance(Note startNote, Note endNote);

std::string calculateIntervalName(Note startNote, Note endNote);

Note calculateEndNote(const Note &startNote, std::string name, std::string attribute, std::string direction, int semitones);

class Interval{
private:
	//composition
	Note m_startNote;
	Note m_endNote;
	
	//name
	std::string m_name;
	std::string m_attribute;
	
	//others
	std::string m_direction;
	int m_semitones;
	
public:
	//constructors
	Interval();
	
	//getters
	Note& getStartNote();
	Note& getEndNote();
	std::string getName();
	std::string getAttribute();
	std::string getDirection();
	int getSemitones();
	
	std::string getFullName();
	Interval getInvertion();
	
	//setters
	bool setInterval(Note startNote, Note endNote);
	bool setInterval(Note startNote, std::string name, std::string attribute, std::string direction=glob.DIRECTIONS[0]);
	bool setStartNote(Note note);
	bool setEndNote(Note note);
	bool setNameAndAttribute(std::string name, std::string attribute);
	bool setAttribute(std::string attribute);
	bool setDirection(std::string direction);
	
	//others
	void invert();
};

Interval randomInterval(Note startNote, std::vector<std::string> nameExclusions,
						std::vector<std::string> attributeExclusions, std::vector<std::string> directionExclusions);

std::ostream& operator<<(std::ostream &out, Interval &interval);
bool operator==(Interval &interval1, Interval &interval2);

#endif
