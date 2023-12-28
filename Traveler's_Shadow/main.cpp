#include <SFML/Graphics.hpp>
#include "classes/math.hpp"
#include "classes/window.hpp"
#include "classes/entity.hpp"
#include "classes/collisions.hpp"
#include "classes/rockpaperscissors.hpp"
#include "classes/tictactoe.hpp"
#include <iostream>
#include <cmath>


void eventLoop(sf::RenderWindow& window, sf::Event& event) {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
    }

}
int scaleSprite(sf::RenderWindow& window, sf::Sprite sprite, bool x) {
    int scale;
    if (x) scale = ceil(window.getSize().x / sprite.getLocalBounds().width);
    else scale = ceil(window.getSize().y / sprite.getLocalBounds().height);
    return scale;
}

int main() {
    bool isPlaying = true;

    RockPaperScissors rockpaperscissors;
    bool hasJustEntered = true;
    Collisions playerSprite;
    Window game(1280, 720, "Traveller's Shadow");
    Entity* player = new Player("assets/graphics/entities/playerSprite.png", 16, 0, 16, 16, 4);
    Entity startingRoomBackground("assets/graphics/backgrounds/startingRoom.png", 0, 0, 192, 108, 6.66666666667);
    Entity tictactoeRoomBackground("assets/graphics/backgrounds/tictactoeRoom.png", 0, 0, 192, 108, 6.66666666667);
    Entity rockpaperscissorsBackground("assets/graphics/backgrounds/rockpaperscissorsRoom.png", 0, 0, 192, 108, 6.66666666667);
    TicTacToe tictactoe;
    sf::Event event;

    while (game.window.isOpen()) {
        game.window.clear(sf::Color::Blue);
        eventLoop(game.window, event);

        switch (player->currentSector) {
        case player->isInStartingRoom:
            game.window.draw(startingRoomBackground.sprite);
            if (hasJustEntered) {
                hasJustEntered = false;
                player->sprite.setPosition(game.window.getSize().x / 2, game.window.getSize().y);
            }



            if (playerSprite.collidesWithBorder(player->sprite, 0, true)) { player->currentSector = player->isInRockPaperScissorsRoom; hasJustEntered = true; break;}
            else if (playerSprite.collidesWithBorder(player->sprite, game.window.getSize().x - (player->sprite.getLocalBounds().width * player->sprite.getScale().x), false)) { player->currentSector = player->isInTicTacToeRoom; hasJustEntered = true; break; }
            break;
        case player->isInTicTacToeRoom:
            game.window.draw(tictactoeRoomBackground.sprite);
            if (hasJustEntered) {
                isPlaying = true;
                hasJustEntered = false;
                player->sprite.setPosition(0 + (player->sprite.getLocalBounds().width * player->sprite.getScale().x), player->sprite.getPosition().y);
            }
            if (isPlaying) tictactoe.play(game.window, isPlaying);
            if (playerSprite.collidesWithBorder(player->sprite, game.window.getSize().x - (player->sprite.getLocalBounds().width * player->sprite.getScale().x), false) && tictactoe.hasPlayerWon) { player->currentSector = player->isInBossRoom; hasJustEntered = true; break; }
            break;
        case player->isInRockPaperScissorsRoom:
            game.window.draw(rockpaperscissorsBackground.sprite);
            if (hasJustEntered) {
                isPlaying = true;
                hasJustEntered = false;
                player->sprite.setPosition(game.window.getSize().x - (player->sprite.getLocalBounds().width * player->sprite.getScale().x), player->sprite.getPosition().y);
            }
            if (isPlaying) {
                if (rockpaperscissors.play(game.window) == rockpaperscissors.Win) rockpaperscissors.hasPlayerWon = true;
            }
            if (playerSprite.collidesWithBorder(player->sprite, 0 + (player->sprite.getLocalBounds().width * player->sprite.getScale().x), true) && rockpaperscissors.hasPlayerWon) { player->currentSector = player->isInBossRoom; hasJustEntered = true; break; }
            break;
        case player->isInBossRoom:
            game.window.clear(sf::Color::Yellow);
            break;
        default:
            std::cout << "Something went wrong. There is no such sector" << std::endl;
        }

        player->update(game.window);

        game.window.display();
    }
    delete player;

    return 0;
}