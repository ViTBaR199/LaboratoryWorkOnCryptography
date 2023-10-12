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

// ����� ��� ����� �����
class FermatTest : public AbstractPrimalityTest {
protected:
	bool iteration(int value) override;
};

// ����� ��� ����� �������-���������
class SolovayStrassenTest : public AbstractPrimalityTest {
protected:
	bool iteration(int value) override;
};

//// ����� ��� ����� �������-������
//class MillerRabinTest : public AbstractPrimalityTest {
//protected:
//	bool iteration(int value) override;
//};