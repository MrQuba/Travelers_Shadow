#include <SFML/Graphics.hpp>
#include <iostream>
#pragma once
class Math {
public:
	float canonicalQuadraticFunction(bool isFalling, float x, float p, float q) {
		float result;
		int a;

		if (isFalling) a = 1;
		else a = -1;
		result = (a * (powerOfTwo(x) - powerOfTwo(p))) + q;

		return result;
	}
	float powerOfTwo(int a) {
		return a * a;
	}
	float fallVelocity(float gravity, float mass) {
		return gravity / mass;
	}
};