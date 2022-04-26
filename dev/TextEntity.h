#ifndef TEXTENTITY_H
#define TEXTENTITY_H
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Entity.h"

template<typename ShapeType>
class TextEntity : public Entity, public sf::Drawable, public sf::Transformable {
private:
	void centerTextAndShape(ShapeType &shape);
protected:
	ShapeType* m_shape;
	sf::Text* m_text;
	sf::Font* m_font;
	sf::Color* m_color;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	TextEntity(std::string text, int size, sf::Color color);
	sf::FloatRect getGlobalBounds() const;
	bool contains(const sf::Vector2f &point) const;
	sf::Text getText();
	ShapeType getShape();
	std::string getString();
	sf::Color getColor();
	void setString(std::string string);
	void setColor(sf::Color);
	~TextEntity();
};



#endif

