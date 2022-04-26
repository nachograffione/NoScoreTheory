#ifndef SCALECONSTRUCTIONSC_H
#define SCALECONSTRUCTIONSC_H

#include "Label.h"
#include "Button.h"
#include "CustomSprite.h"
#include "Piano.h"
#include "Scale.h"
#include "MainView.h"
#include "Scene.h"

class ScaleConstructionSC: public Scene {
private:
	Label* m_scaleTargetLabel;
	Button* m_check;
	Button* m_change;
	CustomSprite* m_tick;
	CustomSprite* m_cross;
	Piano* m_piano;
	Scale* m_scaleTarget;
	Scale* m_scaleAnswer;
	void updateAnswer();
	bool checkAnswer(MainView &mainV);
	friend void generateScale(ScaleConstructionSC &ScaleConstructionSC);
public:
	ScaleConstructionSC(MainView &mainV);
	void draw(MainView &mainV);
	void handler(MainView &mainV);
	void afterDisplay();
	~ScaleConstructionSC();
};

void generateScale(ScaleConstructionSC &ScaleConstructionSC);	//it's extern because the class constructor need it

#endif

