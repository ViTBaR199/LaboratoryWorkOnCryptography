#pragma once
class ProbabilisticSimplicityTest
{
public:
	virtual bool runTest(int value, double minProbability) = 0;

	ProbabilisticSimplicityTest() {};
	virtual ~ProbabilisticSimplicityTest() = 0;
};

