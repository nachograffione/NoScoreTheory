#ifndef GROUPEDBUTTON_H
#define GROUPEDBUTTON_H
#include "Button.h"

class GroupedButton : public Button{
private:
	void pressOnDrawer();
	void pressOffDrawer();
public:
	GroupedButton(std::string text, int size, sf::Color color);
};

#endif

