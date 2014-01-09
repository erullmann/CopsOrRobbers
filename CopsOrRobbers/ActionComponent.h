//ActionComponent.h
//Base class to define a set of actions that can be taken by a Game Actor
//Most of these will be virtual and will have some simple sample implementations

#pragma once
#include "Character.h"

//change these definitions to load from file
#define WALK_MOD 1.0f
#define CROUCH_MOD 0.5f

#define WALK_ACCEL 150.0f
#define WALK_MAX 100.0f
#define JUMP_IMPULSE 300.0f

enum ACTION {
	HALT,
	JUMP,
	GO_LEFT,
	GO_RIGHT,
	SHOOT,
	HIT
};

enum MOD {
	STAND,
	CROUCH
};

class ActionComponent {
public:

	ActionComponent(Character* character);

	//Called by character to update info
	void updateComponent();

	//sets the current action to do, some actions can be done while doing other actions
	//Character will do action for next frame, will stop if no action given
	void jump();//character will jump next frame
	void goRight();//sends character right, overridden by goLeft //if not called character stops
	void goLeft();//sends character left, overridden by goRight
	void crouch();//character will crouch next frame, if this is not call, character will stand

	//sets where the character is looking (probably based on mouse)
	void setViewDirection(sf::Vector2f direction);

private:

	MOD _currMod;

	ACTION _currAction;

	sf::Vector2f _currDirection;

	Character* character;

};