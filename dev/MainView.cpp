#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "MainView.h"
#include "GeneralSC.h"
#include "Globals.h"
#include "IntervalIdentificationSC.h"
#include "ScaleIdentificationSC.h"
#include "StartSC.h"
#include "IntervalConstructionSC.h"
#include "ScaleConstructionSC.h"

#include <windows.h>
//////////Sleep function
void sleep(unsigned seconds) {
	Sleep(seconds*1000);
//	clock_t begin, end;
//	double elapsed_secs;
//	
//	begin = clock();
//	do{
//		end = clock();
//		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//	} while(elapsed_secs < seconds);
}
//////////Sleep function

MainView::MainView() :
	//1360, 730
	//1750, 900
	window(sf::VideoMode(1360, 730), "NoScoreTheory", sf::Style::Titlebar|sf::Style::Close|sf::Style::Resize, 
		   sf::ContextSettings(0, 0, 7, 1, 1, sf::ContextSettings::Attribute::Default, false)),		//This is for set antialiasing to 7
	file("misc\\answers.txt"),
	activeSC(nullptr),
	nextSC(nullptr),
	generalSC(nullptr),
	startSC(nullptr),
	intervalIdentificationSC(nullptr),
	intervalConstructionSC(nullptr),
	scaleIdentificationSC(nullptr),
	scaleConstructionSC(nullptr)
{
	//window aditional settings
	window.setFramerateLimit(60);
	
	//init scenes
	generalSC = new GeneralSC(*this);
	startSC = new StartSC(*this);
	intervalIdentificationSC = new IntervalIdentificationSC(*this);
	intervalConstructionSC = new IntervalConstructionSC(*this);
	scaleIdentificationSC = new ScaleIdentificationSC(*this);
	scaleConstructionSC = new ScaleConstructionSC(*this);
	
	
	//set first scene
	activeSC = startSC;
	nextSC = startSC;
}


void MainView::game(){
	while (window.isOpen()){
		// hand events
		while (window.pollEvent(event)){
			generalSC->handler(*this);
			activeSC->handler(*this);
		}
	
		//draw and display
		window.clear(sf::Color(200,220,255));
		generalSC->draw(*this);
		activeSC->draw(*this);
		window.display();
		
		activeSC->afterDisplay();
		
		//set nextScene
		if(nextSC != activeSC){
			activeSC = nextSC;
		}
	}
}

void MainView::setScene(Scene* scene){
	nextSC = scene;
}


MainView::~MainView(){
	file.saveSession();
	
	delete activeSC;
	delete nextSC;
	//scenes
	delete generalSC;
	delete startSC;
	delete intervalIdentificationSC;
	delete intervalConstructionSC;
	delete scaleIdentificationSC;
	delete scaleConstructionSC;
}


