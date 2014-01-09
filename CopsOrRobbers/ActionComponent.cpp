#include "ActionComponent.h"

ActionComponent::ActionComponent(Character* i_character){
	character = i_character;
}

void ActionComponent::updateComponent(){
	_currAction = HALT;
	_currMod = STAND; //check for standing room (or put in auto-updater)
}

void ActionComponent::jump(){
	if(character->status != FALLING && character->status != CROUCHING)
		character->vel.y -= JUMP_IMPULSE;
	character->status = FALLING; //note: need to check for non-input statuses and autoupdate them (like: if not touching ground -> falling)
}

void ActionComponent::goRight(){
	character->vel.x = WALK_MAX * ((_currMod == CROUCH)? CROUCH_MOD : WALK_MOD);
}

void ActionComponent::goLeft(){
	character->vel.x = -WALK_MAX * ((_currMod == CROUCH)? CROUCH_MOD : WALK_MOD);
}

void ActionComponent::crouch(){
	_currMod = CROUCH;
}

void ActionComponent::setViewDirection(sf::Vector2f direction){
	_currDirection = direction;
}