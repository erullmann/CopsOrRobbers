//Menu.h
#pragma once
#include "Button.h"
#include "List.cpp"
#include "ListIter.cpp"
#include <SFML\Graphics.hpp>

class Menu: public sf::Drawable {
public:

	Menu(List<Button>* buttons, const std::string& tileset);

	//activates/diavtiates this menu
	//	toggler: menu that toggled this menu (useful for back buttons and such)
	void disableMenu();
	void enableMenu();

	//passes events onto buttons if menu is active
	//no action otherwise
	//	e: the current event
	void handleEvent(sf::Event e);

	//draws this menu and it's buttons if it is active
	//no action otherwise
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void assignTextures();

private:

	List<Button>* _buttons;

	bool _isActive;

	sf::Texture _textureSet;
	sf::VertexArray _vertices;

};