#ifndef INTERVALCONSTRUCTIONSC_H
#define INTERVALCONSTRUCTIONSC_H
#include "Label.h"
#include "Button.h"
#include "CustomSprite.h"
#include "Piano.h"
#include "Interval.h"
#include "MainView.h"
#include "Scene.h"

class IntervalConstructionSC: public Scene {
private:
	Label* m_intervalTargetLabel;
	Button* m_check;
	Button* m_change;
	CustomSprite* m_tick;
	CustomSprite* m_cross;
	Piano* m_piano;
	Interval* m_intervalTarget;
	Interval* m_intervalAnswer;
	void updateAnswer();
	bool checkAnswer(MainView &mainV);
	friend void generateInterval(IntervalConstructionSC &IntervalConstructionSC);
public:
	IntervalConstructionSC(MainView &mainV);
	void draw(MainView &mainV);
	void handler(MainView &mainV);
	void afterDisplay();
	~IntervalConstructionSC();
};

void generateInterval(IntervalConstructionSC &IntervalConstructionSC);	//it's extern because the class constructor need it

#endif

