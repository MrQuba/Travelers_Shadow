#include "entity.hpp"
#include <cmath>
#include <ctime>
class Boss : public Entity {
public:
	bool isAlive;
	Boss(std::string pathToTexture, int startX, int startY, int sizeX, int sizeY, const int scale) : Entity(pathToTexture, startX, startY, sizeX, sizeY, scale) {
		speed = 1.25f;
		health = maxHealth;
		isMovingLeft = true;
		angle = 1;
		bossHealthBarHeight = 24;
		create = true;
		spins = false;
		isAlive = true;


		currentDelay = maxDelay;

		currentSpinProjectile = 0;
		for (int i = 0; i < amountOfSpinProjectiles; i++) {
			spinProjectile->setFillColor(sf::Color::Green);
			spinProjectile->setRadius(5.f);
		}

	}
	bool specificUpdate(sf::RenderWindow& window) override {

		if (health <= health / 2) speed *= 4;

		float setHealthBarPosition = window.getSize().x - health;

		bossHealth.Bar.setSize(sf::Vector2f(health, bossHealthBarHeight));
		bossHealth.BarBackground.setSize(sf::Vector2f(maxHealth, bossHealthBarHeight));
		if (create) {
			create = false;
			bossHealth.BarBackground.setPosition(sf::Vector2f(setHealthBarPosition / 2, window.getSize().y - bossHealthBarHeight));
			bossHealth.Bar.setPosition(sf::Vector2f(setHealthBarPosition / 2, window.getSize().y - bossHealthBarHeight));
		}

		bossMove(window, sprite);

		spins = true;
		bossSpins(window);
		invinvibilityFrames();


		window.draw(bossHealth.BarBackground);
		window.draw(bossHealth.Bar);
		return true;
	}
private:
	int groundLevel;

	int bossHealthBarHeight;
	const int maxHealth = 750;

	bool isMovingLeft;
	float speed;

	bool create;

	bool spins;
	int angle;
	const static int amountOfSpinProjectiles = 36;
	sf::CircleShape spinProjectile[amountOfSpinProjectiles];
	int currentSpinProjectile;

	const int maxDelay = 750;
	int currentDelay;

	Collisions boss;
	HealthBars bossHealth{ health, bossHealthBarHeight, 1, 1, sf::Color::Red, sf::Color::Black };
	void bossMove(sf::RenderWindow& window, sf::Sprite& sprite) {
		srand(time(NULL));
		if (isMovingLeft) {
			sprite.move(-speed, 0);
			if (boss.collidesWithBorder(sprite, sprite.getLocalBounds().width * sprite.getScale().x, true)) isMovingLeft = false;
		}
		else {
			sprite.move(speed, 0);
			if (boss.collidesWithBorder(sprite, window.getSize().x - (sprite.getLocalBounds().width * sprite.getScale().x), true)) isMovingLeft = true;
		}
		if (currentDelay > 0) currentDelay--;
		else {
			currentDelay = maxDelay;
			switch (rand() % 4) {
			case 0:
				sprite.setPosition(sprite.getPosition().x, sprite.getLocalBounds().height);
				break;
			case 1:
				sprite.setPosition(sprite.getPosition().x, window.getSize().y - (2 * sprite.getLocalBounds().height));
				break;
			case 2:
				sprite.setPosition(sprite.getPosition().x, window.getSize().y / 2);
				break;
			default: break;
			}
		}
	}
	bool bossSpins(sf::RenderWindow& window);

};