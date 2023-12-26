#include "../classes/tictactoe.hpp"
#include <iostream>
#include <cmath>
#include <ctime>
void TicTacToe::draw(sf::RenderWindow& window) {
	for (int i = 0; i < amountOfSquares; i++) window.draw(square[i]);
}
void TicTacToe::placeSquares(sf::RenderWindow& window) {
	int multiplierX = 1;
	int multiplierY = 1;
	int x = 0;
	for (int i = 0; i < amountOfSquares; i++) {
		if (i == 0) {
			square[i].setPosition(square[i].getLocalBounds().width, square[i].getLocalBounds().height);
			continue;
		}
		if (x < 2 ) {
			x++;
			multiplierX++;
		}
		else {
			x = 0;
			multiplierX = 1;
			multiplierY++;
		}
		square[i].setPosition(multiplierX * square[i].getLocalBounds().width, multiplierY * square[i].getLocalBounds().height);
		
	}
}
void TicTacToe::colorSquare(sf::RectangleShape& shape, const sf::Color color) {
	shape.setFillColor(color);
}
bool TicTacToe::doesContainMouseCursor(sf::RectangleShape& shape, sf::RenderWindow& window) {
	if (shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) return true;
	else return false;
}
void TicTacToe::computer() {
	srand(time(NULL));
	while (hasPlayerPlayed) {
		hasPlayerPlayed = false;
		if (squareState[4] == isEmpty) {
			squareState[4] = isCross;
			break;
		}
		else if (squareState[0] == isEmpty) {
			squareState[0] = isCross;
			break;
		}
		else if (squareState[2] == isEmpty) {
			squareState[2] = isCross;
			break;
		}
		else if (squareState[6] == isEmpty) {
			squareState[6] = isCross;
			break;
		}
		else if (squareState[8] == isEmpty) {
			squareState[8] = isCross;
			break;
		}
		else if (squareState[1] == isEmpty) {
			squareState[1] = isCross;
			break;
		}
		else if (squareState[3] == isEmpty) {
			squareState[3] = isCross;
			break;
		}
		else if (squareState[5] == isEmpty) {
			squareState[5] = isCross;
			break;
		}
		else if (squareState[7] == isEmpty) {
			squareState[7] = isCross;
			break;
		}
	}
}
bool TicTacToe::hasWon(int player) {
	for (int i = 0; i < 7; i += 3) if (squareState[i] == player && squareState[i] == squareState[i + 1] && squareState[i] == squareState[i + 2]) return true;
	for (int i = 0; i < 3; i++) if (squareState[i] == player && squareState[i] == squareState[i + 3] && squareState[i] == squareState[i + 6]) return true;
	if (squareState[0] == player && squareState[0] == squareState[4] && squareState[0] == squareState[8]) return true;
	else if (squareState[2] == player && squareState[2] == squareState[4] && squareState[2] == squareState[6]) return true;
	else return false;
}
void TicTacToe::play(sf::RenderWindow& window) {
		if (!hasAnyoneWon) {
		bool isAnySquareEmpty = true;
		placeSquares(window);
		computer();
		if (!hasPlayerPlayed)
			turnText.setString(playerTurn);
		for (int i = 0; i < amountOfSquares; i++) {
			if (!hasPlayerPlayed && doesContainMouseCursor(square[i], window) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && squareState[i] == isEmpty) {
				colorSquare(this->square[i], sf::Color::Magenta);
				squareState[i] = isCircle;
				hasPlayerPlayed = true;
			}
			if (squareState[i] == isCross) square[i].setFillColor(sf::Color::Yellow);

		}
		if (hasPlayerPlayed)
			turnText.setString(computerTurn);
		if (hasWon(isCircle)) {
			winText.setString(playerWins);
			hasAnyoneWon = true;
			hasPlayerPlayed = true;
		}
		else if (hasWon(isCross)) {
			winText.setString(computerWins);
			hasAnyoneWon = true;
		}
		else {
			for (int i = 0; i < amountOfSquares; i++) {
				if (squareState[i] == isEmpty) {
					isAnySquareEmpty = true;
					break;
				}
				else isAnySquareEmpty = false;
			}
			if (!isAnySquareEmpty) {
				winText.setString(aDraw);
				hasAnyoneWon = true;
			}
		}
		window.draw(turnText);
}
	window.draw(titleText);
	window.draw(winText);
	if (hasAnyoneWon) window.draw(exitText);
	draw(window);
}