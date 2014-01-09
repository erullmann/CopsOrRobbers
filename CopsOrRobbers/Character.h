//Character.h
//Character class based off of PhysicsComponent
//adds drawing and input functionality
#pragma once
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "ActionComponent.h"
#include "SFML\Graphics.hpp"

enum STATUS {
	STANDING,
	CROUCHING,
	FALLING,
	HANGING,
	ATTACK_CLOSE,
	ATTACK_RANGE
};

class PhysicsComponent;
class GraphicsComponent;
class ActionComponent;

class Character{
public:

	Character(sf::Vector2f position, sf::Vector2f orientation, const std::string& texture);//add typing to load health, texture, etc.

	void update(sf::RenderTarget& target, sf::RenderStates& states);

	PhysicsComponent* getPhysics();

	ActionComponent* getAction();

protected:

	STATUS status;

	sf::Vector2f pos;
	sf::Vector2f orn;
	sf::Vector2f vel;

	float health;

private:

	PhysicsComponent* _physics;
	ActionComponent* _action;
	GraphicsComponent* _graphics;

	friend PhysicsComponent;
	friend ActionComponent;
	friend GraphicsComponent;
};