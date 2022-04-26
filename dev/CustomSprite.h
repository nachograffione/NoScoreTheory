#ifndef IMAGE_H
#define IMAGE_H
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <string>

class CustomSprite : public Entity, public sf::Drawable, public sf::Transformable{
private:
	sf::Texture* m_texture;
	sf::Sprite* m_sprite;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	CustomSprite();
	void setPath(std::string path);
	~CustomSprite();
};

#endif

