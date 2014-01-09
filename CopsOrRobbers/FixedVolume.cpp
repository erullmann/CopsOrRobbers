#include "FixedVolume.h"


FixedVolume::FixedVolume(Rectangle* shape, Material *material, sf::Vector2f pos) : cPos(pos), CollisionVolume(shape, material, pos, sf::Vector2f(1,0), sf::Vector2f(0,0)){

}

sf::Vector2f FixedVolume::getPos(){
	return cPos;
}

sf::Vector2f FixedVolume::setPos(sf::Vector2f input){
	//do nothing
	return cPos;
}

sf::Vector2f FixedVolume::getVel(){
	return sf::Vector2f(0, 0);
}

sf::Vector2f FixedVolume::setVel(sf::Vector2f input){
	//do nothing
	return sf::Vector2f(0, 0);
}