#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H
#include "Entity.h"
#include "GroupedButton.h"

class RadioButton : public Entity, public sf::Drawable, public sf::Transformable, public Sensible {
private:
	std::vector<Button*> m_buttons;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	RadioButton();
	RadioButton(std::vector<std::string> texts, int size, int offset, sf::Color color);
	sf::FloatRect getButtonGlobalBounds(int position);
	bool buttonContains(int buttonPosition, const sf::Vector2f &position);
	Button* getButton(int position);
	int size();
	Button* getActiveButton();
	int getActiveButtonPosition();
	void setActiveButton(int position);
	~RadioButton();
};

#endif

