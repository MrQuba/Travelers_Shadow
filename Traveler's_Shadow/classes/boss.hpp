#include "entity.hpp"
class Boss : public Entity {
public:
	Boss(std::string pathToTexture, int startX, int startY, int sizeX, int sizeY, const int scale) : Entity(pathToTexture, startX, startY, sizeX, sizeY, scale) {
		speed = 125;
		health = 1000;
		isMovingLeft = true;
		angle = 1;
		bossHealthBarHeight = 24;
		create = true;
		spins = false;

		currentSpinProjectile = 0;
		for (int i = 0; i < amountOfSpinProjectiles; i++) {
			spinProjectile->setFillColor(sf::Color::Green);
			spinProjectile->setRadius(5.f);
		}

	}
	void specificUpdate(sf::RenderWindow& window) override {
		float setHealthBarPosition = window.getSize().x - health;
		if (create) {
			create = false;
			bossHealth.BarBackground.setPosition(sf::Vector2f(setHealthBarPosition / 2, window.getSize().y - bossHealthBarHeight));
			bossHealth.Bar.setPosition(sf::Vector2f(setHealthBarPosition / 2, window.getSize().y - bossHealthBarHeight));
		}

		bossMove(window, sprite);

		spins = true;
		bossSpins(window);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) health -= 10;

		bossHealth.Bar.setSize(sf::Vector2f(health, bossHealthBarHeight));
		bossHealth.BarBackground.setSize(sf::Vector2f(maxHealth, bossHealthBarHeight));
		window.draw(bossHealth.BarBackground);
		window.draw(bossHealth.Bar);
	}
private:
	int bossHealthBarHeight;
	const int maxHealth = 1000;

	bool isMovingLeft;
	float speed;

	bool create;

	bool spins;
	int angle;
	const static int amountOfSpinProjectiles = 36;
	sf::CircleShape spinProjectile[amountOfSpinProjectiles];
	int currentSpinProjectile;

	Collisions boss;
	HealthBars bossHealth{ health, bossHealthBarHeight, 1, 1, sf::Color::Red, sf::Color::Black };
	void bossMove(sf::RenderWindow& window, sf::Sprite& sprite) {
		if (isMovingLeft) {
			sprite.move(-12.5f, 0);
			if (boss.collidesWithBorder(sprite, sprite.getLocalBounds().width * sprite.getScale().x, true)) isMovingLeft = false;
		}
		else {
			sprite.move(12.5f, 0);
			if (boss.collidesWithBorder(sprite, window.getSize().x - (sprite.getLocalBounds().width * sprite.getScale().x), true)) isMovingLeft = true;
		}

	}
	bool bossSpins(sf::RenderWindow& window) {
		if (!spins) return false;
		if (spins) {
			if (angle > 360) {
				angle = 1;
				spins = false;
				currentSpinProjectile = 0;
				return false;
			}
			this->sprite.rotate(angle);
			if (angle % 10 == 0) {
				window.draw(spinProjectile[currentSpinProjectile]);
				currentSpinProjectile++;
			}
		}
	}
};