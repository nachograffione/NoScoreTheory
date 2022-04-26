#ifndef STARTSC_H
#define STARTSC_H

#include "Button.h"
#include "MainView.h"
#include "Scene.h"

class StartSC : public Scene {
private:
	Button *m_intervalIdentificationEnter;
	Button *m_intervalConstructionEnter;
	Button *m_scaleIdentificationEnter;
	Button *m_scaleConstructionEnter;
public:
	StartSC(MainView &mainV);
	void draw(MainView &mainV);
	void handler(MainView &smainV);
	void afterDisplay();
	~StartSC();
};

#endif

