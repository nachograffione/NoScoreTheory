#include "RadioButton.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "GroupedButton.h"

RadioButton::RadioButton(){
}

RadioButton::RadioButton(std::vector<std::string> texts, int size, int offset, sf::Color color) {
	//init buttons
	for(std::string text : texts){
		Button* buttonPtr = new GroupedButton(text, size, color);
		m_buttons.push_back(buttonPtr);
	}
	//set positions
	sf::Vector2f position = this->getPosition();
	for(size_t i=0;i<m_buttons.size();i++) { 
		m_buttons[i]->setPosition(position.x, position.y + offset*i);
	}
	//set first button as active, to avoid read garbage at anytime
	m_buttons[0]->setPressed(true);
}


void RadioButton::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	if (m_isVisible){
		states.transform *= getTransform();
		for(size_t i=0;i<m_buttons.size();i++) {
			target.draw(*m_buttons[i], states);
		}
	}
}

sf::FloatRect RadioButton::getButtonGlobalBounds(int position){
	//get button bounds
	sf::FloatRect bounds = m_buttons[position]->getGlobalBounds();
	//apply container transformations
	bounds = this->getTransform().transformRect(bounds);
	return bounds;
}


bool RadioButton::buttonContains(int buttonPosition, const sf::Vector2f &position){
	return getButtonGlobalBounds(buttonPosition).contains(position);
}


void RadioButton::setActiveButton(int position){
	for(size_t i=0;i<m_buttons.size();i++) { 
		if(i == position){
			m_buttons[i]->setPressed(true);
		}
		else{
			m_buttons[i]->setPressed(false);
		}
	}
}

Button* RadioButton::getButton(int position){
	return m_buttons[position];
}


Button* RadioButton::getActiveButton(){
	for(Button* button : m_buttons){
		if (button->getPressed()){
			return button;
		}
	}
}

int RadioButton::getActiveButtonPosition(){
	for(size_t i=0;i<m_buttons.size();i++) { 
		if (m_buttons[i]->getPressed()){
			return i;
		}
	}
}

int RadioButton::size(){
	return m_buttons.size();
}

RadioButton::~RadioButton(){
	for(size_t i=0;i<m_buttons.size();i++) { 
		delete m_buttons[i];
	}
}
