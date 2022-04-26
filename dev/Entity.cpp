#include "Entity.h"

Entity::Entity() : m_isVisible(true){
	
}

void Entity::switchVisible(){
	setVisible(!m_isVisible);
}


void Entity::setVisible(bool isVisible){
	m_isVisible = isVisible;
}


bool Entity::getVisible() const{
	return m_isVisible;
}
