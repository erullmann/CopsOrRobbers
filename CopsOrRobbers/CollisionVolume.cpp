#include "CollisionVolume.h"

CollisionVolume::CollisionVolume(Rectangle* i_shape, Material* material, sf::Vector2f i_pos, sf::Vector2f i_orn, sf::Vector2f i_vel, bool i_ghost) : 
	rect(i_shape), 
	material(material),
	pos(i_pos),
	orn(i_orn),
	vel(i_vel),
	ghost(i_ghost){
	
		mass = material->density * rect->getVolume();
}

void CollisionVolume::d_RenderVolume(sf::RenderTarget& target, sf::RenderStates states, bool drawShape){
	sf::Color color = sf::Color::Black;
	if(drawShape){
		sf::Rect<float> rect = AABB();
		sf::VertexArray vertices(sf::PrimitiveType::LinesStrip, 5);
		vertices[0].position = sf::Vector2f(rect.left, rect.top);
		vertices[0].color = color;
		vertices[1].position = sf::Vector2f(rect.left+rect.width, rect.top);
		vertices[1].color = color;
		vertices[2].position = sf::Vector2f(rect.left+rect.width, rect.top+rect.height);
		vertices[2].color = color;
		vertices[3].position = sf::Vector2f(rect.left, rect.top+rect.height);
		vertices[3].color = color;
		vertices[4].position = sf::Vector2f(rect.left, rect.top);
		vertices[4].color = color;
		target.draw(vertices, states);

		sf::VertexArray direction(sf::PrimitiveType::Lines, 4);
		direction[0].position = getPos();
		direction[0].color = color;
		direction[1].position = getPos() + 30.0f * orn;
		direction[1].color = color;
		direction[2].position = getPos();
		direction[2].color = color;
		direction[3].position = getPos() + 10.0f * right(orn);
		direction[3].color = color;
		target.draw(direction, states);
	} 
}

sf::Rect<float> CollisionVolume::AABB(){
	return sf::Rect<float>(getPos().x - rect->getHalfSize().x, getPos().y - rect->getHalfSize().y, rect->getFullSize().x, rect->getFullSize().y);
}

void CollisionVolume::update(sf::Time delta){
	setVel(getVel() + sf::Vector2f(0, GRAV_CONST * delta.asSeconds()));
	setPos(getPos() + getVel() * delta.asSeconds());
	colliding = false;
}

void CollisionVolume::collided(sf::Vector2f i_collsionNormal){
	colliding = true;
}

sf::Vector2f CollisionVolume::getPos(){
	return pos;
}

sf::Vector2f CollisionVolume::setPos(sf::Vector2f input){
	return pos = input;
}

sf::Vector2f CollisionVolume::getVel(){
	return vel;
}

sf::Vector2f CollisionVolume::setVel(sf::Vector2f input){
	return vel = input;
}

const Material* CollisionVolume::getMaterial(){
	return material;
}

const float CollisionVolume::getMass(){
	return mass;
}