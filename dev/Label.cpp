#include "Label.h"
#include "TextEntity.h"
#include <string>
#include <SFML/Graphics.hpp>

Label::Label(std::string text, int size, sf::Color color) : TextEntity<sf::RectangleShape>(text, size, color){
}
