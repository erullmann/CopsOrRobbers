#include "Rectangle.h"

Rectangle::Rectangle(sf::Vector2f halfSize):_halfSize(halfSize){}

Rectangle::Rectangle(float halfWidth, float halfHeight):_halfSize(halfWidth, halfHeight){}

sf::Vector2f Rectangle::getHalfSize(){
	return _halfSize;
}

sf::Vector2f Rectangle::getFullSize(){
	return 2.0f * _halfSize;
}

float Rectangle::getVolume(){
	return _halfSize.x * _halfSize.y;
}