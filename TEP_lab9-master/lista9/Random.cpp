#include "pch.h"
#include "Random.h"

using namespace std;

Random::Random() {
	random_device rd;
	this->min = 0;
	this->max = INT_MAX;
	this->randomInt = uniform_int_distribution<int>(min, max);
	this->randomReal = uniform_real_distribution<double>(min, max);
	this->gen = mt19937(rd());
}

void Random::setSeed(double newSeed) {
	this->gen = mt19937(newSeed);
}

void Random::setRandomSeed() {
	random_device rd;
	this->gen = mt19937(rd());
}

void Random::setRange(double newMin, double newMax) {
	this->min = newMin;
	this->max = newMax;
	this->randomInt = uniform_int_distribution<int>(min, max);
	this->randomReal = uniform_real_distribution<double>(min, max);
}

void Random::setMin(double newMin) {
	this->min = newMin;
	this->randomInt = uniform_int_distribution<int>(min, max);
	this->randomReal = uniform_real_distribution<double>(min, max);
}

void Random::setMax(double newMax) {
	this->max = newMax;
	this->randomInt = uniform_int_distribution<int>(min, max);
	this->randomReal = uniform_real_distribution<double>(min, max);
}

int Random::nextInt() {
	return randomInt(gen);
}

double Random::nextReal() {
	return randomReal(gen);
}

double Random::getMin() {
	return this->min;
}

double Random::getMax() {
	return this->max;
}