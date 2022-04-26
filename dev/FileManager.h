#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <map>
#include "Interval.h"
#include "Scale.h"

class FileManager {
private:
	string m_fileName;
	map<string, vector<string>> m_answers;
public:
	FileManager(string fileName);
	void addAnswer(bool correct, Interval &intervalTarget, string activityType);
	void addAnswer(bool correct, Scale &scaleTarget, string activityType);
	void saveSession();
};

#endif

