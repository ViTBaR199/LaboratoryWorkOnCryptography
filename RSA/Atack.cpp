#include "Atack.h"

double Atack::NewtonsAlgorithm(double n) {
	double x = n;
	double y = (x + n / x) / 2;

	while (fabs(y - x) > 1e-10) {
		x = y;
		y = (x + n / x) / 2;
	}
	return y;
}

unsigned long long Atack::AtackFermat(unsigned long long n){
	unsigned long long a = ceil(NewtonsAlgorithm(n));
	unsigned long long b2 = a * a - n;
	unsigned long long b = round(NewtonsAlgorithm(fabs(b2)));

	while (b * b != b2) {
		a++;
		b2 = a * a - n;
		b = round(NewtonsAlgorithm(fabs(b2)));
	}

	//std::cout << "\nРезультаты: " << a - b << " и " << a + b << std::endl;
    return (a-b-1)*(a+b-1);
}

std::vector<unsigned long long> Atack::ChainShot(unsigned long long e, unsigned long long N){
	std::vector<unsigned long long> result;
	unsigned long long remainder = 0;
	unsigned long long base = 1;

	while (true) {
		base = e / N;
		remainder = e - (N * base);
		result.push_back(base);
		if (remainder == 0) {
			break;
		}
		std::swap(e, remainder);
		std::swap(N, e);
	}
	return result;
}

std::vector<std::pair <unsigned long long, unsigned long long>> Atack::SuitableFractions(std::vector<unsigned long long> fractions) {
	std::vector<std::pair <unsigned long long, unsigned long long>> result;
	unsigned long long p = 0;
	unsigned long long q = 0;
	result.push_back(std::make_pair(1, 0));
	result.push_back(std::make_pair(fractions[0], 1));
	for (int i = 2; i < fractions.size() + 1; i++) {
		/*auto temp = std::make_pair(p, q);
		result[i] = temp;*/

		p = result[i-1].first * fractions[i - 1] + result[i-2].first;
		q = result[i - 1].second * fractions[i - 1] + result[i - 2].second;
		result.push_back(std::make_pair(p, q));
	}
	return result;
}