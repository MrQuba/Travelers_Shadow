#include <SFML/Graphics.hpp>
#include "math.hpp"
#pragma once
class Input {
public:
	Math calculate;
	Input(float jH) {
		isMoving = false;
		isFalling = false;
		isJumping = false;
		jumpAcceleration = 2.5;
		acceleration = 9;
		jumpHeight = jH;
		direction = None;
		canJump - true;
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
	bool isFalling;
	bool isJumping;
	sf::Vector2f velocity;
	float jumpAcceleration;
	float acceleration;
	float jumpHeight;
	int direction;
	bool canJump;
	float moveLeft(float& acceleration, float velocityX) {
		float velocityX_n = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			this->direction = Left;
			velocityX_n = (velocityX + acceleration);
			return -velocityX_n;
		}
		else return 0;
	}
	float moveRight(float& acceleration, float velocityX) {
		float velocityX_n = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			this->direction = Right;
			velocityX_n = (velocityX + acceleration);
			return velocityX_n;
		}
		else return 0;
	}
	float moveUp(float jumpHeight, float positionX, float incrementPositionY, bool state, float deltaTime) {
		float result;
		bool isFalling;
		if (state) isFalling = false;
		else isFalling = true;
		result = calculate.canonicalQuadraticFunction(isFalling, incrementPositionY, positionX, jumpHeight) * deltaTime;
		return result;
	}
	float fallFaster(float fallSpeed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			return fallSpeed * 5.2;
		else return fallSpeed;
	}
	float dash(float velocity) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) return velocity * 3.5;
		else return velocity;
	}
	sf::Vector2f movementManager(float deltaTime, sf::Sprite& entity, sf::RenderWindow& window) {
		sf::Event input;
		this->velocity.x = (moveRight(this->acceleration, this->velocity.x) / 50) + (this->moveLeft(this->acceleration, this->velocity.x) / 50);
		if(this->acceleration < 35 )this->acceleration += 0.5;

		velocity.x = dash(velocity.x);
		while (window.pollEvent(input)) {
			if (input.type == sf::Event::KeyReleased && input.key.code == sf::Keyboard::A || input.key.code == sf::Keyboard::Left) this->velocity.x = 0;
			if (input.type == sf::Event::KeyReleased && input.key.code == sf::Keyboard::D || input.key.code == sf::Keyboard::Right) this->velocity.x = 0;
		}
		if (this->velocity.x > 0 && this->direction == Left) this->velocity.x *= -1;
		if (this->velocity.x < 0 && this->direction == Right) this->velocity.x *= -1;
		if (this->velocity.x == 0) this->isMoving = false;
		return velocity;
	}
};