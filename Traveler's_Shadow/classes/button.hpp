#include <SFML/Graphics.hpp>
#pragma once
class Button{
public:
	sf::RectangleShape button;
	sf::Texture buttonTexture;
	Button(int sizeX, int sizeY, std::string pathToTexture, int scale) {
		buttonTexture.loadFromFile(pathToTexture);
		button.setSize(sf::Vector2f(sizeX, sizeY));
		button.setTexture(&buttonTexture);
		button.setScale(scale, scale);

	}
	bool doesContainMouseCursor(sf::RenderWindow& window) {
		if(this->button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) return true;
		else return false;
	}
};