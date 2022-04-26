#include "Piano.h"
#include <string>
#include <iostream>
#include <SFML/System.hpp>
#include "Globals.h"
#include <tuple>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Key.h"
#include <vector>
#include <algorithm>
#include "Note.h"

Piano::Piano(Note firstNote, Note endNote) {
	//init keys
	int keysAmount = endNote.getPosition()-firstNote.getPosition();
	for(int i=0;i<keysAmount;i++) { 
		Key* keyPtr = new Key(firstNote.getPosition() + i);
		m_keys.push_back(keyPtr);
	}
	//set positions
	float whiteKeyWidth = 62;	//taken from key constructor
	float xPosition = 0;
	for(size_t i=0;i<m_keys.size();i++) {
		if(i != 0){
			switch(m_keys[i]->getShapeType()){
			case whiteLeft:
				xPosition += whiteKeyWidth;
				break;
			case whiteRight:
				xPosition += whiteKeyWidth*0.25;
				break;
			case whiteCenter:
				xPosition += whiteKeyWidth*0.25;
				break;
			case black:
				xPosition += whiteKeyWidth*0.75;
				break;
			}
		}
		m_keys[i]->setPosition(xPosition, 0);
	}
}

void Piano::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	for(size_t i=0;i<m_keys.size();i++) {
		target.draw(*m_keys[i], states);
	}
}

int Piano::size(){
	return m_keys.size();
}

Key* Piano::getKey(int position){
	return m_keys[position];
}


std::vector<Key*> Piano::getAllKeys(){
	return m_keys;
}


std::vector<sf::FloatRect> Piano::getKeyGlobalBounds(int position) const{
	//get key bounds
	std::vector<sf::FloatRect> bounds = m_keys[position]->getAccurateGlobalBounds();
	//apply piano transformations
	for(sf::FloatRect &rect : bounds){
		rect = this->getTransform().transformRect(rect);
	}
	return bounds;
}

bool Piano::keyContains(int keyPosition, const sf::Vector2f &point) const{
	for(sf::FloatRect &rect : getKeyGlobalBounds(keyPosition)){
		if(rect.contains(point)){
			return true;
		}
	}
	return false;
}

sf::FloatRect Piano::getKeyNoteButtonGlobalBounds(int keyPosition, int noteButtonPosition) const{
	//get button bounds (with key transformations)
	sf::FloatRect bounds = m_keys[keyPosition]->getButtonGlobalBounds(noteButtonPosition);
	//apply piano transformations
	bounds = this->getTransform().transformRect(bounds);
	return bounds;
}

bool Piano::keyNoteButtonContains(int keyPosition, int noteButtonPosition, const sf::Vector2f &point) const{
	if(getKeyNoteButtonGlobalBounds(keyPosition, noteButtonPosition).contains(point)){
		return true;
	}
	return false;
}

void Piano::setPressedNotes(std::vector<Note> notes){
	std::sort(notes.begin(), notes.end(), [](Note n1, Note n2) -> bool {return n1.getPosition() < n2.getPosition();});
	for(Key* key : m_keys){
		key->setPressed(false);
		for(Note note : notes){
			if (key->getPosition() == note.getPosition()){
				//visualization
				key->switchPressed();
				key->setActiveNote(note);
				break;
			}
		}
	}
}

std::vector<Note> Piano::getPressedNotes(){
	std::vector<Note> pressedNotes;
	for(Key* key : m_keys){
		if(key->getPressed()){
			pressedNotes.push_back(key->getActiveNote());
		}
	}
	return pressedNotes;
}

sf::FloatRect Piano::getGlobalBounds(){
	sf::FloatRect firstKeyBounds = m_keys[0]->getGlobalBounds();
	sf::FloatRect lastKeyBounds = m_keys[m_keys.size()-1]->getGlobalBounds();
	sf::FloatRect pianoBounds;
	pianoBounds.left = firstKeyBounds.left;
	pianoBounds.top = firstKeyBounds.top;
	pianoBounds.width = (lastKeyBounds.left + lastKeyBounds.width) - firstKeyBounds.left;
	pianoBounds.height = firstKeyBounds.height;
	return pianoBounds;
}

Piano::~Piano(){
	for(size_t i=0;i<m_keys.size();i++) { 
		delete m_keys[i];
	}
}
