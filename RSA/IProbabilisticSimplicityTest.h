#pragma once
#include "CalculatingValues.h"

class IProbabilisticSimplicityTest{
public:
	virtual bool runTest(int value, double minProbability) = 0;

	IProbabilisticSimplicityTest();
	virtual ~IProbabilisticSimplicityTest() = 0;
};

class AbstractPrimalityTest : public IProbabilisticSimplicityTest {
protected:
	virtual bool iteration(int value) = 0;
public:
	bool runTest(int value, double minProbability) override;
};

// Класс для теста Ферма
class FermatTest : public AbstractPrimalityTest {
protected:
	bool iteration(int value) override;
};

// Класс для теста Соловея-Штрассена
class SolovayStrassenTest : public AbstractPrimalityTest {
protected:
	bool iteration(int value) override;
};

//// Класс для теста Миллера-Рабина
//class MillerRabinTest : public AbstractPrimalityTest {
//protected:
//	bool iteration(int value) override;
//};