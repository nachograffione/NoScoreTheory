#ifndef LABEL_H
#define LABEL_H
#include <SFML/Graphics.hpp>
#include "TextEntity.h"
#include <string>

class Label : public TextEntity<sf::RectangleShape> {
public:
	Label(std::string text, int size, sf::Color color);
//	sf::FloatRect getBounds();		
};

#endif

