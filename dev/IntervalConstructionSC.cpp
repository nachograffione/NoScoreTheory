#include "IntervalConstructionSC.h"
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
#include <sstream>

IntervalConstructionSC::IntervalConstructionSC(MainView &mainV) :
	m_intervalTargetLabel(nullptr),
	m_check(nullptr),
	m_change(nullptr),
	m_tick(nullptr),
	m_cross(nullptr),
	m_piano(nullptr),
	m_intervalTarget(nullptr),
	m_intervalAnswer(nullptr)
{
	//init
	m_intervalTargetLabel = new Label("", 30, sf::Color(230,150,150));
	m_check = new Button("Comprobar", 35, sf::Color(226,13,13));
	m_change = new Button("Cambiar", 35, sf::Color(40,180,40));
	m_tick = new CustomSprite();
	m_cross = new CustomSprite();
	
	Note firstPianoNote, endPianoNote;
	firstPianoNote.setNote("do", "", 2);
	endPianoNote.setNote("do", "", 5);
	
	m_piano = new Piano(firstPianoNote, endPianoNote);
	
	//set several things
	m_tick->setPath("img\\tick.png");
	m_tick->setScale(0.3, 0.3);
	m_tick->setVisible(false);
	m_cross->setPath("img\\cross.png");
	m_cross->setScale(0.3, 0.3);
	m_cross->setVisible(false);
	m_intervalTargetLabel->setString("<>");	//update answer
	
	//set positions
	sf::FloatRect pianoBounds = m_piano->getGlobalBounds();
	
	m_intervalTargetLabel->setPosition(mainV.window.getSize().x * 0.5, mainV.window.getSize().y * 0.25);
	m_check->setPosition(mainV.window.getSize().x * 0.5, mainV.window.getSize().y * 0.35);
	
	m_change->setPosition(mainV.window.getSize().x * 0.5, mainV.window.getSize().y - pianoBounds.height - 50);
	m_piano->setPosition((mainV.window.getSize().x - pianoBounds.width)*0.5, mainV.window.getSize().y - pianoBounds.height - 10);
	
	m_tick->setPosition(mainV.window.getSize().x * 0.8, mainV.window.getSize().y * 0.25);
	m_cross->setPosition(mainV.window.getSize().x * 0.8, mainV.window.getSize().y * 0.25);
	
	generateInterval(*this);
}


void IntervalConstructionSC::draw(MainView &mainV){
	mainV.window.draw(*m_intervalTargetLabel);
	mainV.window.draw(*m_check);
	mainV.window.draw(*m_change);
	mainV.window.draw(*m_piano);
	mainV.window.draw(*m_tick);
	mainV.window.draw(*m_cross);
}

void IntervalConstructionSC::handler(MainView &mainV){
	switch (mainV.event.type){
	case sf::Event::MouseButtonPressed:
//		sf::Vector2f mousePosition(mainV.event.mouseButton.x, mainV.event.mouseButton.y);
		sf::Vector2f mousePosition(mainV.window.mapPixelToCoords({mainV.event.mouseButton.x, mainV.event.mouseButton.y}));
		if (m_piano->getSensible()){
			for(size_t i=0;i<m_piano->size();i++) {
				Key* key = m_piano->getKey(i);
				if(key->getSensible()){
					if (m_piano->keyContains(i, mousePosition)){
						m_cross->setVisible(false);
						m_tick->setVisible(false);
						if(key->getPressed()){
							bool buttonPressed = false;
							for(size_t j=0;j<key->getNoteButtons()->size();j++) { 					
								if(m_piano->keyNoteButtonContains(i, j, mousePosition)){
									key->setActiveNote(*key->getNotes()[j]);
									buttonPressed = true;
									break;
								}
							}
							if (!buttonPressed){
								key->switchPressed();
							}
						}
						else{
							key->switchPressed();
						}
					}
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
				updateAnswer();
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

void IntervalConstructionSC::afterDisplay(){
	if(m_tick->getVisible()){
		sleep(2);
		std::vector<Note> empty;
		m_piano->setPressedNotes(empty);
		generateInterval(*this);
		m_tick->setVisible(false);
	}
}

void IntervalConstructionSC::updateAnswer(){
	//delete previous interval, if it exists
	if(m_intervalAnswer != nullptr){
		delete m_intervalAnswer;
	}
	//check if the notes are valid
	if (m_piano->getPressedNotes().size() == 2){
		Interval interval;
		//check if the interval exists and save it
		if (interval.setInterval(m_piano->getPressedNotes()[0], m_piano->getPressedNotes()[1])){
			m_intervalAnswer = new Interval();
			m_intervalAnswer->setInterval(interval.getStartNote(), interval.getEndNote());
		}
		m_cross->setVisible(false);
		m_tick->setVisible(false);
	}
	else {
		m_intervalAnswer = nullptr;
	}
}

bool IntervalConstructionSC::checkAnswer(MainView &mainV){
	if(m_intervalTarget != nullptr and m_intervalAnswer != nullptr){
		if(*m_intervalAnswer == *m_intervalTarget){
			mainV.file.addAnswer(true, *m_intervalTarget, "IntervalConstruction");
			return true;
		}
		else{
			mainV.file.addAnswer(false, *m_intervalTarget, "IntervalConstruction");
			return false;
		}
	}
	else{
		mainV.file.addAnswer(false, *m_intervalTarget, "IntervalConstruction");
		return false;
	}
}


void generateInterval(IntervalConstructionSC &intervalConstructionSC){
	//delete previous interval, if it exists
	if(intervalConstructionSC.m_intervalTarget != nullptr){
		delete intervalConstructionSC.m_intervalTarget;
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
	
	intervalConstructionSC.m_intervalTarget = new Interval();
	*intervalConstructionSC.m_intervalTarget = randomInterval(randomNote(empty, signatureExclusions, octaveExclusions), nameExclusions, attributeExclusions, directionExclusions);
	
	//refresh label
	ostringstream oss;
	oss << intervalConstructionSC.m_intervalTarget->getName() << " " << intervalConstructionSC.m_intervalTarget->getAttribute() << " (desde " <<
		intervalConstructionSC.m_intervalTarget->getStartNote().getFullName() << intervalConstructionSC.m_intervalTarget->getStartNote().getOctave() << ")";
	intervalConstructionSC.m_intervalTargetLabel->setString(oss.str());
}


IntervalConstructionSC::~IntervalConstructionSC(){
	delete m_intervalTargetLabel;
	delete m_check;
	delete m_change;
	delete m_tick;
	delete m_cross;
	delete m_piano;
	delete m_intervalTarget;
	delete m_intervalAnswer;
}

