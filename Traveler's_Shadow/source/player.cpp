#include "../classes/player.hpp"
#include <cmath>
void Player::flipSprite(sf::RenderWindow& window) {
	directionOld = input.direction;
	velocity = input.movementManager(1, this->sprite, window);
	if (directionOld != input.direction) {
		this->sprite.scale(-1, 1);
		swordSprite.scale(-1, 1);
	}
}

void Player::groundCollision() {
	if (player.collidesWithGround(this->sprite, groundLevel)) {
		input.canJump = true;
		input.isJumping = false;
	}
}

void Player::borderCollisions(sf::RenderWindow& window) {
	player.collidesWithBorder(this->sprite, 0, true);
	player.collidesWithBorder(this->sprite, window.getSize().x - (this->sprite.getLocalBounds().width * this->sprite.getScale().x), false);
}

void Player::isMoving() {
	if (input.isMoving) {
		animation.animate(this->sprite);
	}
	else this->sprite.setTexture(this->texture);
}

void Player::createSword() {
	swordTexture.loadFromFile("assets/graphics/entities/sword.png");
	swordSprite.setTexture(swordTexture);
	swordSprite.setScale(-4.f, 4.f);
	swordSprite.setOrigin(sf::Vector2f(0, swordSprite.getLocalBounds().height));
}

void Player::shootMissle(sf::Sprite& projectile, sf::RenderWindow& window) {
	sf::Vector2f direction;
	float speed = 5.f;

	if (isShot) {
		if (isAvalible) {
			projectile.setPosition(sprite.getPosition());
			isAvalible = false;
			targetPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		}

		if (shotMissle.collidesWithBorder(projectile, 0, true) ||
			shotMissle.collidesWithBorder(projectile, 1280, false) ||
			projectile.getPosition().y == 0 ||
			projectile.getPosition().y == window.getSize().y) {
			isShot = false;
			isAvalible = true;
		}
		direction = targetPosition - sprite.getPosition();
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		if (length != 0) {
			direction /= length;
		}
		projectile.move(direction * speed);

	}
	else {

		projectile.setPosition(-1000, -1000);
	}
}

bool Player::attack(sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isAttacking) {
		isAttacking = true;
		return true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && isAvalible) isShot = true;
	shootMissle(missle.sprite, window);
	if (isAttacking) {
		swordSprite.setPosition(sprite.getPosition().x, sprite.getPosition().y);
		std::cout << angle << std::endl;
		if (angle > 120) {
			angle = 0;
			if (input.direction == input.Left)
				swordSprite.setRotation(-270);
			else
				swordSprite.setRotation(270);
			isAttacking = false;
			return false;
		}
		else {
			if (input.direction == input.Left) swordSprite.setRotation(-angle);
			else swordSprite.setRotation(angle);
			angle += 1;
		}
		if (isShot) window.draw(missle.sprite);
	}
}
