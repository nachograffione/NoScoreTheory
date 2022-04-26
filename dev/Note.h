#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <iostream>
#include <vector>


class Note{
private:	
	//name
	std::string m_name;
	std::string m_signature;
	
	//others
	int m_octave;
	int m_position;
	
public:
	//constructors
	Note();
	
	//getters
	std::string getName() const;
	std::string getSignature() const;
	int getPosition() const;
	int getOctave() const;
	std::string getFullName() const;
	//setters
	bool setNote(std::string name="do", std::string signature="", int octave=3);
	bool setName(std::string name);
	bool setSignature(std::string signature);
	bool setOctave(int octave);
	//others
	bool shiftName(int movement);
	bool shiftSignature(int movement);
	bool shiftOctave(int movement);
};

std::string randomName(std::vector<std::string> exclusions);
std::string randomSignature(std::vector<std::string> exclusions);
int randomOctave(std::vector<int> exclusions);
Note randomNote(std::vector<std::string> NameExclusions, std::vector<std::string> SignatureExclusions, std::vector<int> OctaveExclusions);

std::vector<Note> getNotesByPosition(int position);

//operators
std::ostream& operator<<(std::ostream &out, Note &note);
bool operator==(const Note &note1, const Note &note2);
#endif
