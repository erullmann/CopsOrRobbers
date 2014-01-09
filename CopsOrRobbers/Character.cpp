#include "Character.h"

Character::Character(sf::Vector2f position, sf::Vector2f orientation, const std::string& texture) : 
	pos(position), 
	orn(orientation), 
	vel(sf::Vector2f(0, 0)){

		float halfwidth = 5;
		float halfheight = 20;
		Rectangle* rectangle = new Rectangle(-halfwidth, -halfheight);
		
		Material *material = new Material();
		material->density = 0.5;
		material->friction = 0.1;
		material->restitution = 0.5;

		_physics = new PhysicsComponent(this, rectangle, material);
		_graphics = new GraphicsComponent(this, texture);
		_action = new ActionComponent(this);

}

PhysicsComponent* Character::getPhysics(){
	return _physics;
}

ActionComponent* Character::getAction(){
	return _action;
}

void Character::update(sf::RenderTarget& target, sf::RenderStates& states){
	_physics->updateComponent();
	_graphics->updateComponent(target, states);
	_action->updateComponent();
}