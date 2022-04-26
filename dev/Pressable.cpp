#include "Pressable.h"
#include <iostream>

Pressable::Pressable() : m_isPressed(false){
}

bool Pressable::getPressed(){
	return m_isPressed;
}

void Pressable::setPressed(bool isPressed){
	m_isPressed = isPressed;
	if(m_isPressed){
		pressOnDrawer();
	}
	else{
		pressOffDrawer();
	}
}

void Pressable::switchPressed(){
	setPressed(!m_isPressed);
}
