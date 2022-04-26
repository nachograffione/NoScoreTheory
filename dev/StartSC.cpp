#include "StartSC.h"
#include "MainView.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

StartSC::StartSC(MainView &mainV){
	//init
	m_intervalIdentificationEnter = new Button("Identificar\nintervalos", 40, sf::Color(80,75,255));
	m_intervalConstructionEnter = new Button("Construir\nintervalos", 40, sf::Color(80,75,255));
	m_scaleIdentificationEnter = new Button("Identificar\nescalas", 40, sf::Color(80,75,255));
	m_scaleConstructionEnter = new Button("Construir\nescalas", 40, sf::Color(80,75,255));
	//set
	m_intervalIdentificationEnter->setPosition(mainV.window.getSize().x * 0.35, mainV.window.getSize().y * 0.3);
	m_intervalConstructionEnter->setPosition(mainV.window.getSize().x * 0.65, mainV.window.getSize().y * 0.3);
	m_scaleIdentificationEnter->setPosition(mainV.window.getSize().x * 0.35, mainV.window.getSize().y * 0.6);
	m_scaleConstructionEnter->setPosition(mainV.window.getSize().x * 0.65, mainV.window.getSize().y * 0.6);
}


void StartSC::draw(MainView &mainV){
	mainV.window.draw(*m_intervalIdentificationEnter);
	mainV.window.draw(*m_intervalConstructionEnter);
	mainV.window.draw(*m_scaleIdentificationEnter);
	mainV.window.draw(*m_scaleConstructionEnter);
}


void StartSC::handler(MainView &mainV){
	switch (mainV.event.type){
	case sf::Event::MouseButtonPressed:
//		sf::Vector2f mousePosition(mainV.event.mouseButton.x, mainV.event.mouseButton.y);
		sf::Vector2f mousePosition(mainV.window.mapPixelToCoords({mainV.event.mouseButton.x, mainV.event.mouseButton.y}));
		if(m_intervalIdentificationEnter->contains(mousePosition)){
			mainV.setScene(mainV.intervalIdentificationSC);
		}
		else if(m_intervalConstructionEnter->contains(mousePosition)){
			mainV.setScene(mainV.intervalConstructionSC);
		}
		else if(m_scaleIdentificationEnter->contains(mousePosition)){
			mainV.setScene(mainV.scaleIdentificationSC);
		}
		else if(m_scaleConstructionEnter->contains(mousePosition)){
			mainV.setScene(mainV.scaleConstructionSC);
		}
		break;
	}
}


void StartSC::afterDisplay(){
}

StartSC::~StartSC(){
	delete m_intervalIdentificationEnter;
	delete m_intervalConstructionEnter;
	delete m_scaleIdentificationEnter;
	delete m_scaleConstructionEnter;
}
