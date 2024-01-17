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

	Entity(std::string pathToTexture = "", int startX = 0, int startY = 0, int sizeX = 0, int sizeY = 0, float scale = 1) {
		texture.loadFromFile(pathToTexture, sf::IntRect(startX, startY, sizeX, sizeY));
		sprite.setTexture(texture);
		sprite.scale(scale, scale);
		this->jumpHeight = 1;
		isAlive = true;
		currentSector = isInStartingRoom;
	}
		~Entity(){}

	sf::Sprite sprite;
	sf::Texture texture;
	int health;
	float const gravity = 9.81;
	float jumpHeight;

	bool isAlive;

	int currentSector;

	sf::Vector2f velocity;
	virtual int hitBoss(sf::Sprite& sprt) {
		std::cout << "to override";
			return 0;
	}
	virtual int hitBossMelee(sf::Sprite& sprt) {
		std::cout << "to override";
		return 0;
	}
	virtual int hitByBoss(sf::Sprite& sprt) {
		std::cout << "to override";
		return 0;
	}
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
