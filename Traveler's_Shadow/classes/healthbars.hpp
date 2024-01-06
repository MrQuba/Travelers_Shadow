#include <SFML/Graphics.hpp>

class HealthBars {
public:
	HealthBars(int sizeX, int sizeY, int scaleX, int scaleY, sf::Color color, sf::Color background) {
		Bar.setSize(sf::Vector2f(sizeX * scaleX, sizeY * scaleY));
		BarBackground.setSize(sf::Vector2f(sizeX * scaleX, sizeY * scaleY));

		Bar.setFillColor(color);
		BarBackground.setFillColor(background);
 }
	sf::RectangleShape Bar;
	sf::RectangleShape BarBackground;
};