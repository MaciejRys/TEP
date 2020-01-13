#pragma once

#include <random>
#include <time.h>

using namespace std;

class Random {
private:
	double min;		//wartoœæ min zakresu
	double max;		//wartoœæ max zakresu
	uniform_int_distribution<int> randomInt;		//generator liczb ca³kowitych
	uniform_real_distribution<double> randomReal;	//generator liczb rzeczywistych
	mt19937 gen;	//ziarno

public:
	Random();		//konstruktor bezparametrowy

	void setSeed(double newSeed);	//ustawia ziarno
	void setRandomSeed();			//ustawia losowe ziarno
	void setRange(double newMin, double newMax);	//ustawia zakres
	void setMin(double newMin);		//ustawia wartoœæ min zakresu
	void setMax(double newMax);		//ustawia wartoœæ max zakresu

	int nextInt();			//zwraca losow¹ liczbê ca³kowit¹ z przedzia³u min max
	double nextReal();		//zwraca losow¹ liczbê rzeczywist¹ z przedzia³u min max
	double getMin();		//zwraca min zakresu
	double getMax();		//zwraca max zakresu

};