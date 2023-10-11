#include "IProbabilisticSimplicityTest.h"
#include <iostream>
#include <random>

IProbabilisticSimplicityTest::IProbabilisticSimplicityTest() = default;
IProbabilisticSimplicityTest::~IProbabilisticSimplicityTest() = default;

bool AbstractPrimalityTest :: runTest(int value, double minProbability) {
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

// Класс для теста Ферма
// Если value - простое, то оно удовлетворяет сравнению a^(value-1) = 1 (mod value)
// для любого a, не делящегося на value
bool FermatTest :: iteration(int value) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(2, value - 2);
	int a = dist(gen);

	int result = 1;					 //будущий результат
	int base = a % value;			 //остаток от деления, будет вычисляться на каждом шагу
	int exponent = value - 1;		 //степень

	while (exponent > 0) {
		if (exponent & 1) {			 //побитовое И, проверка на нечётность
			result = (result * base) % value;
		}
		base = (base * base) % value;
		exponent >>= 1;
	}
	if (result != 1) {
		return false;				 //число составное
	}

	return true;					 //число простое
}

//// Класс для теста Соловея-Штрассена
//class SolovayStrassenTest : public AbstractPrimalityTest {
//protected:
//	bool iteration(int value) override {
//
//
//	}
//};
//
//// Класс для теста Миллера-Рабина
//class MillerRabinTest : public AbstractPrimalityTest {
//protected:
//	bool iteration(int value) override {
//
//
//	}
//};