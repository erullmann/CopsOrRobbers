//Map.h
//class that implements both the visible and collision map
#pragma once
#include "SFML\Graphics.hpp"
#include "PhysicsManager.h"
#include "FixedVolume.h"
#include "rapidxml.hpp"
#include <list>
#include <string>
#include <fstream>


class Map : public sf::Drawable, public sf::Transformable {
public:

	Map();

	Map(const std::string& tileSet, const int* tileMap, sf::Vector2u tileSize, sf::Vector2u mapSize, std::list<CollisionVolume*>& collisionMap, PhysicsManager physicsManager);

	Map(const std::string& fileName, PhysicsManager& physicsManager);

	bool loadTileMap(const std::string& tileSet, const int* tileMap, sf::Vector2u tileSize, sf::Vector2u mapSize);

	bool loadCollisionMap(std::list<CollisionVolume*>& collisionMap, PhysicsManager& physicsManager);

	bool loadMapFromFile(const std::string& fileName, PhysicsManager& physicsManager);

	const std::list<CollisionVolume*>* getCollisionMap();

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture _tileset;

	sf::VertexArray _verticies;

	std::list<CollisionVolume*>* _collisionMap;

};