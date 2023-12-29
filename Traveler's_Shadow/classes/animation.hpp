#include <SFML/Graphics.hpp>

class Animation {
public:
	Animation(int interval, std::string path, int sizeX, int sizeY, int startX, int startY) {
		texture.loadFromFile(path, sf::IntRect(startX, startY, sizeX, sizeY));
		this->interval = interval;
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		this->startX = 0;
		this->startY = 0;
		this->path = path;
		count = 0;
		frame = 0;
	}
	sf::Texture texture;
	int frame;
	int count;
	int interval;
	std::string path;
	int sizeX, sizeY, startX, startY;
	int animate(sf::Sprite& sprite) {
		if (4 > frame) {
			if (count < this->interval) {
				count++;
				return count;
			}
			else if (count == this->interval) {
				frame++;
				count = 0;
				std::cout << "Frame: " << frame << std::endl
					<< "Start X: " << startX * frame << " Start Y: " << startY << std::endl;
				texture.loadFromFile(this->path, sf::IntRect(sizeX * frame, startY, sizeX, sizeY));
				sprite.setTexture(texture);
			}
		}
		else if(4 <= frame) frame = 0;
	}
};