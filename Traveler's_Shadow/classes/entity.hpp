#include <SFML/Graphics.hpp>
#include <iostream>
#include "math.hpp"
#include "input.hpp"
#include "collisions.hpp"
#include "animation.hpp"
#include "healthbars.hpp"
#pragma once
class Entity {
public:
	enum {
		isInStartingRoom = 1,
		isInTicTacToeRoom = 10,
		isInRockPaperScissorsRoom = 11,
		isInBossRoom = 100
	};
	float const gravity = 9.81;

	Entity(std::string pathToTexture, int startX, int startY, int sizeX, int sizeY, float scale) {
		texture.loadFromFile(pathToTexture, sf::IntRect(startX, startY, sizeX, sizeY));
		sprite.setTexture(texture);
		sprite.scale(scale, scale);
		this->jumpHeight = 1;
		isAlive = true;
		currentSector = isInStartingRoom;
	}
	sf::Sprite sprite;
	sf::Texture texture;
	float jumpHeight;
	bool isAlive;
	int health;
	int currentSector;
	sf::Vector2f velocity;
	 bool update(sf::RenderWindow& window) {
		if (!this->isAlive) return false;
			if (this->health <= 0) this->isAlive = false;

			specificUpdate(window);
			window.draw(this->sprite);
			return true;
	}
	 virtual void specificUpdate(sf::RenderWindow& window) {
		 std::cout << "entity" << std::endl;

	 }
};
