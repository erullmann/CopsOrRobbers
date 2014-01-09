//button.h 
//provides functions to create and monitor buttons
#pragma once
#include <string>
#include <SFML\Graphics.hpp>

enum BUTTONSTATUS{
	NORMAL,
	MOUSEOVER,
	MOUSEDOWN,
	DISABLED
};

//central struct for buttons
class Button {
public:
	//create button
	//	position: the x and y position of the button
	//	size: the width and height of the button
	//	texture: the teture that the button draws
	//	callbackFunction: the function that is called by the button when pressed
	Button(sf::Vector2f position, sf::Vector2f size, void (*callbackFunction)(void));

	//evaluate button: check if button has been clicked and call callback function if so
	//also changes the button's status
	//	e: mouse click event
	bool handleEvent(sf::Event e);

	//Toggles the disabled status of the button between DISABLED and NORMAL
	void disableToggle();

	std::string  getText();
	sf::Vector2f getPostion();
	sf::Vector2f getSize();
	BUTTONSTATUS getStatus();

private:
	sf::Vector2f _position;
	sf::Vector2f _size;
	std::string _text;
	BUTTONSTATUS _status;

	void (*_callbackFunction)(void);

};