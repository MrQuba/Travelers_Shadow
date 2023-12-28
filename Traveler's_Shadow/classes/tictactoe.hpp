#include <SFML/Graphics.hpp>
#include <tuple>
class TicTacToe {
public:
	enum {
		isEmpty = 1,
		isCircle = 10,
		isCross = 11
	};
	void play(sf::RenderWindow& window, bool& w);
	TicTacToe() {
		for (int i = 0; i < amountOfSquares; i++) {
			squareState[i] = isEmpty;
			square[i].setFillColor(sf::Color::Green);
			square[i].setSize(sf::Vector2f(128, 128));
			square[i].setOutlineColor(sf::Color::Black);
			square[i].setOutlineThickness(8);

		}
		hasPlayerPlayed = false;
		playerTurn = "Your Turn!";
		computerTurn = "Computers Turn!";
		playerWins = "You win!";
		computerWins = "Computer wins!";
		aDraw = "It is a Draw";
		title = "Tic Tac Toe";

		font.loadFromFile("assets/font/ARIAL.TTF");

		turnText.setFont(font);
		turnText.setCharacterSize(64);
		turnText.setFillColor(sf::Color::White);
		turnText.setPosition(5 * square[0].getLocalBounds().width, square[0].getLocalBounds().height);

		winText.setFont(font);
		winText.setCharacterSize(64);
		winText.setFillColor(sf::Color::White);
		winText.setPosition(5 * square[0].getLocalBounds().width, 2 * square[0].getLocalBounds().height);

		exitText.setFont(font);
		exitText.setCharacterSize(32);
		exitText.setFillColor(sf::Color::White);
		exitText.setPosition(5 * square[0].getLocalBounds().width, 3 * square[0].getLocalBounds().height);
		exitText.setString(exit);

		titleText.setFont(font);
		titleText.setCharacterSize(96);
		titleText.setFillColor(sf::Color::Green);
		titleText.setPosition(2.5 * square[0].getLocalBounds().width, 0);
		titleText.setString(title);

		hasAnyoneWon = false;
		hasPlayerWon = false;
	}
	bool hasPlayerWon;
private:
	void draw(sf::RenderWindow& window);
	void computer();
	void colorSquare(sf::RectangleShape& shape, const sf::Color color);
	void placeSquares(sf::RenderWindow& window);
	bool doesContainMouseCursor(sf::RectangleShape& shape, sf::RenderWindow& window);
	bool hasWon(int player);
	const static int amountOfSquares = 9;
	sf::RectangleShape square[amountOfSquares];
	int squareState[amountOfSquares];
	bool hasPlayerPlayed;
	bool hasAnyoneWon;

	std::string playerTurn;
	std::string computerTurn;
	std::string playerWins;
	std::string computerWins;
	std::string aDraw;
	std::string exit;
	std::string title;
	sf::Font font;
	sf::Text turnText;
	sf::Text winText;
	sf::Text titleText;
	sf::Text exitText;

};