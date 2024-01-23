#include <SFML/Graphics.hpp>

class Window {
public:
	Window(int sizeX, int sizeY, std::string title) {
		window.create(sf::VideoMode(sizeX, sizeY), title);
	}
	~Window() {
		std::cout << "Destructed Window Object" << std::endl;
	}
	sf::RenderWindow window;
};