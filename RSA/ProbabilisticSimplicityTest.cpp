#include "IProbabilisticSimplicityTest.h"
#include <iostream>

class AbstractPrimalityTest :ProbabilisticSimplicityTest {
protected:
	virtual bool iteration(int value) = 0;

public:
	bool runTest(int value, double minProbability) override {
		if (minProbability < 0.5 || minProbability >= 1) {
			throw std::invalid_argument("Минимальная вероятность должна быть в диапазоне [0.5, 1)");
		}

		double increase = 0.5;
		while (minProbability < 1 || minProbability <= 0.9995) {
			if (!iteration(value)) {
				return false;
			}
			minProbability += increase;
			increase /= 2;
		}
		return true;
	}
};

// Класс для теста Ферма
class FermatTest : public AbstractPrimalityTest {
protected:
	bool iteration(int value) override {


	}
};

// Класс для теста Соловея-Штрассена
class SolovayStrassenTest : public AbstractPrimalityTest {
protected:
	bool iteration(int value) override {


	}
};

// Класс для теста Миллера-Рабина
class MillerRabinTest : public AbstractPrimalityTest {
protected:
	bool iteration(int value) override {


	}
};