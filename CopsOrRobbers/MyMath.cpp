//Math.cpp
//provides math utitlity functions
#pragma once
#include "MyMath.h"

float dot(sf::Vector2f a, sf::Vector2f b){
	return a.x*b.x + a.y*b.y;
}

float length(sf::Vector2f a){
	return std::sqrt(a.x*a.x + a.y*a.y);
}

sf::Vector2f unit(sf::Vector2f a){
	return a/length(a);
}

float cross(sf::Vector2f a, sf::Vector2f b){
	return a.x*b.y - a.y*b.x;
}

sf::Vector2f cross(float x, sf::Vector2f a){
	return sf::Vector2f(-x*a.y, x*a.x);
}

sf::Vector2f cross(sf::Vector2f a, float x){
	return sf::Vector2f(x*a.y , -x*a.x);
}

sf::Vector2f right(sf::Vector2f a){
	return sf::Vector2f(-a.y, a.x);
}

sf::Vector2f snap(sf::Vector2f v){
	float signx = v.x/abs(v.x);
	float signy = v.y/abs(v.y);
	bool snapx = ((abs(v.x) - abs(v.y)) >= 0);
	return sf::Vector2f(signx*snapx, signy*(!snapx));
}