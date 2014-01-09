#pragma once
#include "SFML\Graphics.hpp"

float dot(sf::Vector2f a, sf::Vector2f b);

float length(sf::Vector2f a);

sf::Vector2f unit(sf::Vector2f a);

float cross(sf::Vector2f a, sf::Vector2f b);

sf::Vector2f cross(float x, sf::Vector2f a);

sf::Vector2f cross(sf::Vector2f a, float x);

sf::Vector2f right(sf::Vector2f a);

sf::Vector2f snap(sf::Vector2f a);//snaps vector to unit vector of four cardinal directions