#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "button.hpp"
class RockPaperScissors {
public:
	enum {
		Nothing = 0,
		Rock = 1,
		Paper = 10,
		Scissors = 11,
		Error = 100,
		Tie = 101,
		Win = 110,
		Loss = 111
	};

	RockPaperScissors() {
		playerWins = "You win!";
		computerWins = "Computer wins!";
		aDraw = "It is a Draw";
		title = "Rock Paper Scissors";

		font.loadFromFile("assets/font/ARIAL.TTF");

		winText.setFont(font);
		winText.setCharacterSize(64);
		winText.setFillColor(sf::Color::White);
		winText.setPosition(5 * winText.getLocalBounds().width, 300);

		titleText.setFont(font);
		titleText.setCharacterSize(96);
		titleText.setFillColor(sf::Color::Green);
		titleText.setString(title);
		titleText.setPosition(250, 0);
		texture.loadFromFile("assets/buttons/emptyButton.png");
		displayComputerPlayed.setTexture(&texture);

		hasPlayerWon = false;
	}

	int played = Nothing;
	int computerPlayed = Nothing;
	sf::RectangleShape displayComputerPlayed;
	sf::Texture texture;
	bool hasPlayerWon;
	void draw(sf::RenderWindow& window, sf::RectangleShape& rs, sf::RectangleShape& rs2, sf::RectangleShape& rs3, sf::RectangleShape& cP) {
		window.draw(rs);
		window.draw(rs2);
		window.draw(rs3);
		window.draw(this->displayComputerPlayed);
		window.draw(this->titleText);
		window.draw(this->winText);
	}
	int play(sf::RenderWindow& window) {
		displayComputerPlayed.setSize(sf::Vector2f(200, 100));
		Button rock(200, 100, "assets/buttons/rockButton.png", 1);
		Button paper(200, 100, "assets/buttons/paperButton.png", 1);
		Button scissors(200, 100, "assets/buttons/scissorsButton.png", 1);
		rock.button.setPosition(rock.button.getLocalBounds().width, window.getSize().y - rock.button.getLocalBounds().height);
		paper.button.setPosition(3 * paper.button.getLocalBounds().width, window.getSize().y - paper.button.getLocalBounds().height);
		scissors.button.setPosition(5 * scissors.button.getLocalBounds().width, window.getSize().y - scissors.button.getLocalBounds().height);
		
		if (!hasPlayerWon) {
			if (rock.doesContainMouseCursor(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				played = Rock;
			}
			else if (paper.doesContainMouseCursor(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				played = Paper;
			}
			else if (scissors.doesContainMouseCursor(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				played = Scissors;
			}
			else {
				played = Nothing;
			}
			if (played != Nothing) {
				computerPlayed = ai();
				switch (computerPlayed)
				{
				case Rock:
					this->texture.loadFromFile("assets/buttons/rockButton.png");
					break;
				case Paper:
					this->texture.loadFromFile("assets/buttons/paperButton.png");
					break;
				case Scissors:
					this->texture.loadFromFile("assets/buttons/scissorsButton.png");
					break;
				}
				if (played == computerPlayed) {
					winText.setString(aDraw);
					return Tie;
				}
				switch (played) {
				case Rock:
					if (computerPlayed == Paper) {
						winText.setString(computerWins);
						return Loss;
					}
					else {
						winText.setString(playerWins);
						return Win;
					}
					break;
				case Paper:
					if (computerPlayed == Scissors) {
						winText.setString(computerWins);
						return Loss;
					}
					else {
						winText.setString(playerWins);
						return Win;
					}
					break;
				case Scissors:
					if (computerPlayed == Rock) {
						winText.setString(computerWins);
						return Loss;
					}
					else {
						winText.setString(playerWins);
						return Win;
					};
					break;
				default: return Error;
				}
			}
			this->displayComputerPlayed.setTexture(&this->texture);


		draw(window, rock.button, paper.button, scissors.button, this->displayComputerPlayed);
		}
	}
	int ai() {
		srand(time(NULL));
		int randVal = rand() % 3 + 1;
		switch (randVal)
		{
		case 1: return Rock;
		case 2: return Paper;
		case 3: return Scissors;
		default: return Error;
		}
	}
	private:
		std::string playerWins;
		std::string computerWins;
		std::string aDraw;
		std::string title;
		sf::Text winText;
		sf::Text titleText;
		sf::Font font;
};