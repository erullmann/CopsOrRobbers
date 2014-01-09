//Contact.h
//Struct for maintaining a record of contact between two physics objects
#pragma once
#include "PhysicsComponent.h"
#include "SFML\Graphics.hpp"

struct Contact {
	CollisionVolume* a;
	CollisionVolume* b;

	sf::Vector2f n; //normal
	float m;//magnitude
};