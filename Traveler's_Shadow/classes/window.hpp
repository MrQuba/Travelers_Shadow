#include <SFML/Graphics.hpp>

class Window {
public:
	Window(int sizeX, int sizeY, std::string title) {
		std::cout << "Created Window Object" << std::endl;
		window.create(sf::VideoMode(sizeX, sizeY), title);
	}
	~Window() {
		std::cout << "Destructed Window Object" << std::endl;
	}
	sf::RenderWindow window;
};