#pragma once
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <iostream>
class Atack
{
public:
	double NewtonsAlgorithm(double n);

	unsigned long long AtackFermat(unsigned long long n);

	std::vector<unsigned long long> ChainShot(unsigned long long e, unsigned long long N);

	std::vector<std::pair <unsigned long long, unsigned long long>> SuitableFractions(std::vector<unsigned long long> fractions);
};

