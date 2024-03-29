#include <SFML/Graphics.hpp>
#include "classes/math.hpp"
#include "classes/window.hpp"
#include "classes/entity.hpp"
#include "classes/player.hpp"
#include "classes/boss.hpp"
#include "classes/collisions.hpp"
#include "classes/rockpaperscissors.hpp"
#include "classes/tictactoe.hpp"
#include <iostream>
#include <cmath>
#include <windows.h>

enum {
    Error = -1,
};

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
    bool hasGameEnded = false;

    sf::Font font;
    sf::Text endText;
    endText.setFont(font);
    endText.setCharacterSize(32);
    endText.setFillColor(sf::Color::White);


    RockPaperScissors rockpaperscissors;
    bool hasJustEntered = true;
    Collisions playerSprite;
    Window game(1280, 720, "Traveller's Shadow");
    Entity* player = new Player("assets/graphics/entities/playerSprite.png", 16, 0, 16, 16, 4);
    Entity* boss = new Boss("assets/graphics/entities/bossSprite.png", 0, 0, 23, 45, 4);
    Player pc;
    Entity startingRoomBackground("assets/graphics/backgrounds/startingRoom.png", 0, 0, 192, 108, 6.66666666667);
    Entity tictactoeRoomBackground("assets/graphics/backgrounds/tictactoeRoom.png", 0, 0, 192, 108, 6.66666666667);
    Entity rockpaperscissorsBackground("assets/graphics/backgrounds/rockpaperscissorsRoom.png", 0, 0, 192, 108, 6.66666666667);
    Entity bossBackground("assets/graphics/backgrounds/bossRoom.png", 0, 0, 1920, 1080, 0.66666666666);
    TicTacToe tictactoe;
    Button quit(200, 100, "assets/buttons/quitButton.png", 1);
    quit.button.setFillColor(sf::Color::Red);
    quit.button.setPosition((game.window.getSize().x / 2) - quit.button.getLocalBounds().width, (game.window.getSize().y / 2) - (quit.button.getLocalBounds().height * 3));
    sf::Event event;

    while (game.window.isOpen()) {
        game.window.clear(sf::Color::Blue);
        eventLoop(game.window, event);
        if (hasGameEnded) goto end;
        else if (!hasGameEnded) {
            switch (player->currentSector) {
            case player->isInStartingRoom:
                game.window.draw(startingRoomBackground.sprite);
                if (hasJustEntered) {
                    hasJustEntered = false;
                    player->sprite.setPosition(game.window.getSize().x / 2, game.window.getSize().y);
                }



                if (playerSprite.collidesWithBorder(player->sprite, 0, true)) { player->currentSector = player->isInRockPaperScissorsRoom; hasJustEntered = true; break; }
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
                if (hasJustEntered) {
                    hasJustEntered = false;
                    player->sprite.setPosition(game.window.getSize().x / 2, player->sprite.getPosition().y);
                    boss->sprite.setPosition(game.window.getSize().x / 2, boss->sprite.getLocalBounds().height);
                }
                if (boss->isAlive) {
                    boss->health -= player->hitBoss(boss->sprite, boss->isHit, boss->gotHit);
                    boss->health -= player->hitBossMelee(boss->sprite, boss->isHit, boss->gotHit);
                    player->health -= player->hitByBoss(boss->sprite);
                }
                if (playerSprite.collidesWithBorder(player->sprite, 0 + (player->sprite.getLocalBounds().width * player->sprite.getScale().x), true))
                    player->sprite.setPosition(game.window.getSize().x - (player->sprite.getLocalBounds().width * player->sprite.getScale().x), player->sprite.getPosition().y);
                if (playerSprite.collidesWithBorder(player->sprite, game.window.getSize().x - (player->sprite.getLocalBounds().width * player->sprite.getScale().x), false))
                    player->sprite.setPosition(player->sprite.getLocalBounds().width * player->sprite.getScale().x, player->sprite.getPosition().y);

                game.window.draw(bossBackground.sprite);
                if (boss->isAlive) {
                    boss->update(game.window);
                }
                break;
            default:
                return Error;
            }

            player->update(game.window);
        }
        end:
        if (!boss->isAlive) {
            hasGameEnded = false;
            endText.setString("You Won!");
            if (quit.doesContainMouseCursor(game.window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) game.window.close();
            game.window.draw(endText);
            game.window.draw(quit.button);
        }
        else {
            if (!player->isAlive) {
                hasGameEnded = false;
                endText.setString("You Lost!");
                if (quit.doesContainMouseCursor(game.window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) game.window.close();
                game.window.draw(endText);
                game.window.draw(quit.button);
            }
        }


        game.window.display();
    }
    delete player;
    delete boss;
    exit(0);
    return 0;
}