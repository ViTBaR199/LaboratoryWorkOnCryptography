#include "IProbabilisticSimplicityTest.h"
#include <iostream>
#include <random>

IProbabilisticSimplicityTest::IProbabilisticSimplicityTest() = default;
IProbabilisticSimplicityTest::~IProbabilisticSimplicityTest() = default;

bool AbstractPrimalityTest :: runTest(int value, double minProbability) {
	if (minProbability < 0.5 || minProbability >= 1) {
		throw std::invalid_argument("����������� ����������� ������ ���� � ��������� [0.5, 1)");
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

// ����� ��� ����� �����
// ���� value - �������, �� ��� ������������� ��������� a^(value-1) = 1 (mod value)
// ��� ������ a, �� ���������� �� value
bool FermatTest :: iteration(long long value) {
	value = abs(value);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<long long> dist(2, value - 2);
	long long a = dist(gen);

	long long result = 1;					 //������� ���������
	long long base = a % value;			 //������� �� �������, ����� ����������� �� ������ ����
	long long exponent = value - 1;		 //�������

	while (exponent > 0) {
		if (exponent & 1) {			 //��������� �, �������� �� ����������
			result = (result * base) % value;
		}
		base = (base * base) % value;
		exponent >>= 1;
	}
	if (result != 1) {
		return false;				 //����� ���������
	}

	return true;					 //����� �������
}

// ����� ��� ����� �������-���������
bool SolovayStrassenTest :: iteration(long long value) {
	value = abs(value);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<long long> dist(2, value - 2);
	long long a = dist(gen);

	// ��������� ����� (a / value)
	long long jacobi = CalculatingValues::jacobi(a, value);
	if (jacobi == -1) {
		jacobi = value - 1; // �������� ����� � �������������� ��������
	}

	// ��������� a ^ ((value - 1) / 2) mod value
	long long exponent = (value - 1) / 2;
	long long result = 1;
	long long base = a % value;
	while (exponent > 0) {
		if (exponent & 1) {
			result = (result * base) % value;
		}
		base = (base * base) % value;
		exponent >>= 1;
	}

	// ���� ����� �� ����� ����������, �� ����� ���������
	if (jacobi != result) {
		return false;
	}

	// � ��������� ������, ������������, ��� ����� �������
	return true;
}

// ����� ��� ����� �������-������
bool MillerRabinTest::iteration(long long value) {
	value = abs(value);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<long long> dis(2, value - 2);
	long long a = dis(gen);

	long long r = 0;
	long long d = value - 1;
	while (d % 2 == 0) {
		d /= 2;
		r++;
	}

	long long x = 1;
	long long base = a % value;
	while (d > 0) {
		if (d & 1) {
			x = (x * base) % value;
		}
		base = (base * base) % value;
		d >>= 1;
	}

	if (x == 1 || x == value - 1) {
		return true;		//����� �������
	}

	for (int i = 0; i < r - 1; i++) {
		x = (x * x) % value;

		if (x == 1) {
			return false;		//����� ���������
		}

		if (x == value - 1) {
			return true;		//����� �������
		}
	}

	return false;		//����� ���������
}