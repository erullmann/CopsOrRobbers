//button.cpp

#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, void (*callbackFunction)(void)){
	_callbackFunction = callbackFunction;
	_size = size;
	_position = position;
	_status = BUTTONSTATUS::NORMAL;
}

bool Button::handleEvent(sf::Event e){
	if(_status == BUTTONSTATUS::DISABLED){
		return false;
	}

	bool mouseOverButton = false;
	bool mouseButtonPressed = (e.type == sf::Event::MouseButtonPressed);
	bool mouseButtonReleased = (e.type == sf::Event::MouseButtonReleased);
	BUTTONSTATUS newStatus = _status;

	if((e.mouseMove.x >= _position.x && e.mouseMove.x <= _position.x + _size.x) &&
	   (e.mouseMove.y >= _position.y && e.mouseMove.y <= _position.y + _size.y)){
		   mouseOverButton = true;
	}
	if((e.mouseButton.x >= _position.x && e.mouseButton.x <= _position.x + _size.x) &&
	   (e.mouseButton.y >= _position.y && e.mouseButton.y <= _position.y + _size.y)){
		   mouseOverButton = true;
	}

	if(mouseOverButton && _status != BUTTONSTATUS::MOUSEDOWN){
		newStatus = BUTTONSTATUS::MOUSEOVER;
	} else if(_status != BUTTONSTATUS::MOUSEDOWN) {
		newStatus = BUTTONSTATUS::NORMAL;
	}

	if(mouseButtonPressed && mouseOverButton){
		newStatus = BUTTONSTATUS::MOUSEDOWN;
	}

	if(mouseButtonReleased){
		newStatus = BUTTONSTATUS::NORMAL;
	}

	if(mouseButtonReleased && mouseOverButton && _status == BUTTONSTATUS::MOUSEDOWN){
		_callbackFunction();
	}

	bool change = !(_status == newStatus);
	_status = newStatus;
	return change;
}

void Button::disableToggle(){
	if(_status == BUTTONSTATUS::DISABLED){
		_status = BUTTONSTATUS::NORMAL;
	} else {
		_status = BUTTONSTATUS::DISABLED;
	}
}

std::string  Button::getText(){
	return _text;
}

BUTTONSTATUS Button::getStatus(){
	return _status;
}

sf::Vector2f Button::getPostion(){
	return _position;
}

sf::Vector2f Button::getSize(){
	return _size;
}