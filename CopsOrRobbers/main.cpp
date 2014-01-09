#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Character.h"
#include "PhysicsManager.h"
#include "Map.h"
#include <iostream>

bool _close = false;
bool gamePaused = true;
bool gameStarted = false;

void startGame(){
	gameStarted = true;
	gamePaused = false;
}

void close(){
	_close = true;
}

Rectangle rectangle(5, 10);

Rectangle bottom(10, 300);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Cops or Robbers");

	List<Button> buttons;
	Button b(sf::Vector2f(200, 100), sf::Vector2f(200, 50), close);
	Button c(sf::Vector2f(200, 300), sf::Vector2f(200, 50), startGame);
	buttons.pushBack(&b);
	buttons.pushBack(&c);
	Menu mainMenu(&buttons, "buttons.png");
	mainMenu.enableMenu();

	PhysicsManager physics;
	Map worldMap("testmap.tmx", physics);

	Character* body = new Character(sf::Vector2f(100, 150), sf::Vector2f(-1, 0), "theguy.png");
	ActionComponent* action = body->getAction();
	physics.addPhysicsObject((CollisionVolume*) body->getPhysics());

	sf::RenderStates states;
	
	sf::Clock clock;
	clock.restart();
	float accumulator = 0;
	window.clear(sf::Color::White);

	while (window.isOpen())
	{
		sf::Time delta = clock.restart();
		accumulator += delta.asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
				mainMenu.enableMenu();
				gamePaused = true;
			}
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P && gameStarted){
				gamePaused = !gamePaused;
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				action->goRight();
			
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				action->goLeft();

			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				action->jump();

			mainMenu.handleEvent(event);
		}

		if (_close)
			window.close();

		window.clear(sf::Color::White);

		if(!gamePaused){
			mainMenu.disableMenu();
			physics.updatePhysics(delta);
		}
		if(gameStarted){
			window.draw(worldMap);
			physics.d_drawPhysics(window, states);
			body->update(window, states);
		}
		
		if(accumulator >= 1.0){
			if(!gamePaused) std::cout<<"FPS " << 1/delta.asSeconds() << "\n";
			accumulator = 0;
		}

		mainMenu.draw(window, states);
		window.display();
	}

	return 0;
}