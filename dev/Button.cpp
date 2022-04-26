#include "Button.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Pressable.h"
#include <string>
#include "TextEntity.h"
#include "RoundedRectangleShape.h"


Button::Button(std::string text, int size, sf::Color color) : TextEntity<sf::RoundedRectangleShape>(text, size, color) {
	setPressed(false);
}

void Button::pressOnDrawer(){
	m_shape->setOutlineThickness(0.07);
}
void Button::pressOffDrawer(){
	m_shape->setOutlineThickness(0);
}
