#include "PhysicsManager.h"	
#include <iostream>

PhysicsManager::PhysicsManager(){
	_physicsObjects = new std::list<CollisionVolume*>();
	_contacts = new std::list<Contact*>();
}

PhysicsManager::~PhysicsManager(){
	delete _physicsObjects;
	delete _contacts;
}

void PhysicsManager::addPhysicsObject(CollisionVolume* body){
	_physicsObjects->push_back(body);
}

void PhysicsManager::removePysicsObject(CollisionVolume* body){
	_physicsObjects->remove(body);
}

void PhysicsManager::removeAllPhysicsObjects(){
	_physicsObjects->clear();
}

const std::list<CollisionVolume*>* PhysicsManager::getAllPhysicsObjects(){
	return _physicsObjects;
}

void PhysicsManager::updatePhysics(sf::Time delta){

	_collisionCheck();

	for(std::list<Contact*>::iterator iter = _contacts->begin(); iter != _contacts->end(); iter++){
		_frictionalCorrect((*iter));
	}

	for(int i = 0; i < 10; i++){
		for(std::list<Contact*>::iterator iter = _contacts->begin(); iter != _contacts->end(); iter++){
			_handleCollision((*iter));
		}
	}

	for(std::list<CollisionVolume*>::iterator iter = _physicsObjects->begin(); iter != _physicsObjects->end(); iter++){
		(*iter)->update(delta);
	}

	for(std::list<Contact*>::iterator iter = _contacts->begin(); iter != _contacts->end(); iter++){
		_positionalCorrect((*iter));
	}
	
}

void PhysicsManager::d_drawPhysics(sf::RenderTarget &target, sf::RenderStates states){
	for(std::list<CollisionVolume*>::iterator iter = _physicsObjects->begin(); iter != _physicsObjects->end(); iter++){
		(*iter)->d_RenderVolume(target, states, true);
	}
}

void PhysicsManager::_collisionCheck(){
	_contacts->clear();

	for(std::list<CollisionVolume*>::iterator iter = _physicsObjects->begin(); iter != _physicsObjects->end(); iter++){
		for(std::list<CollisionVolume*>::iterator jter = _physicsObjects->begin(); jter != _physicsObjects->end(); jter++){
			if(((*iter) != (*jter)) && ((*iter)->AABB().intersects((*jter)->AABB())) && !_inPairsList((*iter), (*jter))){
				CollisionVolume* a = (*iter);
				CollisionVolume* b = (*jter);

				sf::Rect<float> inter;
				a->AABB().intersects(b->AABB(), inter);

				sf::Vector2f n = (inter.width <= inter.height)? sf::Vector2f(1, 0) : sf::Vector2f(0, 1);
				float neg = (inter.width <= inter.height)? a->getPos().x - b->getPos().x : a->getPos().y - b->getPos().y;
				neg /= abs(neg);
				n *= neg;

				float m = (inter.width <= inter.height)? inter.width : inter.height;

				Contact* c = new Contact;
				c->a = (a->AABB().contains(inter.left, inter.top))? a : b;
				c->b = (c->a == a)? b : a;
				c->n = n;
				c->m = m;
				_contacts->push_back(c);	
			}
		}
	}
}

bool PhysicsManager::_inPairsList(CollisionVolume* a, CollisionVolume* b){
	for(std::list<Contact*>::iterator iter = _contacts->begin(); iter != _contacts->end(); iter++){
		if(((*iter)->a == a || (*iter)->a == b) &&
			((*iter)->b == a || (*iter)->b == b))
			return true;
	}
	return false;
}

void PhysicsManager::_handleCollision(Contact* c){

	sf::Vector2f apvel = c->a->getVel();
	sf::Vector2f bpvel = c->b->getVel();

	sf::Vector2f n = c->n;

	float vrel = dot(n, apvel - bpvel);

	if(vrel > 0){ //moving away
		return;
	}

	float j = -vrel;

	c->a->setVel(c->a->getVel() + (j * n));
	c->b->setVel(c->b->getVel() - (j * n));

	c->a->collided(c->n);
	c->b->collided(c->n);
}

void PhysicsManager::_positionalCorrect(Contact* c){

	float k_slop = 0.05f; // Penetration allowance
	float percent = 0.4f; // Penetration percentage to correct
	float penetration = c->m;
	sf::Vector2f correction = std::max(penetration - k_slop, 0.0f ) * unit(c->n) * percent;
	c->a->setPos(c->a->getPos() + correction);
	c->b->setPos(c->b->getPos() - correction);

	c->a->collided(c->n);
	c->b->collided(c->n);
}

void PhysicsManager::_frictionalCorrect(Contact* c){
	
}

