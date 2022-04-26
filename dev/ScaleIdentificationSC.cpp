#include "ScaleIdentificationSC.h"
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

ScaleIdentificationSC::ScaleIdentificationSC(MainView &mainV) :
	m_scaleTarget(nullptr),
	m_scaleAnswer(nullptr),
	m_noteNames(nullptr),
	m_noteSignatures(nullptr),
	m_scaleTypes(nullptr),
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
		std::vector<string> noteSignaturesVector;
		std::vector<string> scaleTypesVector;
		std::string scaleName;
		for(size_t i=0;i<glob.SIGNATURES_NAMES.size();i++) { 
			if (glob.SIGNATURES_NAMES[i] != "bb" and glob.SIGNATURES_NAMES[i] != "x"){
				if (glob.SIGNATURES_NAMES[i] == ""){
					noteSignaturesVector.push_back("<natural>");
				}
				else{
					noteSignaturesVector.push_back(glob.SIGNATURES_NAMES[i]);
				}
			}
		}
		for(size_t i = 0; i < glob.SCALES_TYPES.size(); i++){
			std::tie(scaleName, std::ignore) = glob.SCALES_TYPES[i];
			scaleTypesVector.push_back(scaleName);
		}
		m_noteNames = new RadioButton(glob.NOTES_NAMES, 32, 65, sf::Color(0,180,0));
		m_noteSignatures = new RadioButton(noteSignaturesVector, 32, 65, sf::Color(0,180,0));
		m_scaleTypes = new RadioButton(scaleTypesVector, 32, 65, sf::Color(0,180,0));
	};
	
	//set several things
	m_tick->setPath("img\\tick.png");
	m_tick->setScale(0.3, 0.3);
	m_tick->setVisible(false);
	m_cross->setPath("img\\cross.png");
	m_cross->setScale(0.3, 0.3);
	m_cross->setVisible(false);
	m_answer->setString(m_noteNames->getActiveButton()->getString() + " " + m_noteSignatures->getActiveButton()->getString() +
						" " + m_scaleTypes->getActiveButton()->getString());//update answer
	m_piano->setSensible(false);
	
	//set positions
	sf::FloatRect pianoBounds = m_piano->getGlobalBounds();
	
	m_piano->setPosition((mainV.window.getSize().x - pianoBounds.width)*0.5, mainV.window.getSize().y - pianoBounds.height - 10);
	m_change->setPosition(mainV.window.getSize().x * 0.5, mainV.window.getSize().y - pianoBounds.height - 50);
	
	m_noteNames->setPosition(mainV.window.getSize().x * 0.1, mainV.window.getSize().y * 0.08);
	m_noteSignatures->setPosition(mainV.window.getSize().x * 0.2, mainV.window.getSize().y * 0.08);
	m_scaleTypes->setPosition(mainV.window.getSize().x * 0.38, mainV.window.getSize().y * 0.08);
	
	m_check->setPosition(mainV.window.getSize().x * 0.65, mainV.window.getSize().y * 0.35);
	m_answer->setPosition(mainV.window.getSize().x * 0.65, mainV.window.getSize().y * 0.25);
	m_tick->setPosition(mainV.window.getSize().x * 0.85, mainV.window.getSize().y * 0.25);
	m_cross->setPosition(mainV.window.getSize().x * 0.85, mainV.window.getSize().y * 0.25);
	
	generateScale(*this);
}


void ScaleIdentificationSC::draw(MainView &mainV){
	mainV.window.draw(*m_piano);
	mainV.window.draw(*m_change);
	mainV.window.draw(*m_tick);
	mainV.window.draw(*m_cross);
	mainV.window.draw(*m_check);
	mainV.window.draw(*m_answer);
	mainV.window.draw(*m_noteNames);
	mainV.window.draw(*m_noteSignatures);
	mainV.window.draw(*m_scaleTypes);
}

void ScaleIdentificationSC::handler(MainView &mainV){
	switch (mainV.event.type){
	case sf::Event::MouseButtonPressed:
//		sf::Vector2f mousePosition(mainV.event.mouseButton.x, mainV.event.mouseButton.y);
		sf::Vector2f mousePosition(mainV.window.mapPixelToCoords({mainV.event.mouseButton.x, mainV.event.mouseButton.y}));
		if (m_noteNames->getSensible()){
			for(size_t i=0;i<m_noteNames->size();i++) {
				if(m_noteNames->buttonContains(i, mousePosition)){
					m_noteNames->setActiveButton(i);
					updateAnswer();
					break;
				}
			}
		}
		if (m_noteSignatures->getSensible()){
			for(size_t i=0;i<m_noteSignatures->size();i++) {
				if(m_noteSignatures->buttonContains(i, mousePosition)){
					m_noteSignatures->setActiveButton(i);
					updateAnswer();
					break;
				}
			}
		}
		if (m_scaleTypes->getSensible()){
			for(size_t i=0;i<m_scaleTypes->size();i++) {
				if(m_scaleTypes->buttonContains(i, mousePosition)){
					m_scaleTypes->setActiveButton(i);
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
				generateScale(*this);
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

void ScaleIdentificationSC::afterDisplay(){
	if(m_tick->getVisible()){
		sleep(2);
		std::vector<Note> empty;
		m_piano->setPressedNotes(empty);
		generateScale(*this);
		m_tick->setVisible(false);
	}
}

void ScaleIdentificationSC::updateAnswer(){
	std::string noteNameButton = m_noteNames->getActiveButton()->getString();
	std::string noteSignatureButton = m_noteSignatures->getActiveButton()->getString();
	std::string scaleTypeButton = m_scaleTypes->getActiveButton()->getString();
	
	//if it's used, change string for logic management
	if(noteSignatureButton == "<natural>"){
		noteSignatureButton = "";
	}
	
	//check if the scale exist
	Note fundamental;
	Scale scale;
	fundamental.setNote(noteNameButton, noteSignatureButton, 3);
	if(scale.setScale(fundamental, scaleTypeButton)){
		m_answer->setString(noteNameButton + noteSignatureButton + " " + scaleTypeButton);
		//delete previous scale, if it exists
		if(m_scaleAnswer != nullptr){
			delete m_scaleAnswer;
		}
		//save new scale
		m_scaleAnswer = new Scale();
		m_scaleAnswer->setScale(scale.getFundamental(), scale.getType());
	}
	else{
		m_answer->setString("<Escala no valida>");
		if(m_scaleAnswer != nullptr){
			delete m_scaleAnswer;
		}
		m_scaleAnswer = nullptr;
	}
	m_cross->setVisible(false);
	m_tick->setVisible(false);
}

bool ScaleIdentificationSC::checkAnswer(MainView &mainV){
	if(m_scaleTarget != nullptr and m_scaleAnswer != nullptr){
		if(*m_scaleAnswer == *m_scaleTarget){
			mainV.file.addAnswer(true, *m_scaleTarget, "ScaleIdentification");
			return true;
		}
		else{
			mainV.file.addAnswer(false, *m_scaleTarget, "ScaleIdentification");
			return false;
		}
	}
	else{
		mainV.file.addAnswer(false, *m_scaleTarget, "ScaleIdentification");
		return false;
	}
}


void generateScale(ScaleIdentificationSC &scaleIdentificationSC){
	//delete previous scale, if it exists
	if(scaleIdentificationSC.m_scaleTarget != nullptr){
		delete scaleIdentificationSC.m_scaleTarget;
	}
	//generate new scale and assign to the attribute
	std::vector<std::string> emptyString;
	std::vector<Note> emptyNote;
	
	scaleIdentificationSC.m_scaleTarget = new Scale();
	scaleIdentificationSC.m_scaleTarget->setScale(randomScale(emptyNote, emptyString));
	
	
	//refresh piano
	scaleIdentificationSC.m_piano->setPressedNotes(scaleIdentificationSC.m_scaleTarget->getNotes());
}


ScaleIdentificationSC::~ScaleIdentificationSC(){
	delete m_noteNames;
	delete m_noteSignatures;
	delete m_scaleTypes;
	delete m_piano;
	delete m_change;
	delete m_tick;
	delete m_cross;
	delete m_check;
	delete m_answer;
	delete m_scaleTarget;
	delete m_scaleAnswer;
}
