#ifndef PIANO_H
#define PIANO_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Key.h"

class Piano : public sf::Drawable, public sf::Transformable, public Sensible {	
private:
	//attributes
	std::vector<Key*> m_keys;
	//methods
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	//constructor
	Piano(Note firstNote, Note endNote);
	//getters
	int size();
	Key* getKey(int position);
	std::vector<Key*> getAllKeys();
	std::vector<Note> getPressedNotes();
	std::vector<sf::FloatRect> getKeyGlobalBounds(int position) const;
	sf::FloatRect getGlobalBounds();
	bool keyContains(int keyPosition, const sf::Vector2f &point) const;
	sf::FloatRect getKeyNoteButtonGlobalBounds(int keyPosition, int noteButtonPosition) const;
	bool keyNoteButtonContains(int keyPosition, int noteButtonPosition, const sf::Vector2f &point) const;
	//setters
	void setPressedNotes(std::vector<Note> notes);
	~Piano();
};

#endif

