#pragma once
//PhysicsComponent.h
//An implementation of a collidable rigid body of an arbitray shape
#include "Character.h"
#include "CollisionVolume.h"

class Character;

class PhysicsComponent : public CollisionVolume {
public:

	//Create a new PhysicsComponent
	PhysicsComponent(Character* character, Rectangle* rectangle, Material* material);

	//updates component specific stuff (like passing data back to character)
	//this is done to seperate physics update loop and draw/logic loop
	virtual void updateComponent();

	sf::Vector2f getPos();
	sf::Vector2f setPos(sf::Vector2f pos);

	sf::Vector2f getVel();
	sf::Vector2f setVel(sf::Vector2f vel);

private:

	Character* character;

	sf::Vector2f oldPos;
	sf::Vector2f oldVel;

};