#ifndef SCALE_H
#define SCALE_H
#include "Note.h"
#include <vector>
#include <string>
#include "Interval.h"
#include "Scale.h"

class Scale {
private:	
	std::string m_type;
	std::vector<Note*> m_notes;

public:
	//constructors
	Scale();
	
	//getters
	Note getNote(int position) const;	//this is for allow const getter in Scale(const Scale &scale)
	std::string getType() const;
	std::vector<Note> getNotes() const;
	Note getFundamental() const;
	int size();
	std::string getFullName();
	std::vector<int> getPositions();
	std::vector<int> getSemitonesPattern();
	std::vector<Interval> getIntervalPattern();
	
	//setters
	bool setScale(const Scale &scale);
	bool setScale(Note fundamental, std::string type);
	bool setScale(std::vector<Note> orderedNotes);
	bool setType(std::string type);
	bool setFundamental(Note fundamental);
	
	~Scale();
	
	Note& operator[](int i);
};

Scale randomScale(std::vector<Note> noteExclusions, std::vector<std::string> typeExclusions);
std::string randomType(std::vector<std::string> exclusions);

std::ostream& operator<<(std::ostream &out, Scale &scale);
bool operator==(const Scale &scale1, const Scale &scale2);

#endif

