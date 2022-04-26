#ifndef KEY_H
#define KEY_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Note.h"
#include "Label.h"
#include "Button.h"
#include "Pressable.h"
#include "RadioButton.h"
#include "Entity.h"
enum keyShapeType {whiteLeft, whiteRight, whiteCenter, black};

class Key : public Entity, public sf::Drawable, public sf::Transformable, public Pressable {
private:
	//logic attributes
	int m_octavePosition;
	std::vector<Note*> m_notes;
	//drawing attributes
	keyShapeType m_shapeType;
	sf::ConvexShape* m_shape;
	RadioButton* m_notesButtons;
	//methods
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void pressOnDrawer();
	void pressOffDrawer();
public:
	//constructors
	Key();
	Key(int position);
	//getters
	std::vector<sf::FloatRect> getAccurateGlobalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	bool contains(const sf::Vector2f &point) const;
	std::vector<Note*> getNotes() const;
	Note getActiveNote();
	int getOctavePosition() const;
	int getPosition() const;
	RadioButton* getNoteButtons();
	sf::FloatRect getButtonGlobalBounds(int buttonPosition);
	keyShapeType getShapeType();
	//setters
	void setActiveNote(Note note);
	//destructors
	virtual ~Key();
};

#endif

