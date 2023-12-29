#include <SFML/Graphics.hpp>
#include <iostream>
#include "math.hpp"
#include "input.hpp"
#include "collisions.hpp"
#include "animation.hpp"

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
		else {
			if (this->health <= 0) this->isAlive = false;

			specificUpdate(window);
			window.draw(this->sprite);
			return true;
		}
	}
	 virtual void specificUpdate(sf::RenderWindow& window) {
		 std::cout << "entity" << std::endl;

	 }
};
class Player : public Entity {
public:
	Player(std::string pathToTexture, int startX, int startY, int sizeX, int sizeY, const int scale) : Entity(pathToTexture, startX, startY, sizeX, sizeY, scale){
		this->jumpHeight = 600;
		mass = 75;
		groundLevel = 650;
		health = 255;
		directionOld = input.Left;

	}
	Math calculate;
	Collisions player;
	Input input;
	Animation animation{ 25 ,"assets/graphics/entities/playerSprite.png" , 16, 16, 0, 0};
	int groundLevel;
	float mass;
	int directionOld;


	void specificUpdate(sf::RenderWindow& window) override {
		directionOld = input.direction;
		velocity = input.movementManager(1, this->sprite, window);
		if (directionOld != input.direction) this->sprite.scale(-1, 1);
		if (this->velocity.y >= 72) this->velocity.y = 72;
		this->sprite.move(velocity);
		if (player.collidesWithGround(this->sprite, groundLevel)) {
			input.canJump = true;
			input.isJumping = false;
		}
		player.collidesWithBorder(this->sprite, 0, true);
		player.collidesWithBorder(this->sprite, window.getSize().x - (this->sprite.getLocalBounds().width * this->sprite.getScale().x), false);
		if (input.isMoving) {
			std::cout << input.isMoving << std::endl;
			animation.animate(this->sprite);
		}
		else this->sprite.setTexture(this->texture);
	}
};