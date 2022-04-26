#ifndef INTERVALIDENTIFICATIONSC_H
#define INTERVALIDENTIFICATIONSC_H

#include "Button.h"
#include "MainView.h"
#include "Piano.h"
#include "Scene.h"
#include <vector>
#include "RadioButton.h"
#include "Label.h"
#include "Interval.h"
#include "CustomSprite.h"


class IntervalIdentificationSC : public Scene {
private:
	RadioButton* m_intervalNames;
	RadioButton* m_intervalAttributes;
	Button* m_change;
	Button* m_check;
	Label* m_answer;
	CustomSprite* m_tick;
	CustomSprite* m_cross;
	Piano* m_piano;
	Interval* m_intervalTarget;
	Interval* m_intervalAnswer;
	void updateAnswer();
	bool checkAnswer(MainView &mainV);
	friend void generateInterval(IntervalIdentificationSC &intervalIdentificationSC);
public:
	IntervalIdentificationSC(MainView &mainV);
	void draw(MainView &mainV);
	void handler(MainView &mainV);
	void afterDisplay();
	~IntervalIdentificationSC();
};

void generateInterval(IntervalIdentificationSC &intervalIdentificationSC);	//it's extern because the class constructor need it

#endif

