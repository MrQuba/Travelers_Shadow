#include <SFML/Graphics.hpp>
#include "math.hpp"
#pragma once
class Input {
public:
	Math calculate;
	Input() {
		isMoving = false;
		isJumping = false;
		speed = 2;
		direction = None;
		canJump - true;
		isFacing = None;
		dashCooldown = 0;
		dashed = false;
	}
	virtual ~Input() {
		isMoving = false;
	}
	enum {
		None = 0,
		Up = 1000,
		Down = 100,
		Left = 1100,
		Right = 10,
		MouseLeft = 1010,
		MouseRight = 110,
		Exit = 1110
	};
	bool isMoving;
	bool isJumping;
	sf::Vector2f velocity;
	float dashAcceleration;
	float speed;
	float jumpHeight;
	int direction;
	bool canJump;
	int isFacing;
	int dashCooldown;
	bool dashed;
	float moveLeft(float speed) {
		float velocityX = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			direction = Left;
			isFacing = Left;
			velocityX = speed;
			return -velocityX;
		}	
			return 0;
	}
	float moveRight(float speed) {
		float velocityX = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			direction = Right;
			isFacing = Right;
			velocityX = speed;
			return velocityX;
		}
		return 0;
	}
	float jump() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump) {
			isJumping = true; 
			canJump = false;
			return -9.8;
		}
		else return 0;
	}
	sf::Vector2f movementManager(float deltaTime, sf::Sprite& entity, sf::RenderWindow& window) {
		sf::Event input;
		this->velocity.x = moveRight(this->speed) + this->moveLeft(this->speed);
		this->velocity.y += jump();

		if (isJumping) this->velocity.y += 0.15f;

		while (window.pollEvent(input)) {
			if (input.type == sf::Event::KeyReleased && input.key.code == sf::Keyboard::A) this->velocity.x = 0;
			if (input.type == sf::Event::KeyReleased && input.key.code == sf::Keyboard::D) this->velocity.x = 0;
		}
		if (this->velocity.x > 0 && this->direction == Left) this->velocity.x *= -1;
		if (this->velocity.x < 0 && this->direction == Right) this->velocity.x *= -1;
		if (this->velocity.x == 0) isMoving = false;
		if (0 != this->velocity.x) isMoving = true;
		return velocity;
	}
};