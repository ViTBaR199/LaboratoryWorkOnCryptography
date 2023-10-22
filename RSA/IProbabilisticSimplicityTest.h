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

// ����� ��� ����� �����
class FermatTest : public AbstractPrimalityTest {
public:
	bool iteration(long long value) override;
};

// ����� ��� ����� �������-���������
class SolovayStrassenTest : public AbstractPrimalityTest {
public:
	bool iteration(long long value) override;
};

// ����� ��� ����� �������-������
class MillerRabinTest : public AbstractPrimalityTest {
public:
	bool iteration(long long value) override;
};