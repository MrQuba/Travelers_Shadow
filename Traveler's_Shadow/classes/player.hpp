#include "entity.hpp"
class Player : public Entity {
public:
	Player(std::string pathToTexture = "", int startX = 0, int startY = 0, int sizeX = 0, int sizeY = 0, const int scale = 1) : Entity(pathToTexture, startX, startY, sizeX, sizeY, scale) {
		this->jumpHeight = 600;
		groundLevel = 650;
		health = maxHealth;
		directionOld = input.Left;
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

		isAttacking = false;
		angle = 0;
		createSword();

		playerHealthBarHeight = 24;

		isShot = false;
		isAvalible = true;

		create = true;

	}
	Math calculate;
	Collisions player;
	Collisions shotMissle;
	Collisions swordSwing;
	Input input;
	Animation animation{ 25 ,"assets/graphics/entities/playerSprite.png" , 16, 16, 0, 0 };
	Entity missle{"assets/graphics/entities/playerProjectile.png", 0, 0, 16, 16, 2};
	HealthBars playerHealth{ health, playerHealthBarHeight, 1, 1, sf::Color::Red, sf::Color::Black };

	int groundLevel;
	void groundCollision();

	int directionOld;
	void flipSprite(sf::RenderWindow& window);

	void borderCollisions(sf::RenderWindow& window);

	void isMoving();

	void createSword();
	sf::Texture swordTexture;
	sf::Sprite swordSprite;

	void shootMissle(sf::Sprite& projectile, sf::RenderWindow& window);
	bool isShot;
	bool isAvalible;
	sf::Vector2f targetPosition;

	bool attack(sf::RenderWindow& window);
	int angle;
	bool isAttacking;

	int playerHealthBarHeight;

	bool create;
	const int maxHealth = 200;
	void specificUpdate(sf::RenderWindow& window) override {
		if (0 == health) isAlive = false;
		float setHealthBarPosition = window.getSize().x - health;

		playerHealth.Bar.setSize(sf::Vector2f(health, playerHealthBarHeight));
		playerHealth.BarBackground.setSize(sf::Vector2f(maxHealth, playerHealthBarHeight));
		if (create) {
			create = false;
			playerHealth.BarBackground.setPosition(sf::Vector2f(setHealthBarPosition / 2, playerHealthBarHeight));
			playerHealth.Bar.setPosition(sf::Vector2f(setHealthBarPosition / 2, playerHealthBarHeight));
		}

		flipSprite(window);

		if (this->velocity.y >= 72) this->velocity.y = 72;
		this->sprite.move(velocity);

		groundCollision();
		borderCollisions(window);

		isMoving();
		attack(window); 

		if(isAttacking)
		window.draw(swordSprite);

		window.draw(playerHealth.BarBackground);
		window.draw(playerHealth.Bar);
	}

	int hitBoss(sf::Sprite& sprt) override {
		if (shotMissle.spritesIntersect(missle.sprite, sprt) && isShot) {
			isAvalible = true;
			isShot = false;
			return 5;
		}
	}
	int hitBossMelee(sf::Sprite & sprt) override {
			if (swordSwing.spritesIntersect(swordSprite, sprt) && isAttacking) {
				return 2;
			}
		else return 0;
	}
	int hitByBoss(sf::Sprite& sprt) override {
		if (swordSwing.spritesIntersect(sprite, sprt) ) {
			return 2;
		}
		else return 0;
	}
};