#include "TextEntity.h"
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.h"


template<typename ShapeType>
TextEntity<ShapeType>::TextEntity(std::string text, int size, sf::Color color) {
	//init
	m_font = new sf::Font;
	m_text = new sf::Text;
	m_shape = new ShapeType;
	m_color = new sf::Color(color);
	
	//set text
	m_text->setString(text);
	if(!m_font->loadFromFile("fonts\\KOMTXT__.ttf")){
		std::cout << "Unable to load font." << std::endl;
	}
	m_text->setFont(*m_font);
	m_text->setCharacterSize(size);
	m_text->setFillColor(sf::Color::Black);
	m_text->setStyle(sf::Text::Bold);
	
	
	m_shape->setFillColor(*m_color);
	centerTextAndShape(*m_shape);
}

template<typename ShapeType>
sf::Text TextEntity<ShapeType>::getText(){
	return *m_text;
}

template<typename ShapeType>
std::string TextEntity<ShapeType>::getString(){
	return m_text->getString();
}

template<typename ShapeType>
sf::FloatRect TextEntity<ShapeType>::getGlobalBounds() const{
	//get shape bounds
	sf::FloatRect bounds = m_shape->getGlobalBounds();		//the bounds used are global because it needs the bounds after the transformations (scale)
	//align bounds (because the shape's origin is at center)
	bounds.left = m_shape->getPosition().x - bounds.width/2.f;
	bounds.top = m_shape->getPosition().y - bounds.height/2.f;
	//apply container transformations
	bounds = this->getTransform().transformRect(bounds);
	return bounds;
}

template<typename ShapeType>
bool TextEntity<ShapeType>::contains(const sf::Vector2f &point) const{
	return getGlobalBounds().contains(point);
}

template<typename ShapeType>
void TextEntity<ShapeType>::setString(std::string string){
	m_text->setString(string);
	//update shape
	centerTextAndShape(*m_shape);
}

template<typename ShapeType>
sf::Color TextEntity<ShapeType>::getColor(){
	return *m_color;
}

template<typename ShapeType>
void TextEntity<ShapeType>::setColor(sf::Color color){
	*m_color = color;
}

template<typename ShapeType>
void TextEntity<ShapeType>::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	target.draw(*m_shape, states);
	target.draw(*m_text, states);
}

template<typename ShapeType>
TextEntity<ShapeType>::~TextEntity(){
	delete m_shape;
	delete m_text;
	delete m_font;
	delete m_color;
}

//Functions only for a specialization of template class
template<>
void TextEntity<sf::CircleShape>::centerTextAndShape(sf::CircleShape &shape){
	//set text origin at center
	sf::FloatRect textBounds = m_text->getLocalBounds();
	//explicit left and top is for take the left-top point of glyph bounds (which is visualized) instead of
	//text bounds (which is larger than the other) as reference
	m_text->setOrigin(textBounds.left + textBounds.width/2.f, textBounds.top + textBounds.height/2.f);
	
	//circle
	m_shape->setRadius(1);
	m_shape->setPointCount(50);
	m_shape->scale(textBounds.width*0.65, textBounds.height*0.8);	//it isn´t 0.5 because it needs an extra size
	
	//set circle origin at center
	sf::FloatRect shapeBounds = m_shape->getLocalBounds();		//the bounds used are local because setOrigin IGNORES TRANSFORMATIONS!
	m_shape->setOrigin(shapeBounds.width/2, shapeBounds.height/2);
	
	//join them
	m_shape->setPosition(m_text->getPosition());
}

template<>
void TextEntity<sf::RectangleShape>::centerTextAndShape(sf::RectangleShape &shape){
	//set text origin at center
	sf::FloatRect textBounds = m_text->getLocalBounds();
	//explicit left and top is for take the left-top point of glyph bounds (which is visualized) instead of
	//text bounds (which is larger than the other) as reference
	m_text->setOrigin(textBounds.left + textBounds.width/2.f, textBounds.top + textBounds.height/2.f);
	
	//rectangle
	m_shape->setSize(sf::Vector2f(1,1));
	m_shape->setScale(textBounds.width*1.4, textBounds.height*1.4);	//it isn´t 1 because it needs an extra size
	
	//set rectangle origin at center
	sf::FloatRect shapeBounds = m_shape->getLocalBounds();		//the bounds used are local because setOrigin IGNORES TRANSFORMATIONS!
	m_shape->setOrigin(shapeBounds.width/2.f, shapeBounds.height/2.f);
	
	//join them
	m_shape->setPosition(m_text->getPosition());
}

template<>
void TextEntity<sf::RoundedRectangleShape>::centerTextAndShape(sf::RoundedRectangleShape &shape){
	//set text origin at center
	sf::FloatRect textBounds = m_text->getLocalBounds();
	//explicit left and top is for take the left-top point of glyph bounds (which is visualized) instead of
	//text bounds (which is larger than the other) as reference
	m_text->setOrigin(textBounds.left + textBounds.width/2.f, textBounds.top + textBounds.height/2.f);
	
	//rectangle
	m_shape->setCornersRadius(((textBounds.width+textBounds.height)/2.f) * 0.14);	//average with width and height, and a coefficient
	m_shape->setCornerPointCount(15);
	m_shape->setSize(sf::Vector2f(textBounds.width*1.2, textBounds.height*1.7));	//setScale generates problems
	
	//set rectangle origin at center
	sf::FloatRect shapeBounds = m_shape->getLocalBounds();		//the bounds used are local because setOrigin IGNORES TRANSFORMATIONS!
	m_shape->setOrigin(shapeBounds.width/2.f, shapeBounds.height/2.f);
	
	//join them
	m_shape->setPosition(m_text->getPosition());
}


//Necessary instanciations of template class
template class TextEntity<sf::CircleShape>;
template class TextEntity<sf::RectangleShape>;
template class TextEntity<sf::RoundedRectangleShape>;
