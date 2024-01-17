#include <SFML/Graphics.hpp>
#include <iostream>
#pragma once
class Collisions {
public:
	bool collidesWithGround(sf::Sprite& entity, int& groundLevel) {
		if (entity.getPosition().y + entity.getLocalBounds().height >= groundLevel) {
			entity.setPosition(entity.getPosition().x, groundLevel - entity.getLocalBounds().height);
			return true;
		}
		else return false;
	}
	bool collidesWithBorder(sf::Sprite& entity, int borderPos, bool facingLeft) {
		if (facingLeft)
			if (entity.getPosition().x + entity.getLocalBounds().width <= borderPos) {
				entity.setPosition(borderPos - entity.getLocalBounds().width, entity.getPosition().y);
				return true;
			}
			else return false;
		if(!facingLeft)
			if (entity.getPosition().x - entity.getLocalBounds().width >= borderPos) {
				entity.setPosition(borderPos + entity.getLocalBounds().width, entity.getPosition().y);
				return true;
			}
			else return false;
	}
	bool spritesIntersect(sf::Sprite& s1, sf::Sprite& s2) {
		if (s1.getGlobalBounds().intersects(s2.getGlobalBounds()))
			return true;
		else return false;
	}
};