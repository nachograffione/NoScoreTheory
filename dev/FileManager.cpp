#include "FileManager.h"
#include "Interval.h"
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
using namespace std;

FileManager::FileManager(string fileName): m_fileName(fileName) {
	m_answers["IntervalIdentification"];
	m_answers["IntervalConstruction"];
	m_answers["ScaleIdentification"];
	m_answers["ScaleConstruction"];
}

void FileManager::addAnswer(bool correct, Interval &intervalTarget, string activityType){
	ostringstream answer;
	if(correct){
		answer << "CORRECT";
	}
	else{
		answer <<"        " << intervalTarget;
	}
	m_answers[activityType].push_back(answer.str());
	
}

void FileManager::addAnswer(bool correct, Scale &scaleTarget, string activityType){
	ostringstream answer;
	if(correct){
		answer << "CORRECT";
	}
	else{
		answer <<"        " << scaleTarget;
	}
	m_answers[activityType].push_back(answer.str());
}

void FileManager::saveSession(){
	//save up to 4 last sessions
	fstream file;
	
	file.open(m_fileName, ios::in);
	
	vector<string> aux;
	//DON'T USE !file.is_open() RETURN (because the write part must be excecuted)
	if(file.is_open()){
		string line;
		int counter = 0;
		while(getline(file, line)){
			if(line[0] == '-'){			//count sessions
				counter++;
				if(counter == 5) break;
			}
			aux.push_back(line);
		}
	}
	file.close();
	
	
	//write
	file.open(m_fileName,ios::out|ios::trunc);
	if(!file.is_open()) return;
	
	//the current session
	
	//for date
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	
	file << "\n\n-----SESSION    " << std::put_time(&tm,"%d-%m-%Y %H:%M") << endl;
	auto it = m_answers.begin();
	int correctAnswers = 0;
	while(it != m_answers.end()){
		//title
		file << "\n" << it->first << endl;
		//correct answers
		for(string &ans : it->second){			
			if(ans == "CORRECT") correctAnswers++;
		}
		file << "    Correct answers: " << correctAnswers << endl;
		correctAnswers = 0;
		//incorrect answers
		file << "    Incorrect answers details (targets): " << endl;
		for(string &ans : it->second){
			if(ans != "CORRECT") file << ans << endl;;
		}
		it++;
	}
	
	//write aux
	for(string &s : aux){
		file << s << endl;
	}
	
	file.close();
}
