#include "CustomSprite.h"
#include <string>
#include <SFML/Graphics.hpp>

CustomSprite::CustomSprite() {
	m_texture = new sf::Texture();
	m_sprite = new sf::Sprite();
}

void CustomSprite::setPath(std::string path){
	m_texture->loadFromFile(path);
	m_sprite->setTexture(*m_texture);
	m_sprite->setOrigin(m_sprite->getLocalBounds().width * 0.5, m_sprite->getLocalBounds().height * 0.5);
}

CustomSprite::~CustomSprite() {
	delete m_texture;
	delete m_sprite;
}
	
void CustomSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	if(getVisible()){
		states.transform *= getTransform();
		target.draw(*m_sprite, states);
	}
}
