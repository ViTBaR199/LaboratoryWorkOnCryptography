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
	virtual bool iteration(long long value) = 0;
public:
	bool runTest(int value, double minProbability) override;
};

// Класс для теста Ферма
class FermatTest : public AbstractPrimalityTest {
public:
	bool iteration(long long value) override;
};

// Класс для теста Соловея-Штрассена
class SolovayStrassenTest : public AbstractPrimalityTest {
public:
	bool iteration(long long value) override;
};

// Класс для теста Миллера-Рабина
class MillerRabinTest : public AbstractPrimalityTest {
public:
	bool iteration(long long value) override;
};