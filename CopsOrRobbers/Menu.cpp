#pragma once

#include "Menu.h"

Menu::Menu(List<Button>* buttons, const std::string& tileset){
	_buttons = buttons;
	_isActive = false;

	if(!_textureSet.loadFromFile(tileset)){
		//error log?
		return;
	}

	_vertices.setPrimitiveType(sf::Quads);
	_vertices.resize((_buttons->getLength() + 1) * 4);
	int i;
	ListIter<Button> iter(_buttons);
	for(iter.reset(), i = 1; !iter.atEnd(), i < (_buttons->getLength() + 1); iter.next(), ++i){

		sf::Vertex* quad = &_vertices[i * 4];

		quad[0].position = sf::Vector2f(iter.curr()->getPostion()); //top-left
		quad[1].position = sf::Vector2f(iter.curr()->getPostion().x + iter.curr()->getSize().x, iter.curr()->getPostion().y); //top-right
		quad[2].position = sf::Vector2f(iter.curr()->getPostion().x + iter.curr()->getSize().x, iter.curr()->getPostion().y + iter.curr()->getSize().y); //bottom-right
		quad[3].position = sf::Vector2f(iter.curr()->getPostion().x, iter.curr()->getPostion().y + iter.curr()->getSize().y); //bottom-left

		int a = iter.curr()->getStatus();

		quad[0].texCoords = sf::Vector2f(0, a*iter.curr()->getSize().y);
		quad[1].texCoords = sf::Vector2f(iter.curr()->getSize().x, a*iter.curr()->getSize().y);
		quad[2].texCoords = sf::Vector2f(iter.curr()->getSize().x, (a+1)*iter.curr()->getSize().y);
		quad[3].texCoords = sf::Vector2f(0, (a+1)*iter.curr()->getSize().y);

	}

	sf::Vertex* quad = &_vertices[0];
	sf::Color color(0, 0, 0, 200);

	quad[0].position = sf::Vector2f(0, 0); //top-left
	quad[1].position = sf::Vector2f(800, 0); //top-right
	quad[2].position = sf::Vector2f(800, 600); //bottom-right
	quad[3].position = sf::Vector2f(0, 600); //bottom-left

	quad[0].color = color; //top-left
	quad[1].color = color; //top-right
	quad[2].color = color; //bottom-right
	quad[3].color = color; //bottom-left

	assignTextures();
}

void Menu::disableMenu(){
	_isActive = false;
}
void Menu::enableMenu(){
	_isActive = true;
}

void Menu::handleEvent(sf::Event e){
	if(_isActive){
		bool changes = false;
		for(ListIter<Button> iter(_buttons); !iter.atEnd(); iter.next()){
			 if(iter.curr()->handleEvent(e)){
				 changes = true;
			 }
		}
		if(changes)
			assignTextures();
	}
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	if(_isActive){
		states.texture = &_textureSet;

		target.draw(_vertices, states);
	}

}

void Menu::assignTextures(){
	ListIter<Button> iter(_buttons);
	int i;

	for(iter.curr(), i = 1; !iter.atEnd(), i < (_buttons->getLength() + 1); iter.next(), ++i){
		sf::Vertex* quad = &_vertices[i * 4];
		int a = iter.curr()->getStatus();

		quad[0].texCoords = sf::Vector2f(0, a*iter.curr()->getSize().y);
		quad[1].texCoords = sf::Vector2f(iter.curr()->getSize().x, a*iter.curr()->getSize().y);
		quad[2].texCoords = sf::Vector2f(iter.curr()->getSize().x, (a+1)*iter.curr()->getSize().y);
		quad[3].texCoords = sf::Vector2f(0, (a+1)*iter.curr()->getSize().y);
	}
}