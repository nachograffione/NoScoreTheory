#ifndef MAINSC_H
#define MAINSC_H

#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "FileManager.h"

//////////Sleep function
void sleep(unsigned seconds);
//////////Sleep function


class MainView {
private:
	Scene* activeSC;
	Scene* nextSC;
public:
	//attributes
	sf::RenderWindow window;
	sf::Event event;
	FileManager file;
	
	//scenes
	Scene* generalSC;
	Scene* startSC;
	Scene* intervalIdentificationSC;
	Scene* intervalConstructionSC;
	Scene* scaleIdentificationSC;
	Scene* scaleConstructionSC;
	
	//methods
	MainView();
	void game();
	void setScene(Scene* newNextSC);
	~MainView();
};

#endif

