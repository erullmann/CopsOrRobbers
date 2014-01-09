//CollisionVolume.h
#pragma once
#include <SFML\Graphics.hpp>
#include "Material.h"
#include "Rectangle.h"
#include "MyMath.h"

#define GRAV_CONST 750


class CollisionVolume{
public:
	
	CollisionVolume(Rectangle* rect, Material *material, sf::Vector2f position, sf::Vector2f orientation, sf::Vector2f velocity, bool ghost=false);

	//Debug function that draws the shape of the body and/or the bounding box
	void d_RenderVolume(sf::RenderTarget& target, sf::RenderStates states, bool drawShape=true);

	//Returns a rectangle of the bounding box of the shape
	virtual sf::Rect<float> AABB();

	//updates the position and orientation of the object based on its velocity and rotaionalVelocity
	virtual void update(sf::Time delta);

	//call when collsion occurs with normal to collsion
	virtual void collided(sf::Vector2f collsionNormal);

	virtual sf::Vector2f getPos();
	virtual sf::Vector2f setPos(sf::Vector2f pos);

	virtual sf::Vector2f getVel();
	virtual sf::Vector2f setVel(sf::Vector2f vel);

	virtual const Material* getMaterial();
	virtual const float getMass();

protected:

	Rectangle* rect;

	Material* material;

	bool colliding;

	bool ghost;

	float mass;

	sf::Vector2f pos;
	sf::Vector2f orn;
	sf::Vector2f vel;
};