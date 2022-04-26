#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Pressable.h"
#include "TextEntity.h"
#include <vector>
#include "RoundedRectangleShape.h"


class Button : public TextEntity<sf::RoundedRectangleShape>, public Pressable {
private:
	virtual void pressOnDrawer();
	virtual void pressOffDrawer();
public:
	Button(std::string text, int size, sf::Color color);
};

#endif

