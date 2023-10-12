#pragma once
class CalculatingValues
{
public:
	static int legendre(int a, int p);
	static int jacobi(int a, int p);

	CalculatingValues();
	virtual ~CalculatingValues();
};

