//FixedVolume.h
//A collision volume with a fixed position that cannot be moved

#pragma once
#include "CollisionVolume.h"

class FixedVolume : public CollisionVolume {
public:

	FixedVolume(Rectangle* rect, Material* material, sf::Vector2f pos);

	virtual sf::Vector2f getPos();
	virtual sf::Vector2f setPos(sf::Vector2f pos);

	virtual sf::Vector2f getVel();
	virtual sf::Vector2f setVel(sf::Vector2f vel);

protected:

	const sf::Vector2f cPos;

};