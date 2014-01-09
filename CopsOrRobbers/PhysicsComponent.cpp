#include "PhysicsComponent.h"
#include <iostream>


PhysicsComponent::PhysicsComponent(Character *i_character, Rectangle* i_shape, Material *i_material) : 
	CollisionVolume(i_shape, i_material, i_character->pos, i_character->orn, i_character->vel), 
	character(i_character){
		oldPos = character->pos;
		oldVel = character->vel;
}

void PhysicsComponent::updateComponent(){
	if(&CollisionVolume::collided){
		character->status = STANDING;
	}
	//I don't think we have to do much here	
}

sf::Vector2f PhysicsComponent::getPos(){
	return character->pos;
}

sf::Vector2f PhysicsComponent::setPos(sf::Vector2f ipos){
	return character->pos = ipos;
}

sf::Vector2f PhysicsComponent::getVel(){
	return character->vel;
}

sf::Vector2f PhysicsComponent::setVel(sf::Vector2f ivel){
	return character->vel = ivel;
}