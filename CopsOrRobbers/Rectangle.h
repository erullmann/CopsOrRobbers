//Rectangle.h
//simple shape for collision

#include "SFML\Graphics.hpp"

class Rectangle {
private:

	sf::Vector2f _halfSize;

public:

	Rectangle(sf::Vector2f halfSize);

	Rectangle(float halfWidth, float halfHeight);

	sf::Vector2f getHalfSize();

	sf::Vector2f getFullSize();

	float getVolume();

};