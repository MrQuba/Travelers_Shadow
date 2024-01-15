#include "../classes/player.hpp"

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

void Player::shootMissle(sf::Sprite& projectile) {
	if (isShot) {
		shape.move(-1.f, 0.f);
		window.draw(shape);
	}
	else {
		isShot = true;
	}
}

bool Player::attack(sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isAttacking) {
		isAttacking = true;
		return true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) shootMissle()''
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
			if(input.direction == input.Left) swordSprite.setRotation(-angle);
			else swordSprite.setRotation(angle);
			angle += 1;
		}

	}
}
