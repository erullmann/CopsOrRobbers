//Graphics Component.h

#pragma once
#include "SFML\Graphics.hpp"
#include "Character.h"

#define CHARACTERWIDTH 12
#define CHARACTERHEIGHT 43

class Character;

class GraphicsComponent {
public:

	//add load image mapping from file, texture loading from reasorce locator (to avoid duplicate loads)
	GraphicsComponent(Character* character, const std::string& texture);

	void updateComponent(sf::RenderTarget& target, sf::RenderStates &states);

private:

	void setSprite();

	sf::IntRect subRect;

	sf::Texture* texture;

	sf::Sprite sprite;

	Character* character;

};