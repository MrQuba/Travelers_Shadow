#include "../classes/boss.hpp"

bool Boss::bossSpins(sf::RenderWindow& window) {
	if (!spins) return false;
	if (spins) {
		if (angle > 360) {
			angle = 1;
			spins = false;
			currentSpinProjectile = 0;
			return false;
		}
		this->sprite.rotate(angle);
		if (angle % 10 == 0) {
			window.draw(spinProjectile[currentSpinProjectile]);
			currentSpinProjectile++;
		}
	}
}
