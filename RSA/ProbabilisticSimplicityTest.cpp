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
bool FermatTest :: iteration(int value) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(2, value - 2);
	int a = dist(gen);

	int result = 1;					 //������� ���������
	int base = a % value;			 //������� �� �������, ����� ����������� �� ������ ����
	int exponent = value - 1;		 //�������

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
bool SolovayStrassenTest :: iteration(int value) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(2, value - 2);
	int a = dist(gen);

	// ��������� ����� (a / value)
	int jacobi = CalculatingValues::jacobi(a, value);
	if (jacobi == -1) {
		jacobi = value - 1; // �������� ����� � �������������� ��������
	}

	// ��������� a ^ ((value - 1) / 2) mod value
	int exponent = (value - 1) / 2;
	int result = 1;
	int base = a % value;
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
bool MillerRabinTest::iteration(int value) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(2, value - 2);
	int a = dis(gen);

	int r = 0;
	int d = value - 1;
	while (d % 2 == 0) {
		d /= 2;
		r++;
	}

	int x = 1;
	int base = a % value;
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