#pragma once
#include "Map.h"
#include <iostream>

Map::Map(){
	_collisionMap = new std::list<CollisionVolume*>;
}

Map::Map(const std::string& tileSet, const int* tileMap, sf::Vector2u tileSize, sf::Vector2u mapSize, std::list<CollisionVolume*>& collisionMap, PhysicsManager physicsManager){
	_collisionMap = new std::list<CollisionVolume*>;
	loadTileMap(tileSet, tileMap, tileSize, mapSize);
	loadCollisionMap(collisionMap, physicsManager);
}

Map::Map(const std::string& fileName, PhysicsManager& physicsManager){
	_collisionMap = new std::list<CollisionVolume*>;
	loadMapFromFile(fileName, physicsManager);
}

bool Map::loadTileMap(const std::string& tileSet, const int* tileMap, sf::Vector2u tileSize, sf::Vector2u mapSize){
	
	if(!_tileset.loadFromFile(tileSet))
		return false; //couldn't load tileset

	_verticies.setPrimitiveType(sf::PrimitiveType::Quads);
	_verticies.resize(mapSize.x * mapSize.y * 4);

	for(int i = 0; i < mapSize.x; ++i){
		for(int j = 0; j < mapSize.y; ++j){
			
			int tn = tileMap[i + j * mapSize.x];

			if(tn == 0){
				//skip
			} else {

				tn--;

				int tu = tn % (_tileset.getSize().x / tileSize.x);
				int tv = tn / (_tileset.getSize().x / tileSize.x);

				//std::cout<< i << ", " << j << " Mapsize: " << mapSize.x << ", " << mapSize.y <<" total: " << (i + j * mapSize.x) * 4 <<std::endl;

				sf::Vertex* quad = &_verticies[(i + j * mapSize.x) * 4];

				quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

				quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
				quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

			}

		}
	}

	return true;
}

bool Map::loadCollisionMap(std::list<CollisionVolume*>& collisionMap, PhysicsManager& physicsManager){
	
	for(std::list<CollisionVolume*>::iterator iter = collisionMap.begin(); iter != collisionMap.end(); iter++){
		physicsManager.addPhysicsObject(*iter);
	}

	return false;

}

bool Map::loadMapFromFile(const std::string& fileName, PhysicsManager& physicsManager){

	//read file into char array
	std::ifstream file(fileName, std::ios::in | std::ios::binary);
	char* contents = NULL;

	//TEST ENCODING PROBLEM, NEED UTF-8
	if(file){
		file.seekg(0, std::ios::end);
		int n = file.tellg();
		contents = new char[n+1];
		file.seekg(0, std::ios::beg);
		file.read(contents, n);
		file.close();
		contents[n] = '\0';
		//std::cout << "file: " << fileName << " read of length: " << n << std::endl;
		//std::cout << contents << std::endl;
	}

	//parse XML document
	rapidxml::xml_document<> doc;
	doc.parse<0>(contents);

	rapidxml::xml_node<>* mapNode = doc.first_node();
	rapidxml::xml_node<>* tilesetNode = mapNode->first_node();
	
	//get tileset varibles
	sf::Vector2u tileSize(std::stoi(tilesetNode->first_attribute("tilewidth")->value()), std::stoi(tilesetNode->first_attribute("tileheight")->value()));
	std::string tilesetName(tilesetNode->first_node("image")->first_attribute("source")->value());
	sf::Vector2u mapSize(std::stoi(mapNode->first_attribute("width")->value()), std::stoi(mapNode->first_attribute("height")->value()));

	//get map array
	int* map = new int[mapSize.x * mapSize.y];//free me
	int i = 0;
	for(rapidxml::xml_node<>* node = mapNode->first_node()->next_sibling()->next_sibling()->first_node()->first_node(); node; node = node->next_sibling()){
		map[i] = std::stoi(node->first_attribute("gid")->value());
		std::cout << map[i] << std::endl;
		++i;
	}

	//load tiles
	loadTileMap(std::string(tilesetName), map, tileSize, mapSize);

	delete [] map;

	//create collision rectangles and add them to physics manager
	i = 0;
	for(rapidxml::xml_node<>* node = mapNode->first_node()->next_sibling("objectgroup")->first_node(); node; node = node->next_sibling()){

		float halfwidth = std::stoi(node->first_attribute("width")->value())/2;
		float halfheight = std::stoi(node->first_attribute("height")->value())/2;

		int x = std::stoi(node->first_attribute("x")->value())+halfwidth;
		int y = std::stoi(node->first_attribute("y")->value())+halfheight;

		Rectangle* rectangle = new Rectangle(-halfwidth, -halfheight);
		Material* material = new Material();
		material->density = 0.5;
		material->friction = 0.5;
		material->restitution = 0.5;

		CollisionVolume* body = new FixedVolume(rectangle, material, sf::Vector2f(x, y));

		physicsManager.addPhysicsObject(body);
		++i;
	}

	delete [] contents;

	return true;

}

const std::list<CollisionVolume*>* Map::getCollisionMap(){
	return _collisionMap;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const{

	states.texture = &_tileset;

	target.draw(_verticies, states);

}