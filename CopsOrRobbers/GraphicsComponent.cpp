#include "GraphicsComponent.h"


GraphicsComponent::GraphicsComponent(Character* i_character, const std::string& i_texture){
	character = i_character;
	texture = new sf::Texture();
	texture->loadFromFile(i_texture);
	sprite.setTexture(*texture);
}

void GraphicsComponent::updateComponent(sf::RenderTarget& target, sf::RenderStates &states){
	setSprite();
	target.draw(sprite, states);
}

void GraphicsComponent::setSprite(){
	subRect.left = 0;
	subRect.top = 0;
	subRect.width = CHARACTERWIDTH;
	subRect.height = CHARACTERHEIGHT;

	sprite.setTextureRect(subRect);
	sprite.setPosition(character->pos.x - CHARACTERWIDTH/2, character->pos.y - CHARACTERHEIGHT/2);
}