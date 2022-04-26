#include "Key.h"
#include "Globals.h"
#include <sstream>
#include <tuple>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Label.h"
#include <iostream>
#include "Button.h"
#include <iterator>

//constructors
Key::Key() {
}

Key::Key(int position) {
	//calculate octavePosition
	m_octavePosition = position%12;
	
	//identify key shape
	vector<int> whiteLeftPositions = {0, 5};
	vector<int> whiteRightPositions = {4, 11};
	vector<int> whiteCenterPositions = {2, 7, 9};
	vector<int> blackPositions = {1, 3, 6, 8, 10};
	
	//(the expected if clauses are ommited here for more readability)
	auto whiteLeftIt = find(whiteLeftPositions.begin(), whiteLeftPositions.end(), m_octavePosition);
	auto whiteRightIt = find(whiteRightPositions.begin(), whiteRightPositions.end(), m_octavePosition);
	auto whiteCenterIt = find(whiteCenterPositions.begin(), whiteCenterPositions.end(), m_octavePosition);
	auto blackIt = find(blackPositions.begin(), blackPositions.end(), m_octavePosition);
	
	if (whiteLeftIt != whiteLeftPositions.end()){
		m_shapeType = whiteLeft;
		
	}
	else if (whiteRightIt != whiteRightPositions.end()){
		m_shapeType = whiteRight;
	}
	else if (whiteCenterIt != whiteCenterPositions.end()){
		m_shapeType = whiteCenter;
	}
	else {
		m_shapeType = black;
	}
	
	
	//set shape
	m_shape = new sf::ConvexShape(); 
	float keywidth = 62;
	float keyheight = 227;
	
	switch (m_shapeType){
	case whiteLeft:
		m_shape->setPointCount(6);
		m_shape->setPoint(0, sf::Vector2f(0, 0));
		m_shape->setPoint(1, sf::Vector2f(keywidth*0.75, 0));
		m_shape->setPoint(2, sf::Vector2f(keywidth*0.75, keyheight*0.5));
		m_shape->setPoint(3, sf::Vector2f(keywidth, keyheight*0.5));
		m_shape->setPoint(4, sf::Vector2f(keywidth, keyheight));
		m_shape->setPoint(5, sf::Vector2f(0, keyheight));
		
		m_shape->setFillColor(sf::Color::White);
		break;
	case whiteRight:
		m_shape->setPointCount(6);
		m_shape->setPoint(0, sf::Vector2f(keywidth*0.25, 0));
		m_shape->setPoint(1, sf::Vector2f(keywidth, 0));
		m_shape->setPoint(2, sf::Vector2f(keywidth, keyheight));
		m_shape->setPoint(3, sf::Vector2f(0, keyheight));
		m_shape->setPoint(4, sf::Vector2f(0, keyheight*0.5));
		m_shape->setPoint(5, sf::Vector2f(keywidth*0.25, keyheight*0.5));
		
		m_shape->setFillColor(sf::Color::White);
		break;
	case whiteCenter:
		m_shape->setPointCount(8);
		m_shape->setPoint(0, sf::Vector2f(keywidth*0.25, 0));
		m_shape->setPoint(1, sf::Vector2f(keywidth*0.75, 0));
		m_shape->setPoint(2, sf::Vector2f(keywidth*0.75, keyheight*0.5));
		m_shape->setPoint(3, sf::Vector2f(keywidth, keyheight*0.5));
		m_shape->setPoint(4, sf::Vector2f(keywidth, keyheight));
		m_shape->setPoint(5, sf::Vector2f(0, keyheight));
		m_shape->setPoint(6, sf::Vector2f(0, keyheight*0.5));
		m_shape->setPoint(7, sf::Vector2f(keywidth*0.25, keyheight*0.5));
		
		m_shape->setFillColor(sf::Color::White);
		break;
	case black:
		m_shape->setPointCount(4);
		m_shape->setPoint(0, sf::Vector2f(0, 0));
		m_shape->setPoint(1, sf::Vector2f(keywidth*0.5, 0));
		m_shape->setPoint(2, sf::Vector2f(keywidth*0.5, keyheight*0.5));
		m_shape->setPoint(3, sf::Vector2f(0, keyheight*0.5));
		
		m_shape->setFillColor(sf::Color::Black);
		break;
	}
	
	m_shape->setOutlineColor(sf::Color::Black);
	m_shape->setOutlineThickness(2);
	
	//set notes
	std::vector<Note> notes = getNotesByPosition(position);
	for(size_t i=0;i<notes.size();i++) { 
		Note* note = new Note(notes[i]);
		m_notes.push_back(note);
	}
	
	//set radioButton
	std::vector<std::string> strings;
	for(size_t i=0;i<notes.size();i++) {
		strings.push_back(notes[i].getFullName());
	}
	m_notesButtons = new RadioButton(strings, 13, 26, sf::Color(250,10,10));
	m_notesButtons->setVisible(false);	//because the note isn't pressed
	
	//align key and buttons
	sf::FloatRect generalBounds = m_shape->getGlobalBounds();
	if(m_shapeType == black){
		m_notesButtons->setPosition(generalBounds.width*0.5, generalBounds.height * 0.4);		
	}
	else{
		m_notesButtons->setPosition(generalBounds.width*0.5, generalBounds.height * 0.6);		
	}
}

//private methods
void Key::pressOnDrawer(){
	if(m_shapeType == black){
		m_shape->setFillColor(sf::Color(220,70,70));
	}
	else{
		m_shape->setFillColor(sf::Color(255,90,90));
	}
	m_notesButtons->setVisible(true);
}

void Key::pressOffDrawer(){
	if(m_shapeType == black){
		m_shape->setFillColor(sf::Color::Black);
		
	}
	else{
		m_shape->setFillColor(sf::Color::White);
	}
	m_notesButtons->setVisible(false);
}

void Key::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= getTransform();
	target.draw(*m_shape, states);
	if(m_notesButtons->getVisible()){
		target.draw(*m_notesButtons, states);
	}
}

//getters
vector<sf::FloatRect> Key::getAccurateGlobalBounds() const{
	vector<sf::FloatRect> bounds;
	
	//build bounds
	//the bounds are maded with the complete sprite rect, moving and scaling it to obtain 2 rects which fill all the key surface
	sf::FloatRect generalBounds, upBound, downBound;
	
	generalBounds = m_shape->getGlobalBounds();
	
	switch (m_shapeType){
	case whiteLeft:
		upBound = sf::FloatRect(generalBounds.left, generalBounds.top, generalBounds.width/2.f, generalBounds.height/2.f);
		downBound = sf::FloatRect(generalBounds.left, generalBounds.top + generalBounds.height/2.f, generalBounds.width, generalBounds.height/2.f);
		break;
	case whiteRight:
		upBound = sf::FloatRect(generalBounds.left + generalBounds.width/2.f, generalBounds.top, generalBounds.width/2.f, generalBounds.height/2.f);
		downBound = sf::FloatRect(generalBounds.left, generalBounds.top + generalBounds.height/2.f, generalBounds.width, generalBounds.height/2.f);
		break;
	case whiteCenter:
		upBound = sf::FloatRect(generalBounds.left + generalBounds.width/4.f, generalBounds.top, generalBounds.width/2.f, generalBounds.height/2.f);
		downBound = sf::FloatRect(generalBounds.left, generalBounds.top + generalBounds.height/2.f, generalBounds.width, generalBounds.height/2.f);
		break;
	case black:
		upBound = generalBounds;
		break;
		//downBound is kept the same. It means (0,0,0,0)
	}
	//apply key transformations
	upBound = this->getTransform().transformRect(upBound);
	downBound = this->getTransform().transformRect(downBound);
	
	bounds.push_back(upBound);
	bounds.push_back(downBound);
	
	return bounds;
}


sf::FloatRect Key::getButtonGlobalBounds(int buttonPosition){
	//get button bounds
	sf::FloatRect bounds = m_notesButtons->getButtonGlobalBounds(buttonPosition);
	//apply key transformations
	bounds = this->getTransform().transformRect(bounds);
	return bounds;
}


RadioButton* Key::getNoteButtons(){
	return m_notesButtons;
}

sf::FloatRect Key::getGlobalBounds() const{
	//get shape bounds
	sf::FloatRect bounds = m_shape->getGlobalBounds();
	//apply container transformations
	bounds = this->getTransform().transformRect(bounds);
	return bounds;
}

bool Key::contains(const sf::Vector2f &point) const{
	bool isContained = false;
	for (sf::FloatRect &rect : getAccurateGlobalBounds()){
		if (rect.contains(point)){
			isContained = true;
			break;
		}
	}
	return isContained;
}

int Key::getOctavePosition() const{
	return m_octavePosition;
}

int Key::getPosition() const{
	return m_notes[0]->getPosition();
}


Note Key::getActiveNote(){
	return *m_notes[m_notesButtons->getActiveButtonPosition()];
}

std::vector<Note*> Key::getNotes() const{
	return m_notes;
}

keyShapeType Key::getShapeType(){
	return m_shapeType;
}


//setters
void Key::setActiveNote(Note note){
	//it's necessary to use find_if because the vector elements are pointers
	for(size_t i=0;i<m_notes.size();i++) {
		if (*m_notes[i] == note){
			m_notesButtons->setActiveButton(i);
		}
	}
}

Key::~Key(){
	for(size_t i=0;i<m_notes.size();i++) { 
		delete m_notes[i];
	}
	delete m_shape;
	delete m_notesButtons;
}
