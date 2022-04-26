#include "GeneralSC.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "MainView.h"
#include<Windows.h>

GeneralSC::GeneralSC(MainView &mainV) {
	//init
	m_backToMenu = new Button("<- Atrás", 25, sf::Color(80,75,255));
	m_help = new Button("Ayuda", 25, sf::Color(80,75,255));
	//set
	m_backToMenu->setPosition(mainV.window.getSize().x*0.95, mainV.window.getSize().y*0.03);
	m_help->setPosition(mainV.window.getSize().x*0.95, mainV.window.getSize().y*0.09);
}


void GeneralSC::draw(MainView &mainV){
	mainV.window.draw(*m_backToMenu);
	mainV.window.draw(*m_help);
}


void GeneralSC::handler(MainView &mainV){
	switch (mainV.event.type){
	case sf::Event::Closed:
		mainV.window.close();
		break;
	case sf::Event::MouseButtonPressed:
//		sf::Vector2f mousePosition(mainV.event.mouseButton.x, mainV.event.mouseButton.y);
		sf::Vector2f mousePosition(mainV.window.mapPixelToCoords({mainV.event.mouseButton.x, mainV.event.mouseButton.y}));
		if(m_backToMenu->contains(mousePosition)){
			mainV.setScene(mainV.startSC);
		}
		else if(m_help->contains(mousePosition)){
			#ifdef __WIN32__
			ShellExecute(NULL,"open","misc\\UserManual.pdf","misc\\UserManual.pdf",NULL,SW_NORMAL);
			#else
			system("xdg-open misc\\UserManual.pdf &");
			#endif
		}
		break;
	}
}


void GeneralSC::afterDisplay(){
}

GeneralSC::~GeneralSC(){
	delete m_backToMenu;
	delete m_help;
}
