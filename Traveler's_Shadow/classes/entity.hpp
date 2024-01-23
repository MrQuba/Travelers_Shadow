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
		currentInvincibilityFrames = 0;
		isHit = false;
		gotHit = false;
	}
		~Entity(){}

	sf::Sprite sprite;
	sf::Texture texture;
	int health;
	float const gravity = 9.81;
	float jumpHeight;

	bool isAlive;

	bool isHit;
	bool gotHit;
	const int maxInvincibilityFrames = 96;
	int currentInvincibilityFrames;

	void invinvibilityFrames() {
		if (0 == currentInvincibilityFrames) isHit = false;
		if (gotHit && !isHit) {
			gotHit = false;
			currentInvincibilityFrames = maxInvincibilityFrames;
			isHit = true;
		}
		if (isHit) {
			currentInvincibilityFrames--;
		}
	}

	int currentSector;

	sf::Vector2f velocity;
	virtual int hitBoss(sf::Sprite& sprt, bool isBossHit, bool& bossGotHit) {
			return 0;
	}
	virtual int hitBossMelee(sf::Sprite& sprt, bool isBossHit, bool& bossGotHit) {
		return 0;
	}
	virtual int hitByBoss(sf::Sprite& sprt) {
		return 0;
	}
	bool update(sf::RenderWindow& window) {
		if (!this->isAlive) return false;
		if (this->health <= 0) this->isAlive = false;

		specificUpdate(window);
		window.draw(this->sprite);
		return true;
	}
	virtual bool specificUpdate(sf::RenderWindow& window) {
		return false;
	}
};
