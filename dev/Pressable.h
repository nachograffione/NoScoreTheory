#ifndef PRESSABLE_H
#define PRESSABLE_H
#include <SFML/Graphics.hpp>
#include "Sensible.h"

class Pressable : public Sensible{
protected:
	bool m_isPressed;
//	virtual void focusOn();
//	virtual void focusOff();
	virtual void pressOnDrawer() = 0;
	virtual void pressOffDrawer() = 0;
	
public:
	Pressable();
	bool getPressed();
//	bool getFocus();
	void setPressed(bool isPressed);
//	void setFocus(bool isFocus);
	void switchPressed();
//	void switchFocus();
//	bool clickChecker(const sf::Event &event);
};

#endif

