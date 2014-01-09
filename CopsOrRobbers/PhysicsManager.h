//PhysicsManager.h
//A singleton class to keep track of and update the movement and interactions between physics objects
#pragma once
#include "SFML\Graphics.hpp"
#include <list>
#include "CollisionVolume.h"
#include "Contact.h"

//contact threshold for collisions
#define THRESHOLD 0.001
#define DEBUG false

class PhysicsManager {
public:

	PhysicsManager();

	~PhysicsManager();

	void addPhysicsObject(CollisionVolume* body);

	void removePysicsObject(CollisionVolume* body);

	void removeAllPhysicsObjects();

	const std::list<CollisionVolume*>* getAllPhysicsObjects();

	void updatePhysics(sf::Time delta);

	void d_drawPhysics(sf::RenderTarget &target, sf::RenderStates states);


private:

	struct Line {
		sf::Vector2f n;
		float c;
	};

	void _collisionCheck();

	bool _inPairsList(CollisionVolume* a, CollisionVolume* b);

	void _handleCollision(Contact* c);

	void _positionalCorrect(Contact* c);

	void _frictionalCorrect(Contact* c);

	std::list<CollisionVolume*>* _physicsObjects;

	std::list<Contact*>* _contacts;

};
