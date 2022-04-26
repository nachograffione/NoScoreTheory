#ifndef SCALEIDENTIFICATIONSC_H
#define SCALEIDENTIFICATIONSC_H

#include "Button.h"
#include "MainView.h"
#include "Piano.h"
#include "Scene.h"
#include <vector>
#include "RadioButton.h"
#include "Label.h"
#include "Scale.h"
#include "CustomSprite.h"


class ScaleIdentificationSC : public Scene {
private:
	RadioButton* m_noteNames;
	RadioButton* m_noteSignatures;
	RadioButton* m_scaleTypes;
	Button* m_change;
	Button* m_check;
	Label* m_answer;
	CustomSprite* m_tick;
	CustomSprite* m_cross;
	Piano* m_piano;
	Scale* m_scaleTarget;
	Scale* m_scaleAnswer;
	void updateAnswer();
	bool checkAnswer(MainView &mainV);
	friend void generateScale(ScaleIdentificationSC &scaleIdentificationSC);
public:
	ScaleIdentificationSC(MainView &mainV);
	void draw(MainView &mainV);
	void handler(MainView &mainV);
	void afterDisplay();
	~ScaleIdentificationSC();
};

void generateScale(ScaleIdentificationSC &scaleIdentificationSC);	//it's extern because the class constructor need it

#endif

