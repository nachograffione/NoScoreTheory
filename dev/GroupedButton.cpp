#include "GroupedButton.h"

GroupedButton::GroupedButton(std::string text, int size, sf::Color color) : Button(text, size, color) {	
	setPressed(false);
}


void GroupedButton::pressOnDrawer(){
	m_shape->setOutlineThickness(0.07);
	m_shape->setOutlineColor(sf::Color::Black);
	m_shape->setFillColor(*m_color);						//return to original color
}
void GroupedButton::pressOffDrawer(){
	m_shape->setOutlineThickness(0);
	m_shape->setFillColor(*m_color);											//return to original color
	m_shape->setFillColor(m_shape->getFillColor()*sf::Color(255,255,255,100));	//apply transparency
}
