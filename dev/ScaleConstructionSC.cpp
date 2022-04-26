#include "ScaleConstructionSC.h"
#include "Globals.h"
#include "MainView.h"
#include "Piano.h"
#include <algorithm>
#include <string>
#include <tuple>
#include <iostream>
#include "Scale.h"
#include "Note.h"
#include "CustomSprite.h"

ScaleConstructionSC::ScaleConstructionSC(MainView &mainV) :
	m_scaleTargetLabel(nullptr),
	m_check(nullptr),
	m_change(nullptr),
	m_tick(nullptr),
	m_cross(nullptr),
	m_piano(nullptr),
	m_scaleTarget(nullptr),
	m_scaleAnswer(nullptr)
{
	//init
	m_scaleTargetLabel = new Label("", 30, sf::Color(230,150,150));
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
	m_scaleTargetLabel->setString("<>");	//update answer
	
	//set positions
	sf::FloatRect pianoBounds = m_piano->getGlobalBounds();
	
	m_scaleTargetLabel->setPosition(mainV.window.getSize().x * 0.5, mainV.window.getSize().y * 0.25);
	m_check->setPosition(mainV.window.getSize().x * 0.5, mainV.window.getSize().y * 0.35);
	
	m_change->setPosition(mainV.window.getSize().x * 0.5, mainV.window.getSize().y - pianoBounds.height - 50);
	m_piano->setPosition((mainV.window.getSize().x - pianoBounds.width)*0.5, mainV.window.getSize().y - pianoBounds.height - 10);
	
	m_tick->setPosition(mainV.window.getSize().x * 0.8, mainV.window.getSize().y * 0.25);
	m_cross->setPosition(mainV.window.getSize().x * 0.8, mainV.window.getSize().y * 0.25);
	
	generateScale(*this);
}


void ScaleConstructionSC::draw(MainView &mainV){
	mainV.window.draw(*m_scaleTargetLabel);
	mainV.window.draw(*m_check);
	mainV.window.draw(*m_change);
	mainV.window.draw(*m_piano);
	mainV.window.draw(*m_tick);
	mainV.window.draw(*m_cross);
}

void ScaleConstructionSC::handler(MainView &mainV){
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
			generateScale(*this);
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


void ScaleConstructionSC::afterDisplay(){
	if(m_tick->getVisible()){
		sleep(2);
		std::vector<Note> empty;
		m_piano->setPressedNotes(empty);
		generateScale(*this);
		m_tick->setVisible(false);
	}
}

void ScaleConstructionSC::updateAnswer(){
	//delete previous scale, if it exists
	if(m_scaleAnswer != nullptr){
		delete m_scaleAnswer;
	}
	//check if the notes are valid
	if (m_piano->getPressedNotes().size() == 7){
		//shift octave if it's necessary
		vector<Note> pianoPressedNotes = m_piano->getPressedNotes();
		if(pianoPressedNotes[0].getOctave() != 3){
			int diference = 3 - pianoPressedNotes[0].getOctave();
			for(size_t i=0;i<pianoPressedNotes.size();i++) { 
				pianoPressedNotes[i].shiftOctave(diference);
			}
		}
		Scale scale;
		//check if the scale exists and save it
		if (scale.setScale(pianoPressedNotes)){
			m_scaleAnswer = new Scale();
			m_scaleAnswer->setScale(scale);
		}
		m_cross->setVisible(false);
		m_tick->setVisible(false);
	}
	else{
		m_scaleAnswer = nullptr;
	}
}

bool ScaleConstructionSC::checkAnswer(MainView &mainV){
	if(m_scaleTarget != nullptr and m_scaleAnswer != nullptr){
		if(*m_scaleAnswer == *m_scaleTarget){
			mainV.file.addAnswer(true, *m_scaleTarget, "ScaleConstruction");
			return true;
		}
		else{
			mainV.file.addAnswer(false, *m_scaleTarget, "ScaleConstruction");
			return false;
		}
	}
	else{
		mainV.file.addAnswer(false, *m_scaleTarget, "ScaleConstruction");
		return false;
	}
}


void generateScale(ScaleConstructionSC &scaleConstructionSC){
	//delete previous scale, if it exists
	if(scaleConstructionSC.m_scaleTarget != nullptr){
		delete scaleConstructionSC.m_scaleTarget;
	}
	//generate new scale and assign to the attribute
	std::vector<std::string> emptyString;
	std::vector<Note> emptyNote;
	
	scaleConstructionSC.m_scaleTarget = new Scale(randomScale(emptyNote, emptyString));
	
	//refresh label
	scaleConstructionSC.m_scaleTargetLabel->setString(scaleConstructionSC.m_scaleTarget->getFullName());
}


ScaleConstructionSC::~ScaleConstructionSC(){
	delete m_scaleTargetLabel;
	delete m_check;
	delete m_change;
	delete m_tick;
	delete m_cross;
	delete m_piano;
	delete m_scaleTarget;
	delete m_scaleAnswer;
}

