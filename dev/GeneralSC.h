#ifndef GENERALSC_H
#define GENERALSC_H

#include <SFML/Window.hpp>
#include "MainView.h"
#include "Scene.h"
#include "Button.h"
#include "Piano.h"


class GeneralSC : public Scene {
private:
	Button* m_backToMenu;
	Button* m_help;
	Piano* m_piano;
public:
	GeneralSC(MainView &mainV);
	void draw(MainView &mainV);
	void handler(MainView &mainV);
	void afterDisplay();
	~GeneralSC();
};

#endif

