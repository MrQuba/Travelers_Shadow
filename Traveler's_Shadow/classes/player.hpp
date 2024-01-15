#include "entity.hpp"
class Player : public Entity {
public:
	Player(std::string pathToTexture, int startX, int startY, int sizeX, int sizeY, const int scale) : Entity(pathToTexture, startX, startY, sizeX, sizeY, scale) {
		this->jumpHeight = 600;
		groundLevel = 650;
		health = 255;
		directionOld = input.Left;
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

		isAttacking = false;
		angle = 0;
		createSword();


		isShot = false;
		isAvalible = true;

	}
	Math calculate;
	Collisions player;
	Input input;
	Animation animation{ 25 ,"assets/graphics/entities/playerSprite.png" , 16, 16, 0, 0 };

	int groundLevel;
	void groundCollision();

	int directionOld;
	void flipSprite(sf::RenderWindow& window);

	void borderCollisions(sf::RenderWindow& window);

	void isMoving();

	void createSword();
	sf::Texture swordTexture;
	sf::Sprite swordSprite;

	void shootMissle(sf::Sprite& projectile);
	sf::Sprite missle;
	sf::Texture missleTexture;
	bool isShot;
	bool isAvalible;
;
	bool attack(sf::RenderWindow& window);
	int angle;
	bool isAttacking;

	void specificUpdate(sf::RenderWindow& window) override {
		flipSprite(window);

		if (this->velocity.y >= 72) this->velocity.y = 72;
		this->sprite.move(velocity);

		groundCollision();
		borderCollisions(window);

		isMoving();
		attack(window); 
		if(isAttacking)
		window.draw(swordSprite);
		if (isShot) {
		}
	}
};