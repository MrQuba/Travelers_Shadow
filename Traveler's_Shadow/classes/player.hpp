#include "entity.hpp"
class Player : public Entity {
public:
	Player(std::string pathToTexture, int startX, int startY, int sizeX, int sizeY, const int scale) : Entity(pathToTexture, startX, startY, sizeX, sizeY, scale) {
		this->jumpHeight = 600;
		groundLevel = 650;
		health = 255;
		directionOld = input.Left;

		isAttacking = false;
		angle = 0;
		createSword();
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

	bool isAttacking;
	bool attack();
	int angle;

	void specificUpdate(sf::RenderWindow& window) override {
		flipSprite(window);

		if (this->velocity.y >= 72) this->velocity.y = 72;
		this->sprite.move(velocity);

		groundCollision();
		borderCollisions(window);

		isMoving();
		attack();
		if(isAttacking)
		window.draw(swordSprite);
	}
};