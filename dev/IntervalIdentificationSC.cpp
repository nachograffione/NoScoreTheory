#include "IntervalIdentificationSC.h"
#include "Globals.h"
#include "MainView.h"
#include "Piano.h"
#include <algorithm>
#include <string>
#include <tuple>
#include <iostream>
#include "Interval.h"
#include "Note.h"
#include "CustomSprite.h"



IntervalIdentificationSC::IntervalIdentificationSC(MainView &mainV) :
	m_intervalTarget(nullptr),
	m_intervalAnswer(nullptr),
	m_intervalNames(nullptr),
	m_intervalAttributes(nullptr),
	m_piano(nullptr),
	m_answer(nullptr),
	m_change(nullptr),
	m_tick(nullptr),
	m_cross(nullptr),
	m_check(nullptr)
{
	//init
	Note firstPianoNote, endPianoNote;
	firstPianoNote.setNote("do", "", 2);
	endPianoNote.setNote("do", "", 5);
	
	m_piano = new Piano(firstPianoNote, endPianoNote);
	m_answer = new Label("", 30, sf::Color(230,150,150));
	m_change = new Button("Cambiar", 35, sf::Color(40,180,40));
	m_tick = new CustomSprite();
	m_cross = new CustomSprite();
	m_check = new Button("Comprobar", 35, sf::Color(226,13,13));
	{
		std::vector<string> intervalNamesVector;
		std::vector<string> intervalAttributesVector;
		std::string intervalName;
		std::string intervalAttribute;
		for(size_t i = 0; i < glob.INTERVALS.size(); i++){
			std::tie(intervalName, intervalAttribute, std::ignore) = glob.INTERVALS[i];
			//unisono is not used
			if(intervalName != "unisono"){
				//NAME
				//check if it hasn't been already saved
				auto nameIt = std::find(intervalNamesVector.begin(), intervalNamesVector.end(), intervalName);
				if(nameIt == intervalNamesVector.end()){
					//save name
					intervalNamesVector.push_back(intervalName);
				}
				
				//ATTRIBUTE (similar algorithm)
				//check if it hasn't been already saved
				auto attributeIt = std::find(intervalAttributesVector.begin(), intervalAttributesVector.end(), intervalAttribute);
				if(attributeIt == intervalAttributesVector.end()){
					//save attribute
					intervalAttributesVector.push_back(intervalAttribute);
				}
			}
		}
		m_intervalNames = new RadioButton(intervalNamesVector, 32, 65, sf::Color(0,180,0));
		m_intervalAttributes = new RadioButton(intervalAttributesVector, 32, 65, sf::Color(0,180,0));
	};
	
	//set several things
	m_tick->setPath("img\\tick.png");
	m_tick->setScale(0.3, 0.3);
	m_tick->setVisible(false);
	m_cross->setPath("img\\cross.png");
	m_cross->setScale(0.3, 0.3);
	m_cross->setVisible(false);
	m_answer->setString(m_intervalNames->getActiveButton()->getString() + " " + m_intervalAttributes->getActiveButton()->getString());//update answer
	m_piano->setSensible(false);
	
	//set positions
	sf::FloatRect pianoBounds = m_piano->getGlobalBounds();
	
	m_piano->setPosition((mainV.window.getSize().x - pianoBounds.width)*0.5, mainV.window.getSize().y - pianoBounds.height - 10);
	m_change->setPosition(mainV.window.getSize().x * 0.5, mainV.window.getSize().y - pianoBounds.height - 50);
	
	m_intervalNames->setPosition(mainV.window.getSize().x * 0.15, mainV.window.getSize().y * 0.1);
	m_intervalAttributes->setPosition(mainV.window.getSize().x * 0.35, mainV.window.getSize().y * 0.1);
	
	m_check->setPosition(mainV.window.getSize().x * 0.65, mainV.window.getSize().y * 0.35);
	m_answer->setPosition(mainV.window.getSize().x * 0.65, mainV.window.getSize().y * 0.25);
	m_tick->setPosition(mainV.window.getSize().x * 0.85, mainV.window.getSize().y * 0.25);
	m_cross->setPosition(mainV.window.getSize().x * 0.85, mainV.window.getSize().y * 0.25);
	
	generateInterval(*this);
}


void IntervalIdentificationSC::draw(MainView &mainV){
	mainV.window.draw(*m_piano);
	mainV.window.draw(*m_change);
	mainV.window.draw(*m_tick);
	mainV.window.draw(*m_cross);
	mainV.window.draw(*m_check);
	mainV.window.draw(*m_answer);
	mainV.window.draw(*m_intervalNames);
	mainV.window.draw(*m_intervalAttributes);
}

void IntervalIdentificationSC::handler(MainView &mainV){
	switch (mainV.event.type){
	case sf::Event::MouseButtonPressed:
//		sf::Vector2f mousePosition(mainV.event.mouseButton.x, mainV.event.mouseButton.y);
		sf::Vector2f mousePosition(mainV.window.mapPixelToCoords({mainV.event.mouseButton.x, mainV.event.mouseButton.y}));
		if (m_intervalNames->getSensible()){
			for(size_t i=0;i<m_intervalNames->size();i++) {
				if(m_intervalNames->buttonContains(i, mousePosition)){
					m_intervalNames->setActiveButton(i);
					updateAnswer();
					break;
				}
			}
		}
		if (m_intervalAttributes->getSensible()){
			for(size_t i=0;i<m_intervalAttributes->size();i++) {
				if(m_intervalAttributes->buttonContains(i, mousePosition)){
					m_intervalAttributes->setActiveButton(i);
					updateAnswer();
					break;
				}
			}
		}
		if (m_piano->getSensible()){
			for(size_t i=0;i<m_piano->getAllKeys().size();i++) {
				if(m_piano->keyContains(i, mousePosition)){
					m_piano->getKey(i)->switchPressed();
				}
			}
		}
		if(m_change->getSensible()){
			if(m_change->contains(mousePosition)){
				generateInterval(*this);
				m_cross->setVisible(false);
				m_tick->setVisible(false);
			}
		}
		if(m_check->getSensible()){
			if(m_check->contains(mousePosition)){
				if(checkAnswer(mainV)) {
					m_cross->setVisible(false);
					m_tick->setVisible(true);
				}
				else{
					m_cross->setVisible(true);
					m_tick->setVisible(false);
				}
			}
		}
	}
}

void IntervalIdentificationSC::afterDisplay(){
	if(m_tick->getVisible()){
		sleep(2);
		std::vector<Note> empty;
		m_piano->setPressedNotes(empty);
		generateInterval(*this);
		m_tick->setVisible(false);
	}
}

void IntervalIdentificationSC::updateAnswer(){
	std::string intervalNameButton = m_intervalNames->getActiveButton()->getString();
	std::string intervalAttributeButton = m_intervalAttributes->getActiveButton()->getString();
	std::string intervalName;
	std::string intervalAttribute;
	
	//check if the interval exist
	for(size_t i = 0; i < glob.INTERVALS.size(); i++){
		std::tie(intervalName, intervalAttribute, std::ignore) = glob.INTERVALS[i];
		//unisono is not used
		if(intervalName != "unisono"){
			if(intervalNameButton == intervalName and intervalAttributeButton == intervalAttribute){
				m_answer->setString(intervalNameButton + " " + intervalAttributeButton);
				//delete previous interval, if it exists
				if(m_intervalAnswer != nullptr){
					delete m_intervalAnswer;
				}
				//save new interval
				m_intervalAnswer = new Interval();
				m_intervalAnswer->setInterval(m_intervalTarget->getStartNote(), intervalNameButton, intervalAttributeButton);
				break;
			}
			else{
				m_answer->setString("<Intervalo no valido>");
				if(m_intervalAnswer != nullptr){
					delete m_intervalAnswer;
				}
				m_intervalAnswer = nullptr;
			}
		}
	}
	m_cross->setVisible(false);
	m_tick->setVisible(false);
}

bool IntervalIdentificationSC::checkAnswer(MainView &mainV){
	if(m_intervalTarget != nullptr and m_intervalAnswer != nullptr){
		if(*m_intervalAnswer == *m_intervalTarget){
			mainV.file.addAnswer(true, *m_intervalTarget, "IntervalIdentification");
			return true;
		}
		else{
			mainV.file.addAnswer(false, *m_intervalTarget, "IntervalIdentification");
			return false;
		}
	}
	else{
		mainV.file.addAnswer(false, *m_intervalTarget, "IntervalIdentification");
		return false;
	}
}


void generateInterval(IntervalIdentificationSC &intervalIdentificationSC){
	//delete previous interval, if it exists
	if(intervalIdentificationSC.m_intervalTarget != nullptr){
		delete intervalIdentificationSC.m_intervalTarget;
	}
	//generate new interval and assign to the attribute
	std::vector<std::string> empty;
	std::vector<std::string> signatureExclusions = {"bb", "x"};
	std::vector<int> octaveExclusions = {-2,-1,0,1,2,4,5,6,7,8};
	//desc is not used
	std::vector<std::string> directionExclusions = {"desc", ""};
	//unisono is not used
	std::vector<std::string> nameExclusions = {"unisono"};
	std::vector<std::string> attributeExclusions = {""};
	
	intervalIdentificationSC.m_intervalTarget = new Interval();
	//ommit double alterations because make problems with calculateEndNote
	*intervalIdentificationSC.m_intervalTarget = randomInterval(randomNote(empty, signatureExclusions, octaveExclusions), nameExclusions, attributeExclusions, directionExclusions);
	
	//refresh piano
	std::vector<Note> intervalNotes;
	intervalNotes.push_back(intervalIdentificationSC.m_intervalTarget->getStartNote());
	intervalNotes.push_back(intervalIdentificationSC.m_intervalTarget->getEndNote());
	intervalIdentificationSC.m_piano->setPressedNotes(intervalNotes);
	
}


IntervalIdentificationSC::~IntervalIdentificationSC(){
	delete m_intervalNames;
	delete m_intervalAttributes;
	delete m_piano;
	delete m_change;
	delete m_tick;
	delete m_cross;
	delete m_check;
	delete m_intervalTarget;
	delete m_intervalAnswer;
	delete m_answer;
}

